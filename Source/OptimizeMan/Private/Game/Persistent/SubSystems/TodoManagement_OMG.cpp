// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/Persistent/SubSystems/TodoManagement_OMG.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Algo/RandomShuffle.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Game/Persistent/GameInstance_OMG.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/UtilityHelpers_OMG.h"
#include "Utils/Structs/TodoData_Gymcel.h"


void UTodoManagement_OMG::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	GameInstance = Cast<UGameInstance_OMG>(GetGameInstance());

	TimerToTryCasts();
}
void UTodoManagement_OMG::TimerToTryCasts()
{
	GetWorld()->GetTimerManager().ClearTimer(InitializeVariablesHandle);
	
	GetWorld()->GetTimerManager().SetTimer(
		InitializeVariablesHandle,
		this,
		&UTodoManagement_OMG::TryCasts,
		0.3f,
		true);
}

void UTodoManagement_OMG::TryCasts()
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

void UTodoManagement_OMG::InitializeTodos()
{
	FName SexAppealName = FName("SexAppeal");
	FName EgoName = FName("Ego");
	FName SocialName = FName("Social");
	/** Tutorial Todos **/
	FTodoItem TakeColdShower;
	TakeColdShower.Name = TEXT("Take a cold shower");
	TakeColdShower.Level = TEXT("Home");
	TakeColdShower.Desc = TEXT("1 Game Point.  +1 SexAppeal");
	TakeColdShower.StatBuffs = {
		{SexAppealName, 0.1f}
	};
	TakeColdShower.CompletedName = TEXT("Took a cold shower!");
	TakeColdShower.Tag = FGameplayTag::RequestGameplayTag("Todos.Bedroom.TakeColdShower");
	TakeColdShower.Points = 1;
	TodoArray.Add(TakeColdShower);
	
	FTodoItem CompleteWorkout;
	CompleteWorkout.Name = TEXT("Complete Workout");
	CompleteWorkout.Level = TEXT("Gym");
	CompleteWorkout.Desc = TEXT("+1 Ego, +1 SexAppeal");
	CompleteWorkout.StatBuffs = {
		{ EgoName, 0.1f },
		{ SexAppealName, 0.1f }
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
		{ EgoName, 0.1f}
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
		{ SocialName, 0.1f}
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
	{EgoName, 0.1f}
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
		{ EgoName, 0.1f}
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
		{ SocialName, 0.2f},
		{ EgoName, 0.1f}
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
		{ EgoName, 0.1f}
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
		{EgoName, 0.1f},
		{SexAppealName, 0.1f},
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
		{EgoName, 1.f}
	};
	GetARealGirlfriend.CompletedName = TEXT("OMG");
	GetARealGirlfriend.Tag = FGameplayTag::RequestGameplayTag("Todos.Gym.GetARealGirlfriend");
	GetARealGirlfriend.Points = 4;
	TodoArray.Add(GetARealGirlfriend);
}

void UTodoManagement_OMG::ProcessPotentialTodos()
{
	Super::ProcessPotentialTodos();
	FBodyStatus& BodyStatus = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyStatus();
	FInventoryData& InventoryData = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetInventoryData();
	FInnerStatus& InnerStatus = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetInnerStatus();

	PotentialTodos.Empty();

	AddToPotentialTodos(FName("CompleteWorkout"));

	AddToPotentialTodos(FName("GetARealGirlfriend"));
	
	ProcessTodoHelper(!BodyStatus.bIsBulking && GameInstance->GetDayNumber() > 3, FName("StartBulking"));

	float ThighStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartLeftRightCombinedStrengthValue(EBodyPart::Thigh);
	ProcessTodoHelper(ThighStrength > 0 && ThighStrength < 0.5, FName("HitTenSquats"));
	
	ProcessTodoHelper(InventoryData.Money > 5 && !InventoryData.bOwnsSteroids, FName("BuySteroids"));
	ProcessTodoHelper(InventoryData.Money > 0 && InventoryData.bOwnsSteroids, FName("BuySomething"));
	

	ProcessTodoHelper(InnerStatus.Social <= 0, FName("TalkToAGirl"));
	ProcessTodoHelper(InnerStatus.Social >0, FName("MakeSomeoneLikeYou"));

	Algo::RandomShuffle(PotentialTodos);
}

void UTodoManagement_OMG::CompleteTodo(const FGameplayTag TodoCompletedTag)
{
	Super::CompleteTodo(TodoCompletedTag);
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	FInnerStatus& InnerStatus = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetInnerStatus();
	FGymResStats& GymResStats = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetGymResStats();

	for (FTodoItem& Item : CurrentTodoArray)
	{
		if (Item.Tag.MatchesTag(TodoCompletedTag) && !Item.bIsCompleted)
		{
			Item.bIsCompleted = true;

			OnTodoComplete.Broadcast();

			if (Item.Points > 0) OnPointsChanged.Broadcast();

			for (TPair<FName, float>& TodoStatBuffPair : Item.StatBuffs)
			{
				FName BuffType = TodoStatBuffPair.Key;
				float BuffAmount = TodoStatBuffPair.Value;

				if (BuffType == FName("Ego"))
				{
					GameInstance->AddStat(InnerStatus.Ego, BuffAmount);
				}
				else if (BuffType == FName("Social"))
				{
					GameInstance->AddStat(InnerStatus.Social, BuffAmount);
				}
				else if (BuffType == FName("SexAppeal"))
				{
					GameInstance->AddStat(InnerStatus.SexAppeal, BuffAmount);
				}

				constexpr float FocusIncrease = 0.005f;

				GymcelUtils::GetGameInstance_Gymcel(GetWorld())->AddGymResStats(GymResStats.Focus, FocusIncrease);
			}
			
			UpdateTodoList();
			break;
		}
	}

}
