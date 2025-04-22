// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/Dates.h"
#include "Structs/GameSettings.h"
#include "Structs/PlayerData.h"
#include "Structs/RandomEvents.h"
#include "GameInstance_OM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDarkModeToggled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAudioSettingsChanged,
												float, InMaster, float, InVoice,
												float, InMusic, float, InNotifications,
												float, InSfx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualitySettingsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEmotionalStateChanged, EPlayerEmotionalStates, NewState);

class APoster_OM;
UCLASS(BlueprintType)
class OPTIMIZEMAN_API UGameInstance_OM : public UGameInstance
{
	GENERATED_BODY()
public:
	void FirstDay();
	virtual void Init() override;
	void SetPosterAsOwned(const int PosterIndex, const FString& PosterType);
	void InitializePostersOwned();
	void InitializeGameSettings();
	void InitializePlayerData();

	UFUNCTION(Category = "Save System")
	void ResetAllSaves();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAudioSettingsChanged OnAudioSettingsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQualitySettingsChanged OnQualitySettingsChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDarkModeToggled OnDarkModeToggled;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEmotionalStateChanged OnEmotionalStateChanged;
	
	UPROPERTY(BlueprintReadWrite)
	FDayInfo DayInfo;

	UPROPERTY(BlueprintReadWrite)
	FPlayerData PlayerData;
	
	UPROPERTY(BlueprintReadWrite)
	FGameSettings GameSettings;

	UPROPERTY(BlueprintReadWrite)
	FRandomEvents RandomEvents;

	UFUNCTION(BlueprintCallable)
	void DarkModeToggle();

	UFUNCTION(BlueprintCallable)
	bool GetDarkMode() const { return GameSettings.bDarkMode; }

	UFUNCTION(BlueprintCallable)
	void SetDarkMode(const bool InDarkMode);

	UFUNCTION(BlueprintCallable)
	void SetCurrentEmotionalState(const EPlayerEmotionalStates NewState);
	

	UFUNCTION(BlueprintCallable)
	FGameSettings& GetGameSettings() { return GameSettings; }

	UFUNCTION()
	void SetAudioSettings(const float InMaster, const float InVoice, const float InMusic, const float InNotification, const float InSfx);

	UFUNCTION(BlueprintCallable)
	FPlayerData& GetPlayerData();

	UFUNCTION(BlueprintCallable)
	FRandomEvents& GetRandomEvents() { return RandomEvents; }

	UFUNCTION(BlueprintCallable)
	TMap<ERandomEvents, bool> GetRandomEventsWitnessedMap() { return RandomEvents.RandomEventsWitnessedMap; }

	UFUNCTION(BlueprintCallable)
	void SetRandomEventAsWitnessed(const ERandomEvents InRandomEvent, const bool InWitnessed);

	UFUNCTION(BlueprintCallable)
	FDayInfo& GetDayInfo() { return DayInfo; }
	
	void IncrementMonth();

	UFUNCTION(BlueprintPure)
	FString GetCurrentDayName() const;

	UFUNCTION(BlueprintPure)
	int32 GetDayNumber() const;

	UFUNCTION()
	EMonth GetCurrentMonth() const { return DayInfo.CurrentMonth; };

	UFUNCTION(BlueprintCallable)
	void IncrementDay();

	UFUNCTION(BlueprintCallable)
	void HandleDayEvents();
	
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
	

	UFUNCTION()
	void Payday(const int InMoney);

	TArray<bool> GetOwnedWaifuPosters() { return bOwnsWaifuPosters;}
	TArray<bool> GetOwnedChadPosters() { return bOwnsChadPosters;}
	


protected:
	UPROPERTY()
	class UTodoManagementSubsystem* TodoManagement;

	
	TArray<bool> bOwnsWaifuPosters;
	TArray<bool> bOwnsChadPosters;





public:

	
private:
	bool bHasBeenToGymToday;
	bool bHasOpenedTodoListInitial;
	bool bHasOpenedPauseMenuInitial;
	bool bHasInteractedInitial;
	

};