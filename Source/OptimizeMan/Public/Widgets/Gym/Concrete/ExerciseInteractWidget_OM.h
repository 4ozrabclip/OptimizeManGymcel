// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/ExerciseData.h"
#include "Widgets/Both/Abstract/PlayModeBaseWidget_OM.h"
#include "ExerciseMinigameWidget_OM.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinigameResult, EMinigameResult, Result);

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
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void OnExitButtonClicked() override;
	

	UFUNCTION()
	virtual void SetWorkoutState(EWorkoutStates NewWorkoutState) { CurrentWorkoutState = NewWorkoutState; };

	UFUNCTION()
	virtual void CheckAndSetStyles() {}

		
	UFUNCTION()
	void OnPlayModeChanged(EPlayModes InPlayMode);


	/** Delegates / Events **/
	FOnMinigameResult OnMinigameResult;

protected:
	EWorkoutStates CurrentWorkoutState;
	FTimerHandle RepTimeHandle;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MiniGameClickButton;

		
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NotificationText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BloodSplatter;

	FTimerHandle TutorialDelayHandle;


	bool bDoingRep = false;
	bool bHasWorkedOutInitial = true;

	

	
};

