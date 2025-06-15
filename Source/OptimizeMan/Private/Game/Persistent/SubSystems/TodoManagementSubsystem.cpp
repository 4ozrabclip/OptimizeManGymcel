// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Algo/RandomShuffle.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"


void UTodoManagementSubsystem::InitializeTodos()
{
	FTodoItem CompleteWorkout;
	CompleteWorkout.Name = TEXT("Complete Workout");
	CompleteWorkout.Level = TEXT("Gym");
	CompleteWorkout.Desc = TEXT("+1 Ego, +1 SexAppeal");
	CompleteWorkout.StatBuffs = {
		{ EPlayerStatTypes::Ego, 0.1f },
		{ EPlayerStatTypes::SexAppeal, 0.1f }
	};
	CompleteWorkout.CompletedName = TEXT("Workout FIN :D");
	CompleteWorkout.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.Workout");
	CompleteWorkout.Points = 0;
	TodoArray.Add(CompleteWorkout);

	FTodoItem BuySomething; 
	BuySomething.Name = TEXT("Buy Something");
	BuySomething.Level = TEXT("Bedroom");
	BuySomething.Desc = TEXT("+?");
	BuySomething.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f}
	};
	BuySomething.CompletedName = TEXT("Buy Something DONE");
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
	TalkToAGirl.CompletedName = TEXT("Talked To Girl!!");
	TalkToAGirl.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.TalkToAGirl");
	TalkToAGirl.Points = 0;
	TodoArray.Add(TalkToAGirl);

	FTodoItem BuySteroids;
	BuySteroids.Name = TEXT("Buy Steroids");
	BuySteroids.Level = TEXT("Bedroom");
	BuySteroids.Desc = TEXT("+1 Ego");
	BuySteroids.StatBuffs = {
	{EPlayerStatTypes::Ego, 0.1f}
	};
	BuySteroids.CompletedName = TEXT("Buy Steroids DONE");
	BuySteroids.Tag = FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySteroids");
	BuySteroids.Points = 0;
	TodoArray.Add(BuySteroids);

	FTodoItem StartBulking; // ----- Awaiting Win Condition
	StartBulking.Name = TEXT("Start a bulk");
	StartBulking.Level = TEXT("Bedroom");
	StartBulking.Desc = TEXT("+1 Ego");
	StartBulking.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f}
	};
	StartBulking.CompletedName = TEXT("Started my bulk");
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
	MakeSomeoneLikeYou.CompletedName = TEXT("Make Someone Like You DONE");
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
	HitTenSquats.CompletedName = TEXT("HIT TEN SQUATS!!");
	HitTenSquats.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.HitTenSquats");
	HitTenSquats.Points = 2;
	TodoArray.Add(HitTenSquats);

	FTodoItem IncreaseSquatLift; // --------- Awaiting Win Condition
	IncreaseSquatLift.Name = TEXT("Increase Squat Lift");
	IncreaseSquatLift.Level = TEXT("Gym");
	IncreaseSquatLift.Desc = TEXT("+1 Ego, +1 SexAppeal");
	IncreaseSquatLift.StatBuffs = {
		{EPlayerStatTypes::Ego, 0.1f},
		{EPlayerStatTypes::SexAppeal, 0.1f},
	};
	IncreaseSquatLift.CompletedName = TEXT("INCREASED");
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
	GetARealGirlfriend.CompletedName = TEXT("OMG");
	GetARealGirlfriend.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.GetARealGirlfriend");
	GetARealGirlfriend.Points = 4;
	TodoArray.Add(GetARealGirlfriend);
}

void UTodoManagementSubsystem::AddToPotentialTodos(const ETodoArrayList InTodo)
{
	if (TodoArray.IsValidIndex(InTodo))
	{
		PotentialTodos.Add(TodoArray[InTodo]);
	}
	else
	{
		const FString TodoName = UEnum::GetValueAsString(InTodo);
		UE_LOG(LogTemp, Error, TEXT("Cant Find %s in TodoArray"), *TodoName);
	}
}
void UTodoManagementSubsystem::ProcessPotentialTodos()
{
	FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	FInventoryData& InventoryData = GameInstance->GetInventoryData();
	FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();

	PotentialTodos.Empty();

	AddToPotentialTodos(CompleteWorkout);

	AddToPotentialTodos(GetARealGirlfriend);
	
	ProcessTodoHelper(!BodyStatus.bIsBulking && GameInstance->GetDayNumber() > 3, StartBulking);

	float ThighStrength = GameInstance->GetBodyPartLeftRightCombinedStrengthValue(Thigh);
	ProcessTodoHelper(ThighStrength > 0 && ThighStrength < 0.5, HitTenSquats);
	
	ProcessTodoHelper(InventoryData.Money > 5 && !InventoryData.bOwnsSteroids, BuySteroids);
	ProcessTodoHelper(InventoryData.Money > 0 && InventoryData.bOwnsSteroids, BuySomething);
	

	ProcessTodoHelper(InnerStatus.Social <= 0, TalkToAGirl);
	ProcessTodoHelper(InnerStatus.Social >0, MakeSomeoneLikeYou);

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

			if (Item.Points > 0) OnPointsChanged.Broadcast();

			for (TPair<EPlayerStatTypes, float>& TodoStatBuffPair : Item.StatBuffs)
			{
				EPlayerStatTypes BuffType = TodoStatBuffPair.Key;
				float BuffAmount = TodoStatBuffPair.Value;

				switch (BuffType)
				{
					case EPlayerStatTypes::Ego:
						GameInstance->AddStat(InnerStatus.Ego, BuffAmount);
						break;
					case EPlayerStatTypes::Social:
						GameInstance->AddStat(InnerStatus.Social, BuffAmount);
						break;
					case EPlayerStatTypes::SexAppeal:
						GameInstance->AddStat(InnerStatus.SexAppeal, BuffAmount);
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
			Item.Name = Item.CompletedName;
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