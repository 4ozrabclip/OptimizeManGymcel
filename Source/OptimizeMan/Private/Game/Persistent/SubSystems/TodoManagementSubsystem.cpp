// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Algo/RandomShuffle.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"


void UTodoManagementSubsystem::InitializeTodos()
{
	/** Tutorial Todos **/
	FTodoItem TakeColdShower;
	TakeColdShower.Name = TEXT("Take a cold shower");
	TakeColdShower.Level = TEXT("Home");
	TakeColdShower.Desc = TEXT("1 Game Point.  +1 SexAppeal");
	TakeColdShower.StatBuffs = {
		{EPlayerStatTypes::SexAppeal, 0.1f}
	};
	TakeColdShower.Todo = ETodoArrayList::TakeColdShower;
	TakeColdShower.Tag = FGameplayTag::RequestGameplayTag("Todos.Bedroom.TakeColdShower");
	TakeColdShower.Points = 1;
	TodoArray.Add(TakeColdShower);
	
	FTodoItem BuySomething; 
	BuySomething.Name = TEXT("Buy Something");
	BuySomething.Level = TEXT("Home");
	BuySomething.Desc = TEXT("+?");
	BuySomething.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f}
	};
	BuySomething.Todo = ETodoArrayList::BuySomething;
	BuySomething.Tag = FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething");
	BuySomething.Points = 0;
	TodoArray.Add(BuySomething);

	FTodoItem TalkToAGirl;
	TalkToAGirl.Name = TEXT("Talk to A Girl");
	TalkToAGirl.Level = TEXT("Gym");
	TalkToAGirl.Desc = TEXT("+1 Social");
	TalkToAGirl.StatBuffs = {
	{EPlayerStatTypes::Social, 0.1f}
		};
	TalkToAGirl.Todo = ETodoArrayList::TalkToAGirl;
	TalkToAGirl.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.TalkToAGirl");
	TalkToAGirl.Points = 0;
	TodoArray.Add(TalkToAGirl);

	FTodoItem StartBulking; // ----- Awaiting Win Condition
	StartBulking.Name = TEXT("Start a bulk");
	StartBulking.Level = TEXT("Home");
	StartBulking.Desc = TEXT("+1 Ego");
	StartBulking.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f}
	};
	StartBulking.Todo = ETodoArrayList::StartBulking;
	StartBulking.Tag = FGameplayTag::RequestGameplayTag("Todos.Bedroom.StartBulking");
	StartBulking.Points = 0;
	TodoArray.Add(StartBulking);

	FTodoItem MakeSomeoneLikeYou; 
	MakeSomeoneLikeYou.Name = TEXT("Make Someone Like You");
	MakeSomeoneLikeYou.Level = TEXT("Gym");
	MakeSomeoneLikeYou.Desc = TEXT("+2 Social, +1 Ego");
	MakeSomeoneLikeYou.StatBuffs = {
		{EPlayerStatTypes::Social, 0.2f},
		{EPlayerStatTypes::Ego, 0.1f}
	};
	MakeSomeoneLikeYou.Todo = ETodoArrayList::MakeSomeoneLikeYou;
	MakeSomeoneLikeYou.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.MakeSomeoneLikeYou");
	MakeSomeoneLikeYou.Points = 2;
	TodoArray.Add(MakeSomeoneLikeYou);
	
	FTodoItem HitTenSquats;
	HitTenSquats.Name = TEXT("Hit 10 squats in a set");
	HitTenSquats.Level = TEXT("Gym");
	HitTenSquats.Desc = TEXT("+1 Ego");
	HitTenSquats.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f}
	};
	HitTenSquats.Todo = ETodoArrayList::HitTenSquats;
	HitTenSquats.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.HitTenSquats");
	HitTenSquats.Points = 2;
	TodoArray.Add(HitTenSquats);

	FTodoItem HitFiveSquats;
	HitFiveSquats.Name = TEXT("Hit 5 squats in a set");
	HitFiveSquats.Level = TEXT("Gym");
	HitFiveSquats.Desc = TEXT("+1 Ego");
	HitFiveSquats.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f}
	};
	HitFiveSquats.Todo = ETodoArrayList::HitFiveSquats;
	HitFiveSquats.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.HitFiveSquats");
	HitFiveSquats.Points = 1;
	TodoArray.Add(HitFiveSquats);

	FTodoItem HitFiveDips;
	HitFiveDips.Name = TEXT("Hit 5 dips in a set");
	HitFiveDips.Level = TEXT("Gym");
	HitFiveDips.Desc = TEXT("+1 Ego");
	HitFiveDips.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f}
	};
	HitFiveDips.Todo = ETodoArrayList::HitFiveDips;
	HitFiveDips.Tag = FGameplayTag::RequestGameplayTag(("Todos.Gym.HitFiveDips"));
	HitFiveDips.Points = 2;
	TodoArray.Add(HitFiveDips);

	FTodoItem IncreaseSquatLift; // --------- Awaiting Win Condition
	IncreaseSquatLift.Name = TEXT("Increase Squat Lift");
	IncreaseSquatLift.Level = TEXT("Gym");
	IncreaseSquatLift.Desc = TEXT("+1 Ego, +1 SexAppeal");
	IncreaseSquatLift.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f},
		{EPlayerStatTypes::SexAppeal, 0.1f},
	};
	IncreaseSquatLift.Todo = ETodoArrayList::IncreaseSquatLift;
	IncreaseSquatLift.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.IncreaseSquatLift");
	IncreaseSquatLift.Points = 2;
	TodoArray.Add(IncreaseSquatLift);
	
	FTodoItem GetARealGirlfriend; // ----- Awaiting Win Condition
	GetARealGirlfriend.Name = TEXT("Get a real girlfriend");
	GetARealGirlfriend.Level = TEXT("Gym");
	GetARealGirlfriend.Desc = TEXT("+10 Ego");
	GetARealGirlfriend.StatBuffs = {
		{EPlayerStatTypes::Ego, 1.f}
	};
	GetARealGirlfriend.Todo = ETodoArrayList::GetARealGirlfriend;
	GetARealGirlfriend.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.GetARealGirlfriend");
	GetARealGirlfriend.Points = 4;
	TodoArray.Add(GetARealGirlfriend);
}

