// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "WakeUpBase_OM.generated.h"

class UCanvasPanel;
class UNotificationAudio_OM;
class UButton;
class UTextBlock;
class UGridPanel;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FTaskOptionData
{
	GENERATED_BODY()

	FTaskOptionData() :
	Panel(nullptr),
	Button(nullptr),
	Title(nullptr),
	Description(nullptr)
	{}

	FTaskOptionData(UGridPanel* InPanel, UButton* InButton, UTextBlock* InTitle, UTextBlock* InDescription, FButtonStyle InOriginalStyle, FButtonStyle InSelectedStyle) :
	Panel(InPanel),
	Button(InButton),
	Title(InTitle),
	Description(InDescription),
	OriginalStyle(InOriginalStyle),
	SelectedStyle(InSelectedStyle)
	{}
	
	UPROPERTY()
	UGridPanel* Panel;

	UPROPERTY()
	UButton* Button;

	UPROPERTY()
	UTextBlock* Title;

	UPROPERTY()
	UTextBlock* Description;

	UPROPERTY()
	bool bIsSelected = false;

	UPROPERTY()
	FButtonStyle OriginalStyle;
	
	UPROPERTY()
	FButtonStyle SelectedStyle;
};
UCLASS(Abstract)
class OPTIMIZEMAN_API UWakeUpBase_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void OnExitButtonClicked() override;
	virtual void InitWindowsArray() override;
	virtual void SetTodoOptions();
	
	void InitializeTaskOptions();
	
	virtual void AssignOptionsToWidget();
	virtual void HandleOptionSelected(int InOption);

	UFUNCTION()
	virtual void ExitButtonWakeUpClicked() { OnExitButtonClicked();};
	

	
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
	virtual void UpdateFakeTodoList();



	/** Helper funcs **/
	UTodoManagementSubsystem* GetTodoManagerSafe() const;

protected:


	UPROPERTY()
	APlayerController_OM* pc;
	
	UPROPERTY()
	TArray<FTaskOptionData> TaskOptions;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainCanvas;
	

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
	

	UPROPERTY()
	UNotificationAudio_OM* NotificationAudio;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Styles")
	FButtonStyle OriginalStyle_1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Styles")
	FButtonStyle OriginalStyle_2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Styles")
	FButtonStyle CheckedStyle_1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Styles")
	FButtonStyle CheckedStyle_2;

};
