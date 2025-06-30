// Copyright © 2025 4ozStudio. All rights reserved.


#include "Characters/PlayerCharacterBase_OM.h"

#include "Actors/InteractableActor_OM.h"
#include "Camera/CameraComponent.h"
#include "Characters/NpcBase_OM.h"
#include "Components/Audio/Concrete/FootstepAudio_OM.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Components/Audio/Concrete/PlayerVoiceAudio_OM.h"
#include "Components/Management/AbilitySystemComponent_OM.h"
#include "Game/GameInstance_OM.h"
#include "Interfaces/InteractableInterface_OM.h"


APlayerCharacterBase_OM::APlayerCharacterBase_OM()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
	
	AbSysComp = CreateDefaultSubobject<UAbilitySystemComponent_OM>(TEXT("AbilitySystemComponent"));

	PlayerVoiceAudioComponent = CreateDefaultSubobject<UPlayerVoiceAudio_OM>(TEXT("AudioComponent"));
	PlayerVoiceAudioComponent->bAutoActivate = true;
	PlayerVoiceAudioComponent->SetVolumeMultiplier(1.f);

	FootstepAudioComponent = CreateDefaultSubobject<UFootstepAudio_OM>(TEXT("FootstepAudio"));
	FootstepAudioComponent->bAutoActivate = true;
	FootstepAudioComponent->SetVolumeMultiplier(0.6f);

	NotificationAudioComponent = CreateDefaultSubobject<UNotificationAudio_OM>(TEXT("NotificationAudioComponent"));
	NotificationAudioComponent->bAutoActivate = true;
	NotificationAudioComponent->SetVolumeMultiplier(1.f);


}

void APlayerCharacterBase_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacterBase_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacterBase_OM::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void APlayerCharacterBase_OM::Interact(const bool bToggleable)
{
	FVector Start = Camera->GetComponentLocation();
	FVector ForwardVector = Camera->GetForwardVector();
	FVector End = Start + (ForwardVector * 200.0f);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	if (bHit)
	{
		AActor* InteractedActor = HitResult.GetActor();
		if (!InteractedActor) return;
		
		if (AInteractableActor_OM* InteractedActorInterface = Cast<AInteractableActor_OM>(InteractedActor))
		{
			if (!InteractedActorInterface->InteractableInterfaceProperties.bIsInteractable) return;
			if (UGameInstance_OM* GI = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
			{
				if (!GI->GetHasInteractedInitial())
					GI->SetHasInteractedInitial(true);
			}
			
			InteractedActorInterface->Interact_Implementation();
		}
		else if (ANpcBase_OM* InteractedNpcInterface = Cast<ANpcBase_OM>(InteractedActor))
		{
			InteractedNpcInterface->Interact_Implementation();
		}
	}
	else
	{
		HandleNoHitInteraction();
	}

}

void APlayerCharacterBase_OM::SetEmotionalState()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OMG>(GetWorld()->GetGameInstance());

	if (!GameInstance)
		return;
	

	constexpr float ChadThreshold = 0.7f;
	constexpr float GrindsetThreshold = 0.35f;
	constexpr float DoomerThreshold = -0.3f;
	constexpr float GoblinThreshold = -0.2f;

	const float Ego = GameInstance->GetEgo();
	const float SexAppeal = GameInstance->GetSexAppeal();
	const float Social = GameInstance->GetSocial();
	
	EPlayerEmotionalStates NewState;

	if (Ego >= ChadThreshold && SexAppeal >= ChadThreshold)
	{
		UE_LOG(LogTemp, Error, TEXT("new state giga"));

		NewState = EPlayerEmotionalStates::VeryGood;
	}
	else if (Ego >= GrindsetThreshold && (Social >= GrindsetThreshold || SexAppeal >= GrindsetThreshold))
	{
		UE_LOG(LogTemp, Error, TEXT("new state grind"));
		NewState = EPlayerEmotionalStates::Good;
	}
	else if (SexAppeal <= GoblinThreshold && Social <= GoblinThreshold && Ego >= GrindsetThreshold)
	{
		UE_LOG(LogTemp, Error, TEXT("new state goblin"));
		NewState = EPlayerEmotionalStates::VeryBad;
	}
	else if (Ego <= DoomerThreshold && (Social <= DoomerThreshold || SexAppeal <= DoomerThreshold))
	{
		UE_LOG(LogTemp, Error, TEXT("new state doom"));
		NewState = EPlayerEmotionalStates::Bad;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("new state cope"));
		NewState = EPlayerEmotionalStates::Normal;
	}
	
	GameInstance->SetCurrentEmotionalState(NewState);
}

void APlayerCharacterBase_OM::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
	
}
void APlayerCharacterBase_OM::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
	
}
void APlayerCharacterBase_OM::Jump()
{
	if (!GetCharacterMovement())
	{
		UE_LOG(LogTemp, Error, TEXT("Cant get character movement from Jump"));
		return;
	}


	//FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	float CurrentJumpHeight = CalculateJumpHeight(0.2f);
	GetCharacterMovement()->JumpZVelocity = CurrentJumpHeight;
	Super::Jump();
}

UAbilitySystemComponent* APlayerCharacterBase_OM::GetAbilitySystemComponent() const
{
	return AbSysComp;
}