void UTodoManagementSubsystem::AddToPotentialTodos(const ETodoArrayList InTodo)
{
	for (FTodoItem& Item : TodoArray)
	{
		if (Item.Todo == InTodo)
		{
			PotentialTodos.Add(Item);
			return;
		}
	}
	const FString TodoName = UEnum::GetValueAsString(InTodo);
	UE_LOG(LogTemp, Error, TEXT("Cant Find %s in TodoArray"), *TodoName);

}
void UTodoManagementSubsystem::ProcessPotentialTodos()
{
	FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	FInventoryData& InventoryData = GameInstance->GetInventoryData();
	FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();

	PotentialTodos.Empty();
	

	ProcessTodoHelper(!BodyStatus.bIsBulking && GameInstance->GetDayNumber() > 3, ETodoArrayList::StartBulking);

	float ThighStrength = GameInstance->GetBodyPartLeftRightCombinedStrengthValue(EBodyPart::Thigh);
	ProcessTodoHelper(ThighStrength > 0.1 && ThighStrength < 0.5, ETodoArrayList::HitTenSquats);
	ProcessTodoHelper(ThighStrength >= 0 && ThighStrength < 0.3, ETodoArrayList::HitFiveSquats);

	float ChestStrength = GameInstance->GetBodyPartLeftRightCombinedStrengthValue(EBodyPart::Chest);
	ProcessTodoHelper(ChestStrength >= 0 && ChestStrength < 0.2, ETodoArrayList::HitFiveDips);
	
	ProcessTodoHelper(InventoryData.Money > 0 && InventoryData.bOwnsSteroids, ETodoArrayList::BuySomething);
	

	ProcessTodoHelper(InnerStatus.Social <= 0, ETodoArrayList::TalkToAGirl);
	ProcessTodoHelper(InnerStatus.Social >= 0, ETodoArrayList::MakeSomeoneLikeYou);

	Algo::RandomShuffle(PotentialTodos);
}

void UTodoManagementSubsystem::ProcessTodoHelper(bool bTodoCondition, const ETodoArrayList InTodo)
{
	if (bTodoCondition)
		AddToPotentialTodos(InTodo);
}

void UTodoManagementSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UGameInstance_OM>(GetGameInstance());

	TimerToTryCasts();
}
  
// ------- THIS WHOLE THING IS SUS.   SUSS IT OUT!!!!! <-------------------------------------------------
void UTodoManagementSubsystem::TimerToTryCasts()
{
	GetWorld()->GetTimerManager().ClearTimer(InitializeVariablesHandle);
	
	GetWorld()->GetTimerManager().SetTimer(
		InitializeVariablesHandle,
		this,
		&UTodoManagementSubsystem::TryCasts,
		0.3f,
		true);
}

void UTodoManagementSubsystem::TryCasts()
{
	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player)
	{
		TimerToTryCasts();
		return;
	}
	
	NotificationAudio = Cast<UNotificationAudio_OM>(Player->GetComponentByClass(UNotificationAudio_OM::StaticClass()));
	if (!NotificationAudio)
	{
		TimerToTryCasts();
		return;
	}
}


