// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Utils/Structs/ConsumableData.h"
#include "Utils/Structs/Dates.h"
#include "Utils/Structs/GameSettings.h"
#include "Utils/Structs/PlayerData.h"
#include "Utils/Structs/EventAndGPData.h"
#include "Utils/Structs/MinigameData.h"
#include "Utils/Structs/PlayModes.h"
#include "GameInstance_OM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDarkModeToggled, bool, bIsDarkMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioSettingsChanged,
												float, InMaster, float, InVoice,
												float, InMusic, float, InNotifications,
												float, InSfx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualitySettingsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEmotionalStateChanged, EPlayerEmotionalStates, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGymStatsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePointsChanged, int, ChangedPoints);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEgoChanged, float, NewEgo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSexAppealChanged, float, NewSexAppeal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSocialChanged, float, NewSocial);

class APoster_OM;
UCLASS(BlueprintType)
class OPTIMIZEMAN_API UGameInstance_OM : public UGameInstance 
{
	GENERATED_BODY()
	
public: 
	/** Overrides **/
	virtual void Init() override;
	virtual void Shutdown() override;
	

	/** Inits **/
	void InitializePlayerData();
	void InitializePostersOwned();
	void InitializeGameSettings();
	void InitPlayModes();

	void FirstDay();
	void ResetGame();
	void FinishDemo();
	


	/** Getters / Finders **/
	FBodyPartData* FindBodyPart(const EBodyPart& Part, const EBodyPartSide& Side);
	float GetBodyPartStrengthValue(const EBodyPart& Part, const EBodyPartSide& Side);
	float GetBodyPartLeftRightCombinedStrengthValue(const EBodyPart& Part);
	float* GetBodyPartStrengthPtr(const EBodyPart& Part, const EBodyPartSide& Side);



public: //delegates
	/** Delegates **/

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEgoChanged OnEgoChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSocialChanged OnSocialChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSexAppealChanged OnSexAppealChanged;

	
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
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGamePointsChanged OnGamePointsChanged;
	

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Day info")
	FDayInfo DayInfo;


	UPROPERTY(EditDefaultsOnly, Category = "PlayModes")
	TMap<EMiniGameType, FMiniGameData> MiniGameData;
	

public:
//General Non-UFUNCS
	void SetWaveDetails();
	void Check3DayScore();
	void BroadcastNotEnoughPoints();

	/** Events **/
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
	UFUNCTION()
	void SetDayNumber(const int InDayNumber) { DayInfo.DayNumber = InDayNumber;}
	UFUNCTION(BlueprintPure)
	FString GetCurrentDayName() const;
	UFUNCTION(BlueprintCallable)
	FDayInfo& GetDayInfo() { return DayInfo; }
	
	void IncrementMonth();



	
	/** Setters / Adders **/
	void SetPosterAsOwned(const int PosterIndex, const FString& PosterType);
	void SetTempWaveDifficultyMultiplier(const float InMultiplier) { TempWaveDifficultyMultiplier = InMultiplier; }
	void SetBaseDifficultyMultiplier(const float InMultiplier) { BaseDifficultyMultiplier = InMultiplier; }
	void SetHasDonePlayModeInitial(const EPlayModes InPlayMode, const bool InHasDonePlayMode = true);
	void SetHasPlayedMiniGameInitial(const EMiniGameType InMiniGame, const bool InHasPlayedMiniGame = true);
	void SetHasOpenedTodoListInitial(const bool InHasOpenedTodoListInitial) { bHasOpenedTodoListInitial = InHasOpenedTodoListInitial; }
	void SetHasBeenToGymToday(const bool InHasBeenToGymToday) { bHasBeenToGymToday = InHasBeenToGymToday; }
	void SetInnerStatus(const FInnerStatus& InInnerStatus);
	void SetHasOpenedPauseMenuInitial(const bool InHasOpenedPauseMenuInitial) { bHasOpenedPauseMenuInitial = InHasOpenedPauseMenuInitial; }
	void SetHasInteractedInitial(const bool InHasInteractedInitial) { bHasInteractedInitial = InHasInteractedInitial; }
	void SetLookSensitivity(const float InLookSensitivity);
	void SetMoney(const int InMoney)  { InventoryData.Money += InMoney; }
	void SetStat(float& Stat, float Value)
	{
		Stat = FMath::Clamp(Value, -1.f, 1.0f);
	}
	void AddStat(float& Stat, float Value)
	{
		Stat = FMath::Clamp(Stat + Value, -1.f, 1.0f);
	}
	void AddEgo(float InValue)
	{
		InnerStatus.Ego = FMath::Clamp(InnerStatus.Ego + InValue, -1.f, 1.0f);
		OnEgoChanged.Broadcast(InnerStatus.Ego);
	}
	void AddSexAppeal(float InValue)
	{
		InnerStatus.SexAppeal = FMath::Clamp(InnerStatus.SexAppeal + InValue, -1.f, 1.0f);
		OnSexAppealChanged.Broadcast(InnerStatus.SexAppeal);
	}
	void AddSocial(float InValue)
	{
		InnerStatus.Social = FMath::Clamp(InnerStatus.Social + InValue, -1.f, 1.0f);
		OnSocialChanged.Broadcast(InnerStatus.Social);
	}
	void SetPossesion(bool& bPossesable, const bool bInPossesion)
	{
		bPossesable = bInPossesion;
	}
	UFUNCTION()
	void SetTutorialsOn(const bool InEnabled) { GameSettings.bTutorialsOn = InEnabled; }
	UFUNCTION(BlueprintCallable)
	void SetDarkMode(const bool InDarkMode);
	UFUNCTION()
	void SetAudioSettings(const float InMaster, const float InVoice, const float InMusic, const float InNotification, const float InSfx);
	UFUNCTION()
	void SetGymResStats(float& Stat, float Value);
	UFUNCTION(BlueprintCallable)
	void SetRandomEventAsWitnessed(const EEventAndGPData InRandomEvent, const bool InWitnessed);
	UFUNCTION(BlueprintCallable)
	void SetCurrentEmotionalState(const EPlayerEmotionalStates NewState);
	UFUNCTION()
	void AddGymResStats(float& Stat, float Value);
	UFUNCTION()
	void AddGamePoints(const int InPoints);
	
