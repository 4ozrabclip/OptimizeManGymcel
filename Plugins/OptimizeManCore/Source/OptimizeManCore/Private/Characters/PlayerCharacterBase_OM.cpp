// Copyright © 2025 4ozStudio. All rights reserved.


#include "Characters/PlayerCharacterBase_OM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/InteractableActor_OM.h"
#include "Animation/PlayerCharacterAnimInstance_OM.h"
#include "Camera/CameraComponent.h"
#include "Characters/NpcBase_OM.h"
#include "Components/Audio/Concrete/FootstepAudio_OM.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Components/Audio/Concrete/PlayerVoiceAudio_OM.h"
#include "Components/Management/AbilitySystemComponent_OM.h"
#include "Controllers/PlayerController_OM.h"
#include "Game/GameInstance_OM.h"
#include "Game/SubSystems/TodoManagementSubsystem.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "Kismet/GameplayStatics.h"


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
	PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	LastPosition = GetActorLocation();
	
	if (UCharacterMovementComponent* PlayerMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement()))
		SetOriginalMovementSpeed(PlayerMovement->MaxWalkSpeed);
	
	GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoManager) return;

	
	if (USkeletalMeshComponent* SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>())
	{
		DefaultSkeletalMesh = SkeletalMeshComponent->GetSkeletalMeshAsset();
		CachedAnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(SkeletalMeshComponent->GetAnimInstance());

		if (!CachedAnimInstance.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to cache anim instance!"));
			return;
		}
	}
	
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

UAbilitySystemComponent* APlayerCharacterBase_OM::GetAbilitySystemComponent() const
{
	return AbSysComp;
}
bool APlayerCharacterBase_OM::GetIsJumping() const
{
	constexpr float LengthToFloor = 100.f;
	FHitResult HitResult;
	FVector PlayerPosition = GetActorLocation();
	FVector GroundPosition = PlayerPosition - FVector(0.0f, 0.0f, LengthToFloor);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, PlayerPosition, GroundPosition, ECC_Visibility, QueryParams))
	{
		if (HitResult.GetComponent())
		{
			return false;
		}
		return true;
	}
	return true;
}
float APlayerCharacterBase_OM::GetMaxMovementSpeed() const
{
	const UCharacterMovementComponent* PlayerMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	return PlayerMovement->MaxWalkSpeed;
}
void APlayerCharacterBase_OM::SetMaxMovementSpeed(const float InMaxMovementSpeed)
{
	if (UCharacterMovementComponent* PlayerMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement()))
	{
		PlayerMovement->MaxWalkSpeed = InMaxMovementSpeed;
	}
}
void APlayerCharacterBase_OM::UpdateMovementState()
{
	const FVector CurrentPosition = GetActorLocation();
	const float MovementDelta = FVector::Distance(CurrentPosition, LastPosition);
	SetIsWalking(MovementDelta > MinimumMovementThreshold);

	LastPosition = CurrentPosition;
}

void APlayerCharacterBase_OM::CheckInteractable()
{
	const FVector Start = Camera->GetComponentLocation();
	const FVector ForwardVector = Camera->GetForwardVector();
	const FVector End = Start + (ForwardVector * 200.0f); 

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	if (!PlayerController) return;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bHit)
	{
		AActor* InteractedActor = HitResult.GetActor();
		if (!InteractedActor) return;
		
		
		if (AInteractableActor_OM* InteractedActorInterface = Cast<AInteractableActor_OM>(InteractedActor))
		{
			if (!InteractedActorInterface->InteractableInterfaceProperties.bIsInteractable) return;
			PlayerController->WidgetInteraction(InteractedActorInterface);
		}
		else if (ANpcBase_OM* InteractedNpcInterface = Cast<ANpcBase_OM>(InteractedActor))
		{
			PlayerController->WidgetInteraction(InteractedNpcInterface);
		}
		else if (PlayerController->GetIsInteractableWidgetOnViewport())
		{
			PlayerController->ToggleInteractWidgetFromViewport(true);
		}
	}
	else if (PlayerController->GetIsInteractableWidgetOnViewport())
	{
		PlayerController->ToggleInteractWidgetFromViewport(true);
	}
}
