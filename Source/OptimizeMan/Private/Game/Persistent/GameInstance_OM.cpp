// Fill out your copyright notice in the Description page of Project Settings.


#include "OptimizeMan/Public/Game/Persistent/GameInstance_OM.h"

#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UGameInstance_OM::FirstDay()
{
	const FString FirstDayTodo1 = "Complete Workout";

	if (!TodoManagement)
	{
		TodoManagement = GetSubsystem<UTodoManagementSubsystem>();
	}
	TodoManagement->SetCurrentTodos(FirstDayTodo1);


}
void UGameInstance_OM::ResetGame()
{
	InitializePlayerData();
	InitializePostersOwned();
	SetHasBeenToGymToday(false);
	SetHasOpenedTodoListInitial(false);
	SetHasInteractedInitial(false);
	SetHasOpenedPauseMenuInitial(false);

	CurrentWaveType = EDifficultyWaveType::RestWave;
	
	ResetAllSaves();
}
void UGameInstance_OM::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init Called: %p"), this);
	InitializePlayerData();
	InitializePostersOwned();
	InitializeGameSettings();
	SetHasBeenToGymToday(false);
	SetHasOpenedTodoListInitial(false);
	SetHasInteractedInitial(false);
	SetHasOpenedPauseMenuInitial(false);
	
	ResetAllSaves();
	
	TodoManagement = GetSubsystem<UTodoManagementSubsystem>();
	if (!TodoManagement)
	{
		UE_LOG(LogTemp, Error, TEXT("TodoManagement Subsystem not found"));
		return;
	}
	TodoManagement->InitializeTodos();
}

void UGameInstance_OM::SetPosterAsOwned(const int PosterIndex, const FString& PosterType)
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

void UGameInstance_OM::InitializePostersOwned()
{
	bOwnsWaifuPosters = {false, false, false};
	bOwnsChadPosters = {false, false, false};
}

void UGameInstance_OM::InitializeGameSettings()
{
	GameSettings.bDarkMode = false;
}
FBodyPartData* UGameInstance_OM::FindBodyPart(const EBodyPart& Part, const EBodyPartSide& Side)
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
float UGameInstance_OM::GetBodyPartStrengthValue(const EBodyPart& Part, const EBodyPartSide& Side)
{
	if (FBodyPartData* PartData = FindBodyPart(Part, Side))
	{
		return PartData->Strength;
	}
	return 0.f;
}
float UGameInstance_OM::GetBodyPartLeftRightCombinedStrengthValue(const EBodyPart& Part)
{
	float LeftPartStrength = GetBodyPartStrengthValue(Part, Left);
	float RightPartStrength = GetBodyPartStrengthValue(Part, Right);
	
	return LeftPartStrength + RightPartStrength / 2.f;
	
}

float* UGameInstance_OM::GetBodyPartStrengthPtr(const EBodyPart& Part, const EBodyPartSide& Side)
{
	if (FBodyPartData* PartData = FindBodyPart(Part, Side))
	{
		return &PartData->Strength;
	}
	return nullptr;
}


void UGameInstance_OM::InitializePlayerData()
{
	SetStat(InnerStatus.Ego, 0.f);
	SetStat(InnerStatus.Social, 0.f);
	SetStat(InnerStatus.SexAppeal, 0.f);
	SetPossesion(InnerStatus.bIsDelusional, false);
	
	SetPossesion(BodyStatus.bIsBulking, false);
	SetPossesion(BodyStatus.bHasJawSurgery, false);
	SetPossesion(BodyStatus.bCurrentlyOnSteroids, false);
}

void UGameInstance_OM::ResetAllSaves()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("NpcSaveSlot"), 0))
	{
		UGameplayStatics::DeleteGameInSlot(TEXT("NpcSaveSlot"), 0);
	}
}

void UGameInstance_OM::AddGymResStats(float& Stat, float Value)
{	
	Stat = FMath::Clamp(Stat + Value, -1.f, 1.0f);
	
	OnGymStatsChanged.Broadcast();
}
void UGameInstance_OM::SetGymResStats(float& Stat, float Value)
{
	Stat = FMath::Clamp(Value, -1.f, 1.0f);

	OnGymStatsChanged.Broadcast();
}

void UGameInstance_OM::AddGamePoints(const int InPoints)
{
	GamePointsData.GamePoints += InPoints;
}

void UGameInstance_OM::DarkModeToggle()
{
	GameSettings.bDarkMode = !GameSettings.bDarkMode;
	UE_LOG(LogTemp, Log, TEXT("DarkModeToggle called. New Dark Mode State: %d"), GameSettings.bDarkMode);
	OnDarkModeToggled.Broadcast();
}

void UGameInstance_OM::SetDarkMode(const bool InDarkMode)
{
	GameSettings.bDarkMode = InDarkMode;
}

void UGameInstance_OM::SetCurrentEmotionalState(const EPlayerEmotionalStates NewState)
{
	UE_LOG(LogTemp, Display, TEXT("SetCurrentEMOTIONAL STATE GI"));
	InnerStatus.CurrentEmotionalState = NewState;
	OnEmotionalStateChanged.Broadcast(NewState);
}

void UGameInstance_OM::SetAudioSettings(const float InMaster, const float InVoice, const float InMusic, const float InNotification, const float InSfx)
{
	UE_LOG(LogTemp, Display, TEXT("Changed audio settings"));
	if (GameSettings.MasterVolume != InMaster)
		GameSettings.MasterVolume = InMaster;
	if (GameSettings.VoiceVolume != InVoice)
		GameSettings.VoiceVolume = InVoice;
	if (GameSettings.MusicVolume != InMusic)
		GameSettings.MusicVolume = InMusic;
	if (GameSettings.NotificationVolume != InNotification)
		GameSettings.NotificationVolume = InNotification;
	if (GameSettings.SfxVolume != InSfx)
		GameSettings.SfxVolume = InSfx;

	OnAudioSettingsChanged.Broadcast(InMaster, InVoice, InMusic, InNotification, InSfx);
}

void UGameInstance_OM::SetRandomEventAsWitnessed(const EEventAndGPData InRandomEvent, const bool InWitnessed)
{
	if (bool* bWitnessed = RandomEvents.RandomEventsWitnessedMap.Find(InRandomEvent))
		*bWitnessed = InWitnessed;
}

void UGameInstance_OM::IncrementMonth()
{
	constexpr int MaxMonthDays = 31;
	if (DayInfo.MonthDayNumber == MaxMonthDays + 1)
	{
		switch (DayInfo.CurrentMonth)
		{
		case EMonth::January:
			DayInfo.CurrentMonth = EMonth::February;
			break;
		case EMonth::February:
			DayInfo.CurrentMonth = EMonth::March;
			break;
		case EMonth::March:
			DayInfo.CurrentMonth = EMonth::April;
			break;
		case EMonth::April:
			DayInfo.CurrentMonth = EMonth::May;
			break;
		case EMonth::May:
			DayInfo.CurrentMonth = EMonth::June;
			break;
		case EMonth::June:
			DayInfo.CurrentMonth = EMonth::July;
			break;
		case EMonth::July:
			DayInfo.CurrentMonth = EMonth::August;
			break;
		case EMonth::August:
			DayInfo.CurrentMonth = EMonth::September;
			break;
		case EMonth::September:
			DayInfo.CurrentMonth = EMonth::October;
			break;
		case EMonth::October:
			DayInfo.CurrentMonth = EMonth::November;
			break;
		case EMonth::November:
			DayInfo.CurrentMonth = EMonth::December;
			break;
		case EMonth::December:
			DayInfo.CurrentMonth = EMonth::January;
			break;
		}
	}
}
void UGameInstance_OM::IncrementDay()
{
	DayInfo.DayNumber++;;

	int32 NextDayInt = static_cast<int32>(DayInfo.CurrentDay);
	NextDayInt = (NextDayInt + 1) % 7;  
	DayInfo.CurrentDay = static_cast<EWeekDay>(NextDayInt);

	IncrementMonth();
	
	// Clear Current Todo Array
	TodoManagement->GetCurrentTodoArray().Empty();
	
	
	HandleDayEvents();
}
void UGameInstance_OM::SetWaveDetails()
{
	constexpr int IntenseWaveMultiplier = 1.5f;
	constexpr int HardWaveMultiplier = 1.25f;
	switch (CurrentWaveType)
	{
	case EDifficultyWaveType::IntenseWave:
		{
			SetTempWaveDifficultyMultiplier(IntenseWaveMultiplier);
			break;
		}
	case EDifficultyWaveType::HardWave:
		{
			SetTempWaveDifficultyMultiplier(HardWaveMultiplier);
			break;
		}
	case EDifficultyWaveType::RestWave:
		{
			break;
		}
	default:
		break;
	}
}
void UGameInstance_OM::Check3DayScore()
{
	const int MediumScoreMin = GameScoreSincePreviousCheck + 5;
	const int MediumScoreMax = GameScoreSincePreviousCheck + 9;
	const int HighScoreMin = GameScoreSincePreviousCheck + 10;
	const int HighScoreMax = GameScoreSincePreviousCheck + 14;
	
	if (GamePointsData.GamePoints > HighScoreMax)
	{
		CurrentWaveType = EDifficultyWaveType::IntenseWave;
	}
	else if (GamePointsData.GamePoints >= HighScoreMin && GamePointsData.GamePoints <= HighScoreMax)
	{
		CurrentWaveType = EDifficultyWaveType::RestWave;
	}
	else if (GamePointsData.GamePoints >= MediumScoreMin && GamePointsData.GamePoints <= MediumScoreMax)
	{
		CurrentWaveType = EDifficultyWaveType::RestWave;
	}
	else if (GamePointsData.GamePoints < MediumScoreMin)
	{
		CurrentWaveType = EDifficultyWaveType::HardWave;
	}

	SetWaveDetails();
}


void UGameInstance_OM::HandleDayEvents()
{
	DayInfo.bIsSpecialDay = false;
	DayInfo.DayEvent.Empty();
	constexpr int PaydayMoney = 30.f;
	
	switch (DayInfo.CurrentDay)
	{
		case EWeekDay::Monday:
			break;
		case EWeekDay::Tuesday:
			Payday(PaydayMoney);
			break;
		case EWeekDay::Wednesday:
			DayInfo.DayEvent = "Zumba";
			break;
		case EWeekDay::Thursday:
			break;
		case EWeekDay::Friday:
			break;
		case EWeekDay::Saturday:
			break;
		case EWeekDay::Sunday:
			break;
	}
	if (DaysSinceScoreChecked >= 3)
	{
		Check3DayScore();
		DaysSinceScoreChecked = 0;
	}
	else
	{
		DaysSinceScoreChecked++;
	}
	
	if (DaysSinceBaseDifficultyIncreased > 7)
	{
		SetBaseDifficultyMultiplier(BaseDifficultyMultiplier + 0.2f);
		DaysSinceBaseDifficultyIncreased = 0;
	}
	else
	{
		DaysSinceBaseDifficultyIncreased++;
	}
}

void UGameInstance_OM::Payday(const int InMoney)
{
	SetMoney(InMoney);
}

FString UGameInstance_OM::GetCurrentDayName() const
{
	switch (DayInfo.CurrentDay)
	{
	case EWeekDay::Monday:
		return "Monday";
	case EWeekDay::Tuesday:
		return "Tuesday";
	case EWeekDay::Wednesday:
		return "Wednesday";
	case EWeekDay::Thursday:
		return "Thursday";
	case EWeekDay::Friday:
		return "Friday";
	case EWeekDay::Saturday:
		return "Saturday";
	case EWeekDay::Sunday:
		return "Sunday";
	default:
		return "Error";
	}
}

int32 UGameInstance_OM::GetDayNumber() const
{
	return DayInfo.DayNumber;
}
