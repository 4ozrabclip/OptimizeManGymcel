// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/MinigameData.h"
#include "Widgets/Both/Abstract/PlayModeBaseWidget_OM.h"
#include "ExerciseMinigameWidget_OM.generated.h"


class UExercise_OM;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinigameResult, FMinigameResultData, Result);

class USlotsMinigame_OM;
class UMinigamesBase_OM;
class UImage;
class UTextBlock;
class APlayerController_OM;
class APlayerCharacter_OM;

UCLASS(Abstract)
class OPTIMIZEMAN_API UExerciseMinigameWidget_OM : public UPlayModeBaseWidget_OM
{
	GENERATED_BODY()
protected:
	/** Native Overrides **/
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/** PlayMode Overrides **/
	virtual void OnExitButtonClicked() override;

	/** MiniGame Virtual **/
	virtual void OnMiniGameClick();
	virtual void WorkoutTutorial(float DeltaTime) {};
	UFUNCTION()
	virtual void CheckAndSetStyles() {}

	/** Delegate Bound Functions **/
	UFUNCTION()
	void OnPlayModeChanged(EPlayModes InPlayMode);

	
	/** Getters **/
	bool GetHasPlayedThisMiniGame() const { return bHasPlayedThisMinigame; }
	float GetEnergyLevel() const { return EnergyLevel; }
	/** Setters **/
	void SetLocalEnergyLevel(const float InEnergyLevel) { EnergyLevel = InEnergyLevel; }
	void SetNotificationText() const;
	void SetSetAndRepCountTextBlocks() const;
	UFUNCTION()
	virtual void SetWorkoutState(EWorkoutStates NewWorkoutState) { CurrentWorkoutState = NewWorkoutState; }

	
	virtual void CheckStatsForFrontEnd() {};
	UFUNCTION(BlueprintCallable)
	void NotificationTextPopUp(const FString& InString = "");

	
	/** Delegates / Events **/
	FOnMinigameResult OnMinigameResult;


	/** Class Cache **/
	UPROPERTY()
	UExercise_OM* ExerciseComponent;



	/** MiniGameData **/
	UPROPERTY(EditDefaultsOnly)
	EMiniGameType MiniGameType;
		/** Result Data **/
	FMinigameResultData CurrentMinigameResult;
	EMinigameResult NewResult = EMinigameResult::None;


	/** WorkoutData **/
	EWorkoutStates CurrentWorkoutState;

	
	/** TimerHandles **/
	FTimerHandle TutorialDelayHandle;
	FTimerHandle RepTimeHandle;
	FTimerHandle TextPopUpDelayHandle;

	
	/** Widget UObjects **/
	UPROPERTY(meta = (BindWidget))
	UButton* MiniGameClickButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NotificationText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BloodSplatter;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RepCountTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SetCountTextBlock;

	
private:
	bool bHasPlayedThisMinigame = false;
	float EnergyLevel;


	
};

