// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/Concrete/SocialInteractionSystem_OM.h"
#include "Actors/Characters/NPC/Abstract/FemaleBase_OM.h"
#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"


USocialInteractionSystem_OM::USocialInteractionSystem_OM()
{
	CurrentInteractedNpc = nullptr;
	CurrentNpcMood = ENpcMood::Neutral;
	NpcAnimInstance = nullptr;
}
void USocialInteractionSystem_OM::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
}


void USocialInteractionSystem_OM::InitConversation()
{
	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("No TodoManager"));
		return;
	}
	CurrentInteractedNpc = Player->GetCurrentInteractedCharacter();
	if (!CurrentInteractedNpc)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Current Interacted NPC"));
		Player->SetCurrentPlayMode(EPlayModes::RegularMode);
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("InitConvo function called"));
	
	LoadNpcFriendshipData();
	
	CurrentNpcMood = CurrentInteractedNpc->GetCurrentMood();


	// TICK???????

	SetComponentTickEnabled(true);

	
	/*if (Player && CurrentInteractedNpc)
	{
		FVector PlayerLocation = Player->GetActorLocation();
		FVector NpcLocation = CurrentInteractedNpc->GetActorLocation();

		FVector Direction = (NpcLocation - PlayerLocation);
		Direction.Z = 0.0f;

		TargetRotation = Direction.Rotation();
		bShouldRotateToNPC = true;
		//Player->bUseControllerRotationYaw = true;

	}*/



}

void USocialInteractionSystem_OM::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, "Tick");

	/*if (Player && bShouldRotateToNPC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, "Tick 2");
		FRotator CurrentRot = Player->GetActorRotation();
		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRotation, DeltaTime, 5.0f);
		Player->SetActorRotation(NewRot);

		if (CurrentRot.Equals(TargetRotation, 1.0f)) 
		{
			bShouldRotateToNPC = false;
			//Player->bUseControllerRotationYaw = false;
		}
	}*/
	
	if (CurrentInteractedNpc)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, "Tick 3");
		FVector2D Delta = FVector2D(CurrentInteractedNpc->GetActorLocation()) - FVector2D(Player->GetActorLocation());
		if (Delta.Size() > 300)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, "Tick 4");
			LeaveConversationOnWalkingOff();
		}
	}
	else if (Player)
	{
		CurrentInteractedNpc = Player->GetCurrentInteractedCharacter();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player null needs to be recasted"));
		Player = Cast<APlayerCharacter_OM>(GetOwner());
	}
}

void USocialInteractionSystem_OM::SaveNpcFriendshipData()
{
	if (!CurrentInteractedNpc) return;

	FName NpcID = CurrentInteractedNpc->GetUniqueNpcID(); 

	UNpcDataSave* NpcData = Cast<UNpcDataSave>(
		UGameplayStatics::DoesSaveGameExist(TEXT("NpcSaveSlot"), 0)
			? UGameplayStatics::LoadGameFromSlot(TEXT("NpcSaveSlot"), 0)
			: UGameplayStatics::CreateSaveGameObject(UNpcDataSave::StaticClass())
	);

	if (!NpcData) return;

	// Update or add
	bool bFound = false;
	for (auto& Entry : NpcData->NpcRelationships)
	{
		if (Entry.NpcIdentifier == NpcID)
		{
			Entry.FriendshipLevel = CurrentInteractedNpc->GetFriendshipLevel();
			Entry.bHasMetPlayer = CurrentInteractedNpc->GetHasMetPlayer();
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		NpcData->NpcRelationships.Add({
			NpcID,
			CurrentInteractedNpc->GetHasMetPlayer(),
			CurrentInteractedNpc->GetFriendshipLevel()
		});
	}

	UGameplayStatics::SaveGameToSlot(NpcData, TEXT("NpcSaveSlot"), 0);
}

void USocialInteractionSystem_OM::LoadNpcFriendshipData()
{
	if (!CurrentInteractedNpc) return;

	FName NpcID = CurrentInteractedNpc->GetUniqueNpcID();

	UNpcDataSave* NpcData = Cast<UNpcDataSave>(
		UGameplayStatics::LoadGameFromSlot(TEXT("NpcSaveSlot"), 0)
	);

	if (!NpcData) return;

	for (const auto& Entry : NpcData->NpcRelationships)
	{
		if (Entry.NpcIdentifier == NpcID)
		{
			CurrentInteractedNpc->SetFriendshipLevel(Entry.FriendshipLevel, true);
			CurrentInteractedNpc->SetHasMetPlayer(Entry.bHasMetPlayer);
			break;
		}
	}
}

void USocialInteractionSystem_OM::ProcessConversationData()
{
	if (!CurrentInteractedNpc) return;

	CurrentNpcMood = CurrentInteractedNpc->GetCurrentMood();
	

	ProcessFriendshipLevel();
	CheckForSocialAchievements();
}

void USocialInteractionSystem_OM::ProcessFriendshipLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Process friendship level called"));
	
	switch (CurrentNpcMood)
	{
	case ENpcMood::Neutral:
		UE_LOG(LogTemp, Error, TEXT("Mood neutral"));
		break;
	case ENpcMood::Angry:
		CurrentInteractedNpc->SetFriendshipLevel(-0.1f);
		AddFocus(-0.1f);
		break;
	case ENpcMood::Happy:
		CurrentInteractedNpc->SetFriendshipLevel(+0.1f);
		break;
	case ENpcMood::Randy:
		CurrentInteractedNpc->SetFriendshipLevel(+0.3f);
		AddFocus(+0.01f);
		break;
	case ENpcMood::Disgusted:
		CurrentInteractedNpc->SetFriendshipLevel(-0.25f);
		AddFocus(-0.15f);
		break;
	case ENpcMood::Uncomfortable:
		CurrentInteractedNpc->SetFriendshipLevel(-0.15f);
		AddFocus(-0.1f);
		break;
	default:
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("Friendship Levvel from comp= %f"), CurrentInteractedNpc->GetFriendshipLevel());
}

void USocialInteractionSystem_OM::CheckForSocialAchievements()
{
	if (!TodoManager)
	{
		TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
		UE_LOG(LogTemp, Warning, TEXT("Had to recast todomanager in social system check for achievements"));
	}

	CompletedTodosCheckList.Empty();
	
	if (CurrentInteractedNpc->IsA<AFemaleBase_OM>())
	{
		CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Gym.TalkToAGirl"));
		
	}
	if (CurrentInteractedNpc->GetFriendshipLevel() >= FriendThreshold)
	{
		CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Gym.MakeSomeoneLikeYou"));
		
	}
	TodoManager->DelayForPlayerAchievements(CompletedTodosCheckList);
}