void UTodoManagementSubsystem::SetCurrentTodos(const FString& Todo1, const FString& Todo2, const FString& Todo3)
{
	CurrentTodoArray.Empty();

	// See if the todos text we entered in parameter are in our TodoArray, then add them to our CurrentTodoArray
	for (const FTodoItem& Item : TodoArray)
	{
		if (Item.Name == Todo1)
		{
			CurrentTodoArray.Add(Item);
		}
		else if (Item.Name == Todo2)
		{
			CurrentTodoArray.Add(Item);
		}
		else if (Item.Name == Todo3)
		{
			CurrentTodoArray.Add(Item);
		}
	}
}

void UTodoManagementSubsystem::AddToCurrentTodos(const FString& InTodo, const bool bClearCurrentTodo)
{
	if (bClearCurrentTodo) CurrentTodoArray.Empty();

	if (CurrentTodoArray.Num() > 3)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant add anymore to current todo array.  Just clear it with the boolean parameter? "));
		return;
	}
	
	for (const FTodoItem& Item : TodoArray)
	{
		if (Item.Name == InTodo)
		{
			CurrentTodoArray.Add(Item);
		}
	}
}
void UTodoManagementSubsystem::RemoveFromCurrentTodos(const FString& InTodo)
{
	for (const FTodoItem& Item : TodoArray)
	{
		if (Item.Name == InTodo)
		{
			CurrentTodoArray.Remove(Item);
		}
	}
}

FString UTodoManagementSubsystem::GetTodoName(const int TodoIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("GET TODO NAME CALLED"));
	if (CurrentTodoArray.IsValidIndex(TodoIndex))
	{
		return CurrentTodoArray[TodoIndex].Name;
	}
	return FString("");
}
void UTodoManagementSubsystem::DelayForPlayerAchievements(TArray<FGameplayTag> TodoCompletedTags, float TimeTilCheck)
{
	GetWorld()->GetTimerManager().ClearTimer(DelayForPlayerAchievementsHandle);

	short Index = 0;

	FTimerDelegate StaggerDelegate;
	StaggerDelegate.BindLambda([this, TodoCompletedTags, Index, StaggerDelegate, TimeTilCheck]() mutable
	{
		if (TodoCompletedTags.IsValidIndex(Index))
			CompleteTodo(TodoCompletedTags[Index]);
			Index++;
		
		if (Index < TodoCompletedTags.Num())
			GetWorld()->GetTimerManager().SetTimer(DelayForPlayerAchievementsHandle,StaggerDelegate, TimeTilCheck, true);
	});


	GetWorld()->GetTimerManager().SetTimer(DelayForPlayerAchievementsHandle,StaggerDelegate, TimeTilCheck, true);

}
void UTodoManagementSubsystem::CompleteTodo(const FGameplayTag TodoCompletedTag)
{
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();
	FGymResStats& GymResStats = GameInstance->GetGymResStats();

	for (FTodoItem& Item : CurrentTodoArray)
	{
		if (Item.Tag.MatchesTag(TodoCompletedTag) && !Item.bIsCompleted)
		{
			UE_LOG(LogTemp, Display, TEXT("Item found in CompleteTodo"));
			Item.bIsCompleted = true;

			OnTodoComplete.Broadcast();

			if (Item.Points > 0) GameInstance->AddGamePoints(Item.Points);

			for (TPair<EPlayerStatTypes, float>& TodoStatBuffPair : Item.StatBuffs)
			{
				EPlayerStatTypes BuffType = TodoStatBuffPair.Key;
				float BuffAmount = TodoStatBuffPair.Value;

				switch (BuffType)
				{
					case EPlayerStatTypes::Ego:
						GameInstance->AddEgo(BuffAmount);
						break;
					case EPlayerStatTypes::Social:
						GameInstance->AddSocial(BuffAmount);
						break;
					case EPlayerStatTypes::SexAppeal:
						GameInstance->AddSexAppeal(BuffAmount);
						break;
					default:
						break;
				}
				constexpr float FocusIncrease = 0.005f;

				GameInstance->AddGymResStats(GymResStats.Focus, FocusIncrease);
			}
			
			UpdateTodoList();
			break;
		}
	}

	
}
void UTodoManagementSubsystem::UpdateTodoList()
{
	for (FTodoItem& Item : CurrentTodoArray)
	{
		if (Item.bIsCompleted)
		{
			//Item.Name = Item.CompletedName;
		}
	}
}

bool UTodoManagementSubsystem::CurrentTodoListContainsName(const FString& InName, bool InIsComplete)
{
	for (FTodoItem& Item : CurrentTodoArray)
	{
		if (Item.Name == InName && Item.bIsCompleted == InIsComplete) return true;
	}
	return false;
}
bool UTodoManagementSubsystem::CurrentTodoListContainsLayer(const FString& InLayer, bool InIsComplete)
{
	for (FTodoItem& Item : CurrentTodoArray)
	{
		if (Item.Level == InLayer && Item.bIsCompleted == InIsComplete)
		{
			return true;
		}
	}
	return false;
}