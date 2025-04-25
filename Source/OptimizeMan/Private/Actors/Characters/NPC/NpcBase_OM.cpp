// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/NPC/NpcBase_OM.h"

#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Utils/GameInstance_OM.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "Audio/GymSpeaker_OM.h"
#include "Components/AudioComponent.h"
#include "Actors/Characters/NPC/Components/NPCBodyDeformationsComponent_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "Audio/GameAudio_OM.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utils/Structs/AudioTypes.h"

ANpcBase_OM::ANpcBase_OM()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentState = ENpcState::Idle;
	CurrentLookState = ENpcLookStates::Idle;
	CurrentMood = ENpcMood::Neutral;
	CurrentExerciseType = EExerciseType::None;
	bCanInteract = true;
	bIsInDialogue = false;

	AuraLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AuraLight"));
	AuraLight->SetupAttachment(RootComponent);
	AuraLight->SetVisibility(true);
	AuraLight->SetCastShadows(false);
	AuraLight->SetAttenuationRadius(100.f);
	AuraLight->SetIntensityUnits(ELightUnits::Candelas);
	AuraLight->SetIntensity(6.f);

	DeformationComponent = CreateDefaultSubobject<UNPCBodyDeformationsComponent_OM>(TEXT("DeformationComponent"));
	DeformationComponent->SetAutoActivate(true);

	TalkingAudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("TalkingAudioComponent"));
	TalkingAudioComponent->SetupAttachment(RootComponent);
	TalkingAudioComponent->SetAudioType(EAudioTypes::VoiceAudio);
	MaxPlayerLookAtRange = 1600.f;

	bHasMogFace = false;

	WalkSpeed = 100.f;


	
}

void ANpcBase_OM::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);

	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found in npc class beginplay"));
		return;
	}

	if (!AnimInstance)
	{
		AnimInstance = Cast<UNpcBaseAnimInstance_OM>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->SetPlayer(Player);
		}
	}

	

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("player controller not found in npc beginplay"))
		return;
	}
	GameInstance = Cast<UGameInstance_OM>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("game instance not found in npc beginplay"))
		return;
	}

	InteractableInterfaceProperties.InteractableText = InteractableText;
	InteractableInterfaceProperties.InteractableWidget = InteractableWidget;
}

void ANpcBase_OM::Interact_Implementation()
{
	if (!bCanInteract) return;
	
	if (bIsInDialogue) return;
	
	
	StartDialogue();
	
}
void ANpcBase_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ToggleNpcLookStates();

	if (Player && bIsInDialogue)
	{
		if (PlayerRelationship.RelationshipState == ENpcRelationshipState::HatesYou && !bHasMogFace && DeformationComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Load deformations 1"));
			DeformationComponent->LoadDeformations();
			bHasMogFace = true;

			Player->SetCurrentInteractedCharacter(this);
		}
		DistanceFromPlayerVector = Player->GetActorLocation() - GetActorLocation();
		if (GymSpeaker && GetFriendshipLevel() < -0.8 && CurrentMusicPitch > -2.f)
		{
			CurrentMusicPitch -= DeltaTime * 0.2f;
			CurrentMusicPitch = FMath::Clamp(CurrentMusicPitch, -1.f, 1.f);
			GymSpeaker->ChangePitch(CurrentMusicPitch);
		}
	}
	
}
UNpcBaseAnimInstance_OM* ANpcBase_OM::GetAnimInstance()
{
	return AnimInstance;
}
void ANpcBase_OM::ToggleNpcLookStates()
{
	ENpcLookStates NewState = ENpcLookStates::LookingAtPlayer;
	if (!Player)
	{
		CurrentLookState = ENpcLookStates::Idle;
		return;
	}
	DistanceFromPlayerValue = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	
	if (!Player || DistanceFromPlayerValue > MaxPlayerLookAtRange)
	{
		NewState = ENpcLookStates::Idle;
	}
	else if (GetFriendshipLevel() < -0.6f && GetFriendshipLevel() > -1.f)
	{
		NewState = ENpcLookStates::IgnoringPlayer;
	}
	if (NewState != CurrentLookState)
		CurrentLookState = NewState;
	
}