void USocialInteractionSystem_OM::ManageInteractionLogic(ESocialType InSocialType)
{
    if (!Player) 
    {
        UE_LOG(LogTemp, Error, TEXT("Player pointer null in manageinteractionlogic"));
        return;
    }
    if (!CurrentInteractedNpc)
    {
        UE_LOG(LogTemp, Error, TEXT("Current InteractedNpc is null"));
        Player->SetCurrentPlayMode(EPlayModes::RegularMode);
        return;
    }

	if (!NpcAnimInstance)
		NpcAnimInstance = CurrentInteractedNpc->GetAnimInstance();

	const EPlayerEmotionalStates CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
	
	const ENpcRelationshipState Relationship = CurrentInteractedNpc->GetCurrentRelationshipState();
	const bool bHatesYou = Relationship == ENpcRelationshipState::Enemy;
	const bool bIsFriend = Relationship == ENpcRelationshipState::Friend;
	const bool bIsEnemy = Relationship == ENpcRelationshipState::Enemy;
	const bool bIsFemale = CurrentInteractedNpc->IsA<AFemaleBase_OM>();
    const float GodsJudgement = FMath::FRandRange(0.f, 1.f);
	
    auto ModifyMoodByEmotionalState = [&](ENpcMood& Mood, bool& bPositiveReaction) {
        switch (CurrentEmotionalState)
        {
            case EPlayerEmotionalStates::Doomer:
                Mood = ENpcMood::Uncomfortable;
                bPositiveReaction = false;
                break;
            case EPlayerEmotionalStates::Cope:
            	if (GodsJudgement >= 0.55)
            	{
            		Mood = (bPositiveReaction) ? ENpcMood::Happy : ENpcMood::Uncomfortable;
            	}
	            else
	            {
	            	Mood = (bPositiveReaction) ? ENpcMood::Neutral : ENpcMood::Uncomfortable;
	            }
                break;
            case EPlayerEmotionalStates::Grindset:
                Mood = (bPositiveReaction) ? ENpcMood::Happy : ENpcMood::Neutral;
                break;
            case EPlayerEmotionalStates::Gigachad:
                Mood = ENpcMood::Happy;
                bPositiveReaction = true;
                break;
            case EPlayerEmotionalStates::GoblinMode:
                Mood = ENpcMood::Disgusted;
                bPositiveReaction = false;
                break;
        }
    };
	
    switch (InSocialType)
    {
        case ESocialType::Neutral:
            CurrentInteractedNpc->SetCurrentMood(ENpcMood::Neutral);
            NpcAnimInstance->SetIsExplaining(true);
            break;
        case ESocialType::Friendly:
        {
            ENpcMood Mood = (bIsFriend) ? ENpcMood::Happy : (bIsEnemy) ? ENpcMood::Neutral : ENpcMood::Happy;
            bool bPositiveReaction = (!bHatesYou);
            ModifyMoodByEmotionalState(Mood, bPositiveReaction);
            CurrentInteractedNpc->SetCurrentMood(Mood);
        		if (bHatesYou) break;
            if (bPositiveReaction) NpcAnimInstance->SetIsAffirming(true);
            else NpcAnimInstance->SetIsExplaining(true);
            break;
        }
        case ESocialType::Funny:
        {
        	bool bPositiveReaction = bIsFriend || (!bIsEnemy && GodsJudgement >= 0.55);
        	ENpcMood Mood = bPositiveReaction ? ENpcMood::Happy : (bIsEnemy ? ENpcMood::Uncomfortable : ENpcMood::Neutral);
            ModifyMoodByEmotionalState(Mood, bPositiveReaction);
            CurrentInteractedNpc->SetCurrentMood(Mood);
        		if (bHatesYou) break;
            if (bPositiveReaction) NpcAnimInstance->SetIsAffirming(true);
            else NpcAnimInstance->SetIsDisagreeing(true);
            break;
        }
        case ESocialType::Angry:
        {
            ENpcMood Mood = (bIsFemale && !bIsEnemy && !bIsFriend) ? ENpcMood::Uncomfortable : ENpcMood::Angry;
            bool bPositiveReaction = false;
            ModifyMoodByEmotionalState(Mood, bPositiveReaction);
            CurrentInteractedNpc->SetCurrentMood(Mood);
            NpcAnimInstance->SetIsYelling(true);
            break;
        }
        case ESocialType::Flexing:
        {
            ENpcMood Mood = (bIsFemale) ? ((bIsFriend) ? ENpcMood::Neutral : (bIsEnemy) ? ENpcMood::Disgusted : ENpcMood::Uncomfortable) 
                                       : ((bIsFriend) ? ENpcMood::Neutral : (bIsEnemy) ? ENpcMood::Disgusted : ENpcMood::Uncomfortable);
            bool bPositiveReaction = bIsFriend;
            ModifyMoodByEmotionalState(Mood, bPositiveReaction);
            CurrentInteractedNpc->SetCurrentMood(Mood);
        		if (bHatesYou) break;
            if (bPositiveReaction) NpcAnimInstance->SetIsExplaining(true);
            else NpcAnimInstance->SetIsDisagreeing(true);
            break;
        }
		case ESocialType::Hilarious:
        {
        	ENpcMood Mood = (bIsFriend ? ENpcMood::Happy : bIsEnemy ? ENpcMood::Disgusted : ENpcMood::Happy);
        	CurrentInteractedNpc->SetCurrentMood(Mood);
        	bool bPositiveReaction = (bIsFriend || !bIsEnemy);
			if (bPositiveReaction) NpcAnimInstance->SetIsLaughing(true);
        	else NpcAnimInstance->SetIsDisagreeing(true);
        	break;
        }
		case ESocialType::Awkward:
        {
        	ENpcMood Mood = (bIsFriend) ? ENpcMood::Neutral : (bIsEnemy) ? ENpcMood::Disgusted : ENpcMood::Uncomfortable;
        	CurrentInteractedNpc->SetCurrentMood(Mood);
        	bool bPositiveReaction = bIsFriend;
        		if (bHatesYou) break;
        	if (bPositiveReaction) NpcAnimInstance->SetIsExplaining(true);
        	else NpcAnimInstance->SetIsDisagreeing(true);
        	break;
        }
		case ESocialType::Randy:
        {
        	ENpcMood Mood = (bIsFriend) ? ENpcMood::Uncomfortable : (bIsEnemy) ? ENpcMood::Angry : ENpcMood::Disgusted;
        	bool bPositiveReaction = false;
        	ModifyMoodByEmotionalState(Mood, bPositiveReaction);
        	CurrentInteractedNpc->SetCurrentMood(Mood);
        		if (bHatesYou) break;
        	if (bPositiveReaction) NpcAnimInstance->SetIsAffirming(true);
        	else NpcAnimInstance->SetIsDisagreeing(true);
        	break;
        }
		case ESocialType::DontListen:
        {
        	ENpcMood Mood = (bIsEnemy) ? ENpcMood::Angry : ENpcMood::Neutral;
        	CurrentInteractedNpc->SetCurrentMood(Mood);
        	bool bPositiveReaction = false;
        	ModifyMoodByEmotionalState(Mood, bPositiveReaction);
        	if (bHatesYou) break;
        	if (bPositiveReaction) NpcAnimInstance->SetIsLaughing(true);
        	else NpcAnimInstance->SetIsDisagreeing(true);
        	break;
        }
		case ESocialType::WeirdJoke:
        {
        	ENpcMood Mood = (GodsJudgement >= 0.5f) ? ENpcMood::Happy : ENpcMood::Disgusted;
        	bool bPositiveReaction = (GodsJudgement >= 0.5f);
        	CurrentInteractedNpc->SetCurrentMood(Mood);
        	if (bHatesYou) break;
        	if (bPositiveReaction) NpcAnimInstance->SetIsLaughing(true);
        	else NpcAnimInstance->SetIsDisagreeing(true);
	        break;
        }
        default:
            CurrentInteractedNpc->SetCurrentMood(ENpcMood::Neutral);
            break;
    }
}

void USocialInteractionSystem_OM::LeaveConversation()
{
	SaveNpcFriendshipData();
	if (CurrentInteractedNpc)
		GetWorld()->GetTimerManager().ClearAllTimersForObject(CurrentInteractedNpc);
	
	NpcAnimInstance = nullptr;
	CurrentInteractedNpc = nullptr;

	SetComponentTickEnabled(false);
}

void USocialInteractionSystem_OM::AddFocus(const float InFocus)
{
	Super::AddFocus(InFocus);
}

void USocialInteractionSystem_OM::LeaveConversationOnWalkingOff()
{
	if (!CurrentInteractedNpc)
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentInteractedNpc is null in leave convo on walking off"));
		return;
	}

	CurrentInteractedNpc->EndDialog();
	Player->SetCurrentPlayMode(EPlayModes::RegularMode);
	Player->bInteractableOpen = false;
	SaveNpcFriendshipData();
	
	GetWorld()->GetTimerManager().ClearAllTimersForObject(CurrentInteractedNpc);

	NpcAnimInstance = nullptr;
	CurrentInteractedNpc = nullptr;
	SetComponentTickEnabled(false);

	

	
}