	/** Getters **/
	float GetEgo() const { return InnerStatus.Ego; }
	float GetSexAppeal() const { return InnerStatus.SexAppeal; }
	float GetSocial() const { return InnerStatus.Social; }
	
	bool GetHasPlayedMiniGameInitial(const EMiniGameType InMiniGame);
	float GetBaseDifficultyMultiplier() const { return BaseDifficultyMultiplier; }
	float GetTempWaveDifficultyMultiplier() const { return TempWaveDifficultyMultiplier; }
	float GetDifficultyMultiplier() const { return BaseDifficultyMultiplier * TempWaveDifficultyMultiplier; }
	bool GetHasBeenToGymToday() const { return bHasBeenToGymToday; }
	bool GetCurrentlyOnSteroids() const { return BodyStatus.bCurrentlyOnSteroids; }
	bool GetOwnsSteroids() const { return InventoryData.bOwnsSteroids; }
	bool GetOwnsPreWorkout() const { return InventoryData.bOwnsPreWorkout; }
	int GetMoney() const { return InventoryData.Money; }
	TArray<bool> GetOwnedWaifuPosters() { return bOwnsWaifuPosters;}
	TArray<bool> GetOwnedChadPosters() { return bOwnsChadPosters;}
	
	UFUNCTION(BlueprintCallable) //for use with bedroom door
	bool GetHasOpenedTodoListInitial() const { return bHasOpenedTodoListInitial; }
	UFUNCTION(BlueprintCallable)
	bool GetHasOpenedPauseMenuInitial() const { return bHasOpenedPauseMenuInitial; }
	UFUNCTION(BlueprintCallable)
	bool GetHasInteractedInitial() const { return bHasInteractedInitial; }
	UFUNCTION(BlueprintCallable)
	FGameSettings& GetGameSettings() { return GameSettings; }
	UFUNCTION(BlueprintCallable)
	bool GetDarkMode() const { return GameSettings.bDarkMode; }
	UFUNCTION()
	bool GetTutorialsOn() const { return GameSettings.bTutorialsOn; }
	UFUNCTION(BlueprintCallable)
	FGymResStats& GetGymResStats() { return GymResStats; }
	UFUNCTION()
	FBodyStatus& GetBodyStatus() { return BodyStatus;}
	UFUNCTION(BlueprintCallable)
	FEventAndGPData& GetRandomEvents() { return RandomEvents; }
	UFUNCTION(BlueprintCallable)
	TMap<EEventAndGPData, bool> GetRandomEventsWitnessedMap() { return RandomEvents.RandomEventsWitnessedMap; }
	UFUNCTION()
	FInnerStatus& GetInnerStatus() { return InnerStatus; }
	UFUNCTION(BlueprintCallable)
	EPlayerEmotionalStates GetCurrentEmotionalState() const { return InnerStatus.CurrentEmotionalState; }
	UFUNCTION()
	FInventoryData& GetInventoryData() { return InventoryData; }
	UFUNCTION()
	FGamePointsData& GetGamePointsData() { return GamePointsData; }
	UFUNCTION()
	int GetGamePoints() const { return GamePointsData.GamePoints; }



	
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