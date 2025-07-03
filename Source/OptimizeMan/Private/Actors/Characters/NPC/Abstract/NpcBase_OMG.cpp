// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/NPC/Abstract/NpcBase_OMG.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Other/Gym/Concrete/GymSpeaker_OM.h"
#include "AI/Controllers/NPC_Controller_OMG.h"
#include "AnimInstances/NpcBaseAnimInstance_OMG.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/Character/Concrete/NPCBodyDeformationsComponent_OM.h"
#include "Controllers/NPC_AIController_OM.h"
#include "GameFramework/CharacterMovementComponent.h"

ANpcBase_OMG::ANpcBase_OMG()
{
	PrimaryActorTick.bCanEverTick = true;
	Player = nullptr;
	GameInstance = nullptr;
	PlayerController = nullptr;
	GymSpeaker = nullptr;
	CurrentExerciseType = EExerciseType::None;
	CurrentState = ENpcState::Idle;
	CurrentLookState = ENpcLookStates::Idle;
	
	DeformationComponent = CreateDefaultSubobject<UNPCBodyDeformationsComponent_OM>(TEXT("DeformationComponent"));
	DeformationComponent->SetAutoActivate(true);
}

void ANpcBase_OMG::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UNpcBaseAnimInstance_OMG>(GetMesh()->GetAnimInstance());
	
}

void ANpcBase_OMG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ToggleNpcLookStates();

	if (!Player) return;
	if (bIsInDialogue)
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

void ANpcBase_OMG::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (bIsInDialogue) return;
	StartDialogue();
}


void ANpcBase_OMG::SetCurrentState(const ENpcState InState)
{
	CurrentState = InState;

	if (CurrentState != ENpcState::Talking)
	{
		SetIsOpenForConversation(false);
	}
	
	if (auto* AICont = Cast<ANPC_Controller_OMG>(GetController()))
	{
		if (UBlackboardComponent* BB = AICont->GetBlackboardComponent())
		{
			BB->SetValueAsEnum("NPC State", static_cast<uint8>(InState));

			BB->ClearValue(FName("TargetLocation"));
		}
	}
	//OnNpcStateChanged.Broadcast();
}

void ANpcBase_OMG::StartDialogue()
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

void ANpcBase_OMG::EndDialog()
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

void ANpcBase_OMG::ToggleNpcLookStates()
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
	else if (CurrentState == ENpcState::WorkingOut)
	{
		if (GetCharacterMovement()->GetGroundMovementMode() != EMovementMode::MOVE_None)
		{
			NewState = ENpcLookStates::LookingAtItem;
		}
	}
	else if (CurrentState == ENpcState::TalkingWithNpc && CurrentInteractedNpc)
	{
		NewState = ENpcLookStates::LookingAtNpc;
	}
	else if (GetFriendshipLevel() < -0.6f && GetFriendshipLevel() > -1.f)
	{
		NewState = ENpcLookStates::IgnoringPlayer;
	}
	if (NewState != CurrentLookState)
		CurrentLookState = NewState;
	
}


void ANpcBase_OMG::PlayRandomTalkingAnimForMood()
{
	if (!AnimInstance.IsValid()) return;
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
FVector ANpcBase_OMG::LookAtLocation(const float DeltaTime)
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
	case ENpcLookStates::LookingAtItem:
		if (CurrentInteractedItem)
			TargetLookAtLocation = CurrentInteractedItem->GetActorLocation();
		break;
	case ENpcLookStates::LookingAtNpc:
		if (CurrentInteractedNpc)
			TargetLookAtLocation = CurrentInteractedNpc->GetActorLocation();
		break;
	default:
		TargetLookAtLocation = GetActorLocation() + DefaultLookAtOffset;
		break;
	}
	
	float InterpSpeed = GetFriendshipLevel() <= -0.8f ? 2.f : 10.f;

	
	SmoothedLookAtLocation = FMath::VInterpTo(SmoothedLookAtLocation, TargetLookAtLocation, DeltaTime, InterpSpeed);

	return SmoothedLookAtLocation;
}


