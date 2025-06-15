// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "WakeUpWidget_OM.generated.h"

class UGridPanel;
/**
 * 
 */
class UButton;
class UTextBlock;
UCLASS()
class OPTIMIZEMAN_API UWakeUpWidget_OM : public UMinigameBaseWidget_OM
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

	UPROPERTY(meta = (BindWidget))
	UGridPanel* TaskOptionPanel_0;
	UPROPERTY(meta = (BindWidget))
	UButton* TaskOptionButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOption;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOptionDesc;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* TaskOptionPanel_1;
	UPROPERTY(meta = (BindWidget))
	UButton* TaskOptionButton_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOption_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOptionDesc_1;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* TaskOptionPanel_2;
	UPROPERTY(meta = (BindWidget))
	UButton* TaskOptionButton_2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOption_2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOptionDesc_2;
	

	UPROPERTY(meta = (BindWidget))
	UGridPanel* TaskOptionPanel_3;
	UPROPERTY(meta = (BindWidget))
	UButton* TaskOptionButton_3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOption_3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOptionDesc_3;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* TaskOptionPanel_4;
	UPROPERTY(meta = (BindWidget))
	UButton* TaskOptionButton_4;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOption_4;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TaskOptionDesc_4;
	


	// Selected tasks (fake todo list)
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedTask;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedTask_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedTask_2;


private:
	UPROPERTY()
	class UTodoManagementSubsystem* TodoManager;

	UPROPERTY()
	class UNotificationAudio_OM* NotificationAudio;
	
};
