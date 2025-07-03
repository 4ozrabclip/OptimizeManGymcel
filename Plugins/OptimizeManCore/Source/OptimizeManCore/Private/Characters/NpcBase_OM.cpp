// Copyright © 2025 4ozStudio. All rights reserved.


#include "Characters/NpcBase_OM.h"

#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Components/AudioComponent.h"

#include "Animation/NpcBaseAnimInstance_OM.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/PlayerCharacterBase_OM.h"
#include "Controllers/NPC_AIController_OM.h"
#include "Game/GameInstance_OM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Structs/AudioTypes.h"

ANpcBase_OM::ANpcBase_OM()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CurrentMood = ENpcMood::Neutral;
	WalkSpeed = 100.f;
	bCanInteract = true;
	bIsInDialogue = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	AuraLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AuraLight"));
	AuraLight->SetupAttachment(RootComponent);
	AuraLight->SetVisibility(true);
	AuraLight->SetCastShadows(false);
	AuraLight->SetAttenuationRadius(100.f);
	AuraLight->SetIntensityUnits(ELightUnits::Candelas);
	AuraLight->SetIntensity(6.f);

	TalkingAudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("TalkingAudioComponent"));
	TalkingAudioComponent->SetupAttachment(RootComponent);
	TalkingAudioComponent->SetAudioType(EAudioTypes::VoiceAudio);
	MaxPlayerLookAtRange = 1600.f;


}

void ANpcBase_OM::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PlayerController)
    {
    	UE_LOG(LogTemp, Error, TEXT("player controller not found in npc beginplay"))
    	return;
    }
	
	Player = Cast<APlayerCharacterBase_OM>(PlayerController->GetPawn());
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found in npc class beginplay"));
		return;
	}


	AnimInstance = Cast<UNpcBaseAnimInstance_OM>(GetMesh()->GetAnimInstance());
	if (AnimInstance.IsValid())
	{
		AnimInstance->SetPlayer(Player);
	}
	else
	{
		return;
	}
	
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	

	GameInstance = Cast<UGameInstance_OM>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("game instance not found in npc beginplay"))
		return;
	}
	
	GameInstance->OnDarkModeToggled.AddDynamic(this, &ANpcBase_OM::CheckAndSetDarkMode);

	CheckAndSetDarkMode(GameInstance->GetDarkMode());

	InteractableInterfaceProperties.InteractableText = InteractableText;
	InteractableInterfaceProperties.InteractableWidget = InteractableWidget;
}



void ANpcBase_OM::Interact_Implementation()
{
	if (!bCanInteract) return;
	
	if (bIsInDialogue) return;
	

	
}
void ANpcBase_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ANpcBase_OM::CheckAndSetDarkMode(bool bDarkMode)
{
	if (bDarkMode)
	{
		AuraLight->SetAttenuationRadius(35.f);
	}
	else
	{
		AuraLight->SetAttenuationRadius(100.f);
	}
}

ENpcRelationshipState ANpcBase_OM::GetCurrentRelationshipState()
{
	if (!PlayerRelationship.bHasMetPlayer)
		return ENpcRelationshipState::Neutral;
	
	PlayerRelationship.UpdateRelationshipState();

	return PlayerRelationship.RelationshipState;
}


void ANpcBase_OM::SetFriendshipLevel(const float InAmount, const bool bReset)
{
	if (bReset)
	{
		PlayerRelationship.FriendshipLevel = FMath::Clamp(InAmount, -1.f, 1.f);
	}
	else
	{
		PlayerRelationship.FriendshipLevel = FMath::Clamp(PlayerRelationship.FriendshipLevel + InAmount, -1.f, 1.f);
	}

}

void ANpcBase_OM::SetCurrentInteractedNpc(ANpcBase_OM* InNpc)
{
	CurrentInteractedNpc = InNpc;

	if (auto* AICont = Cast<ANPC_AIController_OM>(GetController()))
	{
		if (UBlackboardComponent* BB = AICont->GetBlackboardComponent())
		{
			BB->SetValueAsObject(FName("Current Interacted Npc"), CurrentInteractedNpc.Get());

			FVector TargetLocation = FVector(
								static_cast<int16>(CurrentInteractedNpc->GetActorLocation().X),
								static_cast<int16>(CurrentInteractedNpc->GetActorLocation().Y),
								9.65f);
			
			BB->SetValueAsVector(FName("Target Location"), TargetLocation);
		}
	}
}


void ANpcBase_OM::Talk(USoundBase* InChatAudio) const
{
	if (!TalkingAudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("TalkingAudioComponent null"));
		return;
	}

	if (!InChatAudio)
	{
		UE_LOG(LogTemp, Error, TEXT("InChatAudio null"));
		return;
	}

	TalkingAudioComponent->SetSound(InChatAudio);
	TalkingAudioComponent->Play();
	
}

void ANpcBase_OM::PlayRandomTalkingHelper(TMap<USoundBase*, UAnimMontage*>& InChatMap)
{
	if (InChatMap.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Montage array empty"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Play random Talker Helper working 1"));


	/* Getting the random key/value combo from the Chat Map by making an iterator
	 * and generating a random integer as the final iterator element
	*/
	
	const int RandomIndex = FMath::RandRange(0, InChatMap.Num() - 1);
	TMap<USoundBase*, UAnimMontage*>::TIterator ChatMapIterator = InChatMap.CreateIterator();
	for (size_t i = 0; i < RandomIndex; i++)
	{
		++ChatMapIterator;
	}
	
	if (UAnimMontage* MontageToPlay = ChatMapIterator.Value())
	{
		if (AnimInstance.IsValid())
			AnimInstance->Montage_Play(MontageToPlay);

		CurrentTalkTime = MontageToPlay->GetPlayLength();

	}
	if (USoundBase* AudioToPlay = ChatMapIterator.Key())
	{
		Talk(AudioToPlay);
	}
}

UNpcBaseAnimInstance_OM* ANpcBase_OM::GetAnimInstance()
{
	return AnimInstance.Get();
}