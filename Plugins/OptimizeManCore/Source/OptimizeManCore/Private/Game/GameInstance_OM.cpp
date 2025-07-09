// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/GameInstance_OM.h"

#include "Kismet/GameplayStatics.h"
#include "Structs/DifficultyDefinitions.h"


void UGameInstance_OM::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init Called: %p"), this);
	InitializePlayerData();
	InitializeGameSettings();
	SetHasOpenedTodoListInitial(false);
	SetHasInteractedInitial(false);
	SetHasOpenedPauseMenuInitial(false);
	
	ResetAllSaves();
	ExtraInits();
}


void UGameInstance_OM::InitializeGameSettings()
{
	GameSettings.bDarkMode = false;
}

void UGameInstance_OM::ResetGame()
{
	InitializePlayerData();
	SetHasOpenedTodoListInitial(false);
	SetHasInteractedInitial(false);
	SetHasOpenedPauseMenuInitial(false);

	SetCurrentWaveType(EDifficultyWaveType::RestWave);
	
	ResetAllSaves();
}



void UGameInstance_OM::AddGamePoints(const int InPoints)
{
	GamePointsData.GamePoints += InPoints;
}

void UGameInstance_OM::DarkModeToggle()
{
	GameSettings.bDarkMode = !GameSettings.bDarkMode;
	OnDarkModeToggled.Broadcast(GameSettings.bDarkMode);
}

void UGameInstance_OM::SetDarkMode(const bool InDarkMode)
{
	GameSettings.bDarkMode = InDarkMode;
}

void UGameInstance_OM::SetCurrentEmotionalState(const EPlayerEmotionalStates NewState)
{
	CurrentEmotionalState = NewState;
	OnEmotionalStateChanged.Broadcast(NewState);
}

void UGameInstance_OM::SetAudioSettings(const float InMaster, const float InVoice, const float InMusic, const float InNotification, const float InSfx)
{
	if (GameSettings.AudioSettings.MasterVolume != InMaster)
		GameSettings.AudioSettings.MasterVolume = InMaster;
	if (GameSettings.AudioSettings.VoiceVolume != InVoice)
		GameSettings.AudioSettings.VoiceVolume = InVoice;
	if (GameSettings.AudioSettings.MusicVolume != InMusic)
		GameSettings.AudioSettings.MusicVolume = InMusic;
	if (GameSettings.AudioSettings.NotificationVolume != InNotification)
		GameSettings.AudioSettings.NotificationVolume = InNotification;
	if (GameSettings.AudioSettings.SfxVolume != InSfx)
		GameSettings.AudioSettings.SfxVolume = InSfx;

	OnAudioSettingsChanged.Broadcast(InMaster, InVoice, InMusic, InNotification, InSfx);
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
void UGameInstance_OM::CheckWaveScore()
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

	if (DaysSinceScoreChecked >= WaveLengthByDays)
	{
		CheckWaveScore();
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