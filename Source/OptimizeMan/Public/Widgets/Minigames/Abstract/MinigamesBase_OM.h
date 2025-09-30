// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/MinigameData.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "MinigamesBase_OM.generated.h"


class UImage;
class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinigameResult, EMinigameResult, Result);

class APlayerController_OM;
class APlayerCharacter_OM;
/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API UMinigamesBase_OM : public UParentWidget_OM
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void SetWorkoutState(EWorkoutStates NewWorkoutState) { CurrentWorkoutState = NewWorkoutState; };

	UFUNCTION()
	virtual void CheckAndSetStyles() {}


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
	
	
	UPROPERTY()
	APlayerCharacter_OM* Player;
	UPROPERTY()
	APlayerController_OM* PlayerController;
};
