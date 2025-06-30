// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/Dates.h"
#include "Structs/DifficultyDefinitions.h"
#include "Utils/Structs/ConsumableData.h"
#include "Utils/Structs/Dates.h"
#include "Structs/GameSettings.h"
#include "Structs/PlayerData.h"
#include "Utils/Structs/PlayerData.h"
#include "Utils/Structs/EventAndGPData.h"
#include "GameInstance_OM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDarkModeToggled, bool, bDarkModeOn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioSettingsChanged,
												float, InMaster, float, InVoice,
												float, InMusic, float, InNotifications,
												float, InSfx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualitySettingsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEmotionalStateChanged, EPlayerEmotionalStates, NewState);


UCLASS(BlueprintType)
class OPTIMIZEMAN_API UGameInstance_OM : public UGameInstance 
{
	GENERATED_BODY()
public: 
	/** Overrides **/
	virtual void Init() override;
	virtual void InitializePlayerData();
	virtual void InitializePostersOwned();
	virtual void InitializeGameSettings();


	/** Save/Reset Management **/
	virtual void ResetGame();

	/** Finders/Getters **/
	UFUNCTION(BlueprintCallable) //for use with bedroom door
	bool GetHasOpenedTodoListInitial() const { return bHasOpenedTodoListInitial; }
	UFUNCTION(BlueprintCallable)
	bool GetHasOpenedPauseMenuInitial() const { return bHasOpenedPauseMenuInitial; }
	UFUNCTION(BlueprintCallable)
	bool GetHasInteractedInitial() const { return bHasInteractedInitial; }
	
	float GetBaseDifficultyMultiplier() const { return BaseDifficultyMultiplier; }
	float GetTempWaveDifficultyMultiplier() const { return TempWaveDifficultyMultiplier; }
	float GetDifficultyMultiplier() const { return BaseDifficultyMultiplier * TempWaveDifficultyMultiplier; }
	
	/** Setters/Adders **/
	void SetCurrentWaveType(const EDifficultyWaveType InWaveType) { CurrentWaveType = InWaveType; }
	void SetWaveDetails();
	void SetEmotionalState(const EPlayerEmotionalStates InEmotionalState) { CurrentEmotionalState = InEmotionalState; };
	
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


	EPlayerEmotionalStates CurrentEmotionalState;



public:
//General Non-UFUNCS
	void CheckWaveScore();

//General UFUNCTIONS
	UFUNCTION(BlueprintCallable)
	void DarkModeToggle();
	UFUNCTION(BlueprintCallable)
	void HandleDayEvents();
	UFUNCTION(BlueprintCallable)
	void IncrementDay();
	UFUNCTION(Category = "Save System")
	void ResetAllSaves();

//Day Info
	UFUNCTION()
	EMonth GetCurrentMonth() const { return DayInfo.CurrentMonth; };
	UFUNCTION(BlueprintPure)
	int32 GetDayNumber() const;
	UFUNCTION(BlueprintPure)
	FString GetCurrentDayName() const;
	UFUNCTION(BlueprintCallable)
	FDayInfo& GetDayInfo() { return DayInfo; }
	
	void IncrementMonth();


	
//General Helpers
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

	
//General Getters/Setters

	/*** GAS ***/


	void SetBaseDifficultyMultiplier(const float InMultiplier) { BaseDifficultyMultiplier = InMultiplier; }
	void SetTempWaveDifficultyMultiplier(const float InMultiplier) { TempWaveDifficultyMultiplier = InMultiplier; }
	

	


	void SetHasOpenedTodoListInitial(const bool InHasOpenedTodoListInitial) { bHasOpenedTodoListInitial = InHasOpenedTodoListInitial; }	

	void SetHasOpenedPauseMenuInitial(const bool InHasOpenedPauseMenuInitial) { bHasOpenedPauseMenuInitial = InHasOpenedPauseMenuInitial; }

	void SetHasInteractedInitial(const bool InHasInteractedInitial) { bHasInteractedInitial = InHasInteractedInitial; }

	
//Game Settings
	UFUNCTION(BlueprintCallable)
	FGameSettings& GetGameSettings() { return GameSettings; }
	UFUNCTION(BlueprintCallable)
	bool GetDarkMode() const { return GameSettings.bDarkMode; }

	UFUNCTION(BlueprintCallable)
	void SetDarkMode(const bool InDarkMode);
	
	UFUNCTION()
	void SetAudioSettings(const float InMaster, const float InVoice, const float InMusic, const float InNotification, const float InSfx);
	
	


//Random Events
	UFUNCTION(BlueprintCallable)
	FEventAndGPData& GetRandomEvents() { return RandomEvents; }
	UFUNCTION(BlueprintCallable)
	void SetRandomEventAsWitnessed(const EEventAndGPData InRandomEvent, const bool InWitnessed);
	
	UFUNCTION(BlueprintCallable)
	TMap<EEventAndGPData, bool> GetRandomEventsWitnessedMap() { return RandomEvents.RandomEventsWitnessedMap; }
	


//Inner Status
	UFUNCTION()
	FInnerStatus& GetInnerStatus() { return InnerStatus; }
	
	float GetEgo() const { return InnerStatus.Ego; }
	float GetSexAppeal() const { return InnerStatus.SexAppeal; }
	float GetSocial() const { return InnerStatus.Social; }
	
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentEmotionalState(const EPlayerEmotionalStates NewState);
	UFUNCTION(BlueprintCallable)
	EPlayerEmotionalStates GetCurrentEmotionalState() const { return InnerStatus.CurrentEmotionalState; }
	
//Inventory Data
	UFUNCTION()
	FInventoryData& GetInventoryData() { return InventoryData; }
	
	bool GetOwnsSteroids() const { return InventoryData.bOwnsSteroids; }
	bool GetOwnsPreWorkout() const { return InventoryData.bOwnsPreWorkout; }
	int GetMoney() const { return InventoryData.Money; }
	void SetMoney(const int InMoney)
	{
		InventoryData.Money += InMoney;
	}

//Consumable Status

	
//Game Points Data
	UFUNCTION()
	FGamePointsData& GetGamePointsData() { return GamePointsData; }
	
	UFUNCTION()
	int GetGamePoints() const { return GamePointsData.GamePoints; }
	
	UFUNCTION()
	void AddGamePoints(const int InPoints);


	
protected: //Subsystems
	UPROPERTY()
	class UTodoManagementSubsystem* TodoManagement;


private:
	TArray<bool> bOwnsWaifuPosters;
	TArray<bool> bOwnsChadPosters;
	
	EDifficultyWaveType CurrentWaveType;
	

	bool bHasOpenedTodoListInitial;
	bool bHasOpenedPauseMenuInitial;
	bool bHasInteractedInitial;

	float BaseDifficultyMultiplier = 1.f;
	float TempWaveDifficultyMultiplier = 1.f;

	int DaysSinceBaseDifficultyIncreased = 0;
	int DaysSinceScoreChecked = 0;
	int GameScoreSincePreviousCheck = 0;
	

};};