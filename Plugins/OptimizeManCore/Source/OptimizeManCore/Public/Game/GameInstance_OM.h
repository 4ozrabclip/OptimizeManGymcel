// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/Dates.h"
#include "Structs/DifficultyDefinitions.h"
#include "Structs/GameSettings.h"
#include "Structs/PlayerData.h"
#include "GameInstance_OM.generated.h"

class UTodoManagementSubsystem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDarkModeToggled, bool, bDarkModeOn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioSettingsChanged,
												float, InMaster, float, InVoice,
												float, InMusic, float, InNotifications,
												float, InSfx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualitySettingsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEmotionalStateChanged, EPlayerEmotionalStates, NewState);


UCLASS(BlueprintType)
class OPTIMIZEMANCORE_API UGameInstance_OM : public UGameInstance 
{
	GENERATED_BODY()
public: 
	/** Overrides **/
	virtual void Init() override;
	virtual void InitializePlayerData() {};
	virtual void InitializeGameSettings();

	/** Shader Toggle **/
	UFUNCTION(BlueprintCallable)
	void DarkModeToggle();
	
	/** Wave/Day Management**/
	UFUNCTION(BlueprintCallable)
	virtual void HandleDayEvents();
	UFUNCTION(BlueprintCallable)
	void IncrementDay();
	
	void CheckWaveScore();
	void IncrementMonth();


	/** Save/Reset Management **/
	UFUNCTION(Category = "Save System")
	virtual void ResetAllSaves() {};
	virtual void ResetGame();
	

	/** Finders/Getters **/
	UFUNCTION(BlueprintCallable) //for use with bedroom door
	bool GetHasOpenedTodoListInitial() const { return bHasOpenedTodoListInitial; }
	UFUNCTION(BlueprintCallable)
	bool GetHasOpenedPauseMenuInitial() const { return bHasOpenedPauseMenuInitial; }
	UFUNCTION(BlueprintCallable)
	bool GetHasInteractedInitial() const { return bHasInteractedInitial; }
	UFUNCTION()
	EMonth GetCurrentMonth() const { return DayInfo.CurrentMonth; };
	UFUNCTION(BlueprintPure)
	int32 GetDayNumber() const { return DayInfo.DayNumber; };
	UFUNCTION(BlueprintPure)
	FString GetCurrentDayName() const;
	UFUNCTION(BlueprintCallable)
	FDayInfo& GetDayInfo() { return DayInfo; }
	UFUNCTION(BlueprintCallable)
	FGameSettings& GetGameSettings() { return GameSettings; }
	UFUNCTION(BlueprintCallable)
	bool GetDarkMode() const { return GameSettings.bDarkMode; }
	UFUNCTION(BlueprintCallable)
	EPlayerEmotionalStates GetCurrentEmotionalState() const { return CurrentEmotionalState; }
	UFUNCTION()
	FGamePointsData& GetGamePointsData() { return GamePointsData; }
	UFUNCTION()
	int GetGamePoints() const { return GamePointsData.GamePoints; }
	
	float GetBaseDifficultyMultiplier() const { return BaseDifficultyMultiplier; }
	float GetTempWaveDifficultyMultiplier() const { return TempWaveDifficultyMultiplier; }
	float GetDifficultyMultiplier() const { return BaseDifficultyMultiplier * TempWaveDifficultyMultiplier; }
	int GetWaveLengthByDays() const { return WaveLengthByDays; }
	
	/** Setters/Adders **/
	UFUNCTION(BlueprintCallable)
	void SetDarkMode(const bool InDarkMode);
	UFUNCTION()
	void SetAudioSettings(const float InMaster, const float InVoice, const float InMusic, const float InNotification, const float InSfx);
	UFUNCTION()
	void AddGamePoints(const int InPoints);
	UFUNCTION(BlueprintCallable)
	void SetCurrentEmotionalState(const EPlayerEmotionalStates NewState);
	
	void SetCurrentWaveType(const EDifficultyWaveType InWaveType) { CurrentWaveType = InWaveType; }
	void SetWaveDetails();
	void SetWaveLengthByDays(const int InLength) { WaveLengthByDays = InLength; }
	void SetEmotionalState(const EPlayerEmotionalStates InEmotionalState) { CurrentEmotionalState = InEmotionalState; }
	void SetBaseDifficultyMultiplier(const float InMultiplier) { BaseDifficultyMultiplier = InMultiplier; }
	void SetTempWaveDifficultyMultiplier(const float InMultiplier) { TempWaveDifficultyMultiplier = InMultiplier; }
	void SetHasOpenedTodoListInitial(const bool InHasOpenedTodoListInitial) { bHasOpenedTodoListInitial = InHasOpenedTodoListInitial; }	
	void SetHasOpenedPauseMenuInitial(const bool InHasOpenedPauseMenuInitial) { bHasOpenedPauseMenuInitial = InHasOpenedPauseMenuInitial; }
	void SetHasInteractedInitial(const bool InHasInteractedInitial) { bHasInteractedInitial = InHasInteractedInitial; }
	void SetStat(float& Stat, float Value)
	{
		Stat = FMath::Clamp(Value, -1.f, 1.0f);
	}
	void AddStat(float& Stat, float Value)
	{
		Stat = FMath::Clamp(Stat + Value, -1.f, 1.0f);
	}
	void SetPossesion(bool& bPossesable, const bool bInPossesion)
	{
		bPossesable = bInPossesion;
	}
	
	/** Delegates **/
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAudioSettingsChanged OnAudioSettingsChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQualitySettingsChanged OnQualitySettingsChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDarkModeToggled OnDarkModeToggled;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEmotionalStateChanged OnEmotionalStateChanged;
	

protected:
	/** Structures **/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Structures")
	FGameSettings GameSettings;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Structures")
	FDayInfo DayInfo;

	UPROPERTY(BlueprintReadOnly, Category = "Structures")
	FGamePointsData GamePointsData;

	UPROPERTY(BlueprintReadOnly, Category = "Player State")
	EPlayerEmotionalStates CurrentEmotionalState = EPlayerEmotionalStates::Normal;



protected:
	/** Subsystems **/  
	UPROPERTY()
	UTodoManagementSubsystem* TodoManagement;



private:
	EDifficultyWaveType CurrentWaveType = EDifficultyWaveType::RestWave;
	int WaveLengthByDays = 3;

	bool bHasOpenedTodoListInitial = false;
	bool bHasOpenedPauseMenuInitial = false;
	bool bHasInteractedInitial = false;
	
	float BaseDifficultyMultiplier = 1.f;
	float TempWaveDifficultyMultiplier = 1.f;

	int DaysSinceBaseDifficultyIncreased = 0;
	int DaysSinceScoreChecked = 0;
	int GameScoreSincePreviousCheck = 0;
	

};