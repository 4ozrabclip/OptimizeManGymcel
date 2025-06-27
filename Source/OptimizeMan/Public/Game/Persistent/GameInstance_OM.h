// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Utils/Structs/ConsumableData.h"
#include "Utils/Structs/Dates.h"
#include "Utils/Structs/GameSettings.h"
#include "Utils/Structs/PlayerData.h"
#include "Utils/Structs/EventAndGPData.h"
#include "GameInstance_OM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDarkModeToggled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioSettingsChanged,
												float, InMaster, float, InVoice,
												float, InMusic, float, InNotifications,
												float, InSfx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualitySettingsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEmotionalStateChanged, EPlayerEmotionalStates, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGymStatsChanged);

class APoster_OM;
UCLASS(BlueprintType)
class OPTIMIZEMAN_API UGameInstance_OM : public UGameInstance 
{
	GENERATED_BODY()
	
public: // Initialization
	virtual void Init() override;


	void FirstDay();
	void ResetGame();
	void FinishDemo();

	
	void InitializePlayerData();
	void InitializePostersOwned();
	void InitializeGameSettings();

	
	FBodyPartData* FindBodyPart(const EBodyPart& Part, const EBodyPartSide& Side);
	float GetBodyPartStrengthValue(const EBodyPart& Part, const EBodyPartSide& Side);
	float GetBodyPartLeftRightCombinedStrengthValue(const EBodyPart& Part);
	float* GetBodyPartStrengthPtr(const EBodyPart& Part, const EBodyPartSide& Side);



public: //delegates
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAudioSettingsChanged OnAudioSettingsChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQualitySettingsChanged OnQualitySettingsChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDarkModeToggled OnDarkModeToggled;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGymStatsChanged OnGymStatsChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEmotionalStateChanged OnEmotionalStateChanged;
	

protected:
	UPROPERTY(BlueprintReadOnly)
	FGameSettings GameSettings;
	UPROPERTY(BlueprintReadOnly)
	FEventAndGPData RandomEvents;
	UPROPERTY(BlueprintReadOnly)
	FGamePointsData GamePointsData;
	UPROPERTY(BlueprintReadOnly)
	FGymResStats GymResStats;
	UPROPERTY(BlueprintReadOnly)
	FBodyStatus BodyStatus;
	UPROPERTY(BlueprintReadOnly)
	FInnerStatus InnerStatus;
	UPROPERTY(BlueprintReadOnly)
	FInventoryData InventoryData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Day info")
	FDayInfo DayInfo;

public:
//General Non-UFUNCS
	void SetWaveDetails();
	void Check3DayScore();

//General UFUNCTIONS
	UFUNCTION(BlueprintCallable)
	void DarkModeToggle();
	UFUNCTION(BlueprintCallable)
	void HandleDayEvents();
	UFUNCTION(BlueprintCallable)
	void IncrementDay();
	UFUNCTION()
	void Payday(const int InMoney);
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
	void SetInnerStatus(const FInnerStatus& InInnerStatus) {InnerStatus = InInnerStatus;}

	
	float GetBaseDifficultyMultiplier() const { return BaseDifficultyMultiplier; }
	void SetBaseDifficultyMultiplier(const float InMultiplier) { BaseDifficultyMultiplier = InMultiplier; }
	float GetTempWaveDifficultyMultiplier() const { return TempWaveDifficultyMultiplier; }
	void SetTempWaveDifficultyMultiplier(const float InMultiplier) { TempWaveDifficultyMultiplier = InMultiplier; }

	float GetDifficultyMultiplier() const { return BaseDifficultyMultiplier * TempWaveDifficultyMultiplier; }

	void SetPosterAsOwned(const int PosterIndex, const FString& PosterType);
	TArray<bool> GetOwnedWaifuPosters() { return bOwnsWaifuPosters;}
	TArray<bool> GetOwnedChadPosters() { return bOwnsChadPosters;}
		
	bool GetHasBeenToGymToday() const { return bHasBeenToGymToday; }
	void SetHasBeenToGymToday(const bool InHasBeenToGymToday) { bHasBeenToGymToday = InHasBeenToGymToday; }

	UFUNCTION(BlueprintCallable) //for use with bedroom door
	bool GetHasOpenedTodoListInitial() const { return bHasOpenedTodoListInitial; }
	void SetHasOpenedTodoListInitial(const bool InHasOpenedTodoListInitial) { bHasOpenedTodoListInitial = InHasOpenedTodoListInitial; }	

	UFUNCTION(BlueprintCallable)
	bool GetHasOpenedPauseMenuInitial() const { return bHasOpenedPauseMenuInitial; }
	void SetHasOpenedPauseMenuInitial(const bool InHasOpenedPauseMenuInitial) { bHasOpenedPauseMenuInitial = InHasOpenedPauseMenuInitial; }

	UFUNCTION(BlueprintCallable)
	bool GetHasInteractedInitial() const { return bHasInteractedInitial; }
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

	
//Gym Res Stats
	UFUNCTION(BlueprintCallable)
	FGymResStats& GetGymResStats() { return GymResStats; }
	
	UFUNCTION()
	void AddGymResStats(float& Stat, float Value);
	UFUNCTION()
	void SetGymResStats(float& Stat, float Value);

//Random Events
	UFUNCTION(BlueprintCallable)
	FEventAndGPData& GetRandomEvents() { return RandomEvents; }
	UFUNCTION(BlueprintCallable)
	void SetRandomEventAsWitnessed(const EEventAndGPData InRandomEvent, const bool InWitnessed);
	
	UFUNCTION(BlueprintCallable)
	TMap<EEventAndGPData, bool> GetRandomEventsWitnessedMap() { return RandomEvents.RandomEventsWitnessedMap; }
	
//Body Status
	UFUNCTION()
	FBodyStatus& GetBodyStatus() { return BodyStatus;}
	bool GetCurrentlyOnSteroids() const { return BodyStatus.bCurrentlyOnSteroids; }

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
	
	bool bHasBeenToGymToday;
	bool bHasOpenedTodoListInitial;
	bool bHasOpenedPauseMenuInitial;
	bool bHasInteractedInitial;

	float BaseDifficultyMultiplier = 1.f;
	float TempWaveDifficultyMultiplier = 1.f;

	int DaysSinceBaseDifficultyIncreased = 0;
	int DaysSinceScoreChecked = 0;
	int GameScoreSincePreviousCheck = 0;
	

};