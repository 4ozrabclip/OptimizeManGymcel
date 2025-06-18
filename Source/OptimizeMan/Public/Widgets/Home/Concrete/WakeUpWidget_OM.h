// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "Widgets/Home/Abstract/WakeUpBase_OM.h"
#include "WakeUpWidget_OM.generated.h"

/**
 * 
 */

UCLASS()
class OPTIMIZEMAN_API UWakeUpWidget_OM : public UWakeUpBase_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	virtual void OnExitButtonClicked() override;

	
	void SetTodoOptions();
	
	void AssignOptionsToWidget();
	void HandleOptionSelected(int InOption);
	
	UFUNCTION()
	void HandleOption0Selected() { HandleOptionSelected(0); }
	
	UFUNCTION()
	void HandleOption1Selected() { HandleOptionSelected(1); }
	UFUNCTION()
	void HandleOption2Selected() { HandleOptionSelected(2); }
	UFUNCTION()
	void HandleOption3Selected() { HandleOptionSelected(3); }
	UFUNCTION()
	void HandleOption4Selected() { HandleOptionSelected(4); }

	UFUNCTION()
	void UpdateFakeTodoList();

protected: // TASK OPTIONS


private:



	
};
