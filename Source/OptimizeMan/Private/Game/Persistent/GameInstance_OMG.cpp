// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/Persistent/GameInstance_OMG.h"

#include "Kismet/GameplayStatics.h"
#include "Structs/DifficultyDefinitions.h"


void UGameInstance_OMG::FirstDay()
{
	const FString FirstDayTodo1 = "Complete Workout";

	if (!TodoManagement)
	{
		TodoManagement = GetSubsystem<UTodoManagementSubsystem>();
	}
	TodoManagement->SetCurrentTodos(FirstDayTodo1);
}

void UGameInstance_OMG::ResetGame()
{
	SetHasBeenToGymToday(false);
	InitializePostersOwned();
	Super::ResetGame();
	InitializePlayerData();

	SetHasOpenedTodoListInitial(false);
	SetHasInteractedInitial(false);
	SetHasOpenedPauseMenuInitial(false);

	SetCurrentWaveType(EDifficultyWaveType::RestWave);
	
	ResetAllSaves();
}

void UGameInstance_OMG::FinishDemo()
{
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		const FString MainMenuLevelString = "/Game/Levels/MainMenu";
		const FName LevelToChangeTo = FName(MainMenuLevelString);
		UGameplayStatics::OpenLevel(this, LevelToChangeTo);
	});
}

void UGameInstance_OMG::AddGymResStats(float& Stat, float Value)
{	
	Stat = FMath::Clamp(Stat + Value, -1.f, 1.0f);
	
	OnGymStatsChanged.Broadcast();
}
void UGameInstance_OMG::SetGymResStats(float& Stat, float Value)
{
	Stat = FMath::Clamp(Value, -1.f, 1.0f);

	OnGymStatsChanged.Broadcast();
}
