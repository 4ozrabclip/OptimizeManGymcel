// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/PlayModeBaseWidget_OM.h"
#include "ExerciseInteractWidget_OM.generated.h"

class USlotsMinigame_OM;
class UMinigamesBase_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UExerciseInteractWidget_OM : public UPlayModeBaseWidget_OM
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnPlayModeChanged(EPlayModes InPlayMode);
	


	virtual void OnExitButtonClicked() override;


public:
	UPROPERTY(meta = (BindWidget))
	UMinigamesBase_OM* Minigame;

	
};

