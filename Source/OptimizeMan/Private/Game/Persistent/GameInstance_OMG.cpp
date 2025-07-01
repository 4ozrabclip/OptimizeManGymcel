// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/Persistent/GameInstance_OMG.h"

#include "Game/SubSystems/TodoManagementSubsystem.h"
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
	
}

void UGameInstance_OMG::ResetAllSaves()
{
	Super::ResetAllSaves();
	if (UGameplayStatics::DoesSaveGameExist(TEXT("NpcSaveSlot"), 0))
	{
		UGameplayStatics::DeleteGameInSlot(TEXT("NpcSaveSlot"), 0);
	}
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


FBodyPartData* UGameInstance_OMG::FindBodyPart(const EBodyPart& Part, const EBodyPartSide& Side)
{
	for (FBodyPartData& PartData : BodyStatus.BodyParts)
	{
		if (PartData.Part == Part && PartData.Side == Side)
		{
			return &PartData;
		}
	}
	return nullptr;
}
float UGameInstance_OMG::GetBodyPartStrengthValue(const EBodyPart& Part, const EBodyPartSide& Side)
{
	if (FBodyPartData* PartData = FindBodyPart(Part, Side))
	{
		return PartData->Strength;
	}
	return 0.f;
}
float UGameInstance_OMG::GetBodyPartLeftRightCombinedStrengthValue(const EBodyPart& Part)
{
	float LeftPartStrength = GetBodyPartStrengthValue(Part, Left);
	float RightPartStrength = GetBodyPartStrengthValue(Part, Right);
	
	return LeftPartStrength + RightPartStrength / 2.f;
	
}

float* UGameInstance_OMG::GetBodyPartStrengthPtr(const EBodyPart& Part, const EBodyPartSide& Side)
{
	if (FBodyPartData* PartData = FindBodyPart(Part, Side))
	{
		return &PartData->Strength;
	}
	return nullptr;
}


void UGameInstance_OMG::SetRandomEventAsWitnessed(const EEventAndGPData InRandomEvent, const bool InWitnessed)
{
	if (bool* bWitnessed = RandomEvents.RandomEventsWitnessedMap.Find(InRandomEvent))
		*bWitnessed = InWitnessed;
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

void UGameInstance_OMG::SetPosterAsOwned(const int PosterIndex, const FString& PosterType)
{
	const FString ChadPosterType_String = "Chad";
	const FString WaifuPosterType_String = "Waifu";

	if (PosterType == ChadPosterType_String)
	{
		if (bOwnsChadPosters.IsValidIndex(PosterIndex) && !bOwnsChadPosters[PosterIndex])
		{
		
			bOwnsChadPosters[PosterIndex] = true;
			UE_LOG(LogTemp, Error, TEXT("Set chad poster as owned"));
		}
	}
	else if (PosterType == WaifuPosterType_String)
	{
		if (bOwnsWaifuPosters.IsValidIndex(PosterIndex) && !bOwnsWaifuPosters[PosterIndex])
		{
			bOwnsWaifuPosters[PosterIndex] = true;
		}
	}
}
void UGameInstance_OMG::Payday(const int InMoney)
{
	SetMoney(InMoney);
}

void UGameInstance_OMG::InitializePlayerData()
{
	Super::InitializePlayerData();
	SetStat(InnerStatus.Ego, 0.f);
	SetStat(InnerStatus.Social, 0.f);
	SetStat(InnerStatus.SexAppeal, 0.f);
	
	SetPossesion(BodyStatus.bIsBulking, false);
	SetPossesion(BodyStatus.bHasJawSurgery, false);
	SetPossesion(BodyStatus.bCurrentlyOnSteroids, false);
}

void UGameInstance_OMG::InitializePostersOwned()
{
	bOwnsWaifuPosters = {false, false, false};
	bOwnsChadPosters = {false, false, false};
}