FVector ANpcBase_OM::LookAtLocation(const float DeltaTime)
{
	if (!Player || !Player->GetMesh()) 
	{
		return GetActorLocation() + DefaultLookAtOffset;
		
	}

	FVector PlayersHeadLocation = Player->GetMesh()->GetSocketLocation("Head");


	FVector TargetLookAtLocation;

	switch (CurrentLookState)
	{
		case ENpcLookStates::Idle:
			TargetLookAtLocation = GetActorLocation() + DefaultLookAtOffset;
			break;

		case ENpcLookStates::LookingAtPlayer:
			TargetLookAtLocation = PlayersHeadLocation;
			break;

		case ENpcLookStates::IgnoringPlayer:
		{
			FVector AwayDirection = GetActorLocation() - PlayersHeadLocation;
			AwayDirection.Normalize();
			TargetLookAtLocation = GetActorLocation() + (AwayDirection * 200.0f);
			break;
		}
		default:
			TargetLookAtLocation = GetActorLocation() + DefaultLookAtOffset;
			break;
	}
	
	float InterpSpeed = GetFriendshipLevel() <= -0.8f ? 2.f : 10.f;

	
	SmoothedLookAtLocation = FMath::VInterpTo(SmoothedLookAtLocation, TargetLookAtLocation, DeltaTime, InterpSpeed);

	return SmoothedLookAtLocation;
}


ENpcRelationshipState ANpcBase_OM::GetCurrentRelationshipState()
{
	if (!PlayerRelationship.bHasMetPlayer)
		return ENpcRelationshipState::Neutral;
	
	PlayerRelationship.UpdateRelationshipState();

	return PlayerRelationship.RelationshipState;
}

void ANpcBase_OM::StartDialogue()
{
	if (!bIsInDialogue)
	{
		bIsInDialogue = true;
		SetCurrentState(ENpcState::Talking);
		ActiveTags.AddTag(FGameplayTag::RequestGameplayTag(FName("NPC.States.InConversation")));
	}
	UE_LOG(LogTemp, Warning, TEXT("START DIALOGUE"));
	
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("player null in start dialogue"));
		return;
	}
	Player->SetCurrentPlayMode(EPlayModes::SocialMode, nullptr, this);
	
}

void ANpcBase_OM::EndDialog()
{
	if (bIsInDialogue)
	{
		bIsInDialogue = false;
		SetCurrentState(ExitDialogueState);
		if (auto* Cont = Cast<ANPC_AIController_OM>(GetController()))
		{
			Cont->GetBlackboardComponent()->ClearValue(FName("TargetRotation"));

		}
		
		ActiveTags.RemoveTag(FGameplayTag::RequestGameplayTag(FName("NPC.States.InConversation")));
	}
	if (!PlayerRelationship.bHasMetPlayer)
	{
		SetHasMetPlayer(true);
	}
	//SetActorTickEnabled(false);
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

void ANpcBase_OM::SetCurrentState(const ENpcState InState)
{
	CurrentState = InState;
	
	if (auto* AICont = Cast<ANPC_AIController_OM>(GetController()))
	{
		if (UBlackboardComponent* BB = AICont->GetBlackboardComponent())
		{
			BB->SetValueAsEnum("NPC State", static_cast<uint8>(InState));

			BB->ClearValue(FName("TargetLocation"));
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

void ANpcBase_OM::PlayRandomTalkingAnimForMood()
{
	if (!AnimInstance) return;
	if (!AnimInstance->GetIsTalking()) return;

	UE_LOG(LogTemp, Warning, TEXT("Play random Talkeranim for mood called "));
	if (AnimInstance->GetIsExplaining())
	{
		PlayRandomTalkingHelper(ExplainingChats);
	}
	else if (AnimInstance->GetIsYelling())
	{
		PlayRandomTalkingHelper(AngryChats);
	}
	else if (AnimInstance->GetIsAffirming())
	{
		PlayRandomTalkingHelper(AffirmingChats);
	}
	else if (AnimInstance->GetIsDisagreeing())
	{
		PlayRandomTalkingHelper(DisagreeingChats);
	}
	else if (AnimInstance->GetIsDisgusted())
	{
		PlayRandomTalkingHelper(DisgustedChats);
	}
	else if (AnimInstance->GetIsLaughing())
	{
		PlayRandomTalkingHelper(LaughingChats);
	}
	else if (AnimInstance->GetIsConfused())
	{
		PlayRandomTalkingHelper(ConfusedChats);
	}
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
		UE_LOG(LogTemp, Warning, TEXT("Play random Talker Helper working with array correct"));
		if (AnimInstance)
			AnimInstance->Montage_Play(MontageToPlay);

		CurrentTalkTime = MontageToPlay->GetPlayLength();
		
		UE_LOG(LogTemp, Warning, TEXT("Current talk time = %f"), CurrentTalkTime);
	}
	if (USoundBase* AudioToPlay = ChatMapIterator.Key())
	{
		Talk(AudioToPlay);
	}
}