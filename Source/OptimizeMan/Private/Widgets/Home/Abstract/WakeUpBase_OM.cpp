// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Home/Abstract/WakeUpBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Game/GMB/BedroomGameModeBase_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

void UWakeUpBase_OM::NativeConstruct()
{
	Super::NativeConstruct();

	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("TodoManager is null.  Cast failed"));
		return;
	}
	
	NotificationAudio = Cast<UNotificationAudio_OM>(Player->GetComponentByClass(UNotificationAudio_OM::StaticClass()));
	ExitButton->SetVisibility(ESlateVisibility::Hidden);
	
	InitializeTaskOptions();

	CurrentButtonStyle = OriginalStyle_1;

	OpenWindow(FName("MainWindow"));
}

void UWakeUpBase_OM::InitWindowsArray()
{
	Super::InitWindowsArray();
	
	TArray<FFocusableWidgetStruct> FocusableButtons = {
		MakeButton(TaskOptionButton, OriginalStyle_1),
		MakeButton(TaskOptionButton_1, OriginalStyle_2),
		MakeButton(TaskOptionButton_2, OriginalStyle_1),
		MakeButton(TaskOptionButton_3, OriginalStyle_2),
		MakeButton(TaskOptionButton_4, OriginalStyle_1),
		MakeButton(ExitButton, ExitButton->GetStyle()),
	};
	
	FUserInterfaceWindow MainWindow;
	MainWindow.WindowName = FName("MainWindow");
	MainWindow.Window = MainCanvas;
	MainWindow.bIsOpen = true;
	MainWindow.FocusableContent = FocusableButtons;
	
	Windows.Add(MainWindow);

}

void UWakeUpBase_OM::InitializeTaskOptions()
{
	TaskOptionButton->SetIsEnabled(true);
	TaskOptionButton_1->SetIsEnabled(true);
	TaskOptionButton_2->SetIsEnabled(true);
	TaskOptionButton_3->SetIsEnabled(true);
	TaskOptionButton_4->SetIsEnabled(true);
	
	TaskOptions.Add({TaskOptionPanel_0, TaskOptionButton, TaskOption, TaskOptionDesc, false, OriginalStyle_1, CheckedStyle_1});
	TaskOptions.Add({TaskOptionPanel_1, TaskOptionButton_1, TaskOption_1, TaskOptionDesc_1, false, OriginalStyle_2, CheckedStyle_2});
	TaskOptions.Add({TaskOptionPanel_2, TaskOptionButton_2, TaskOption_2, TaskOptionDesc_2, false, OriginalStyle_1, CheckedStyle_1});
	TaskOptions.Add({TaskOptionPanel_3, TaskOptionButton_3, TaskOption_3, TaskOptionDesc_3, false, OriginalStyle_2, CheckedStyle_2});
	TaskOptions.Add({TaskOptionPanel_4, TaskOptionButton_4, TaskOption_4, TaskOptionDesc_4, false, OriginalStyle_1, CheckedStyle_1});
}

void UWakeUpBase_OM::OnExitButtonClicked()
{
	if (TodoManager->GetCurrentTodoArray().Num() < 3) return;
	if (ABedroomGameModeBase_OM* Gm = Cast<ABedroomGameModeBase_OM>(GetWorld()->GetAuthGameMode()))
		Gm->ShowCurrentDay();
	
	Super::OnExitButtonClicked();
	
}

void UWakeUpBase_OM::SetTodoOptions()
{

	UE_LOG(LogTemp, Warning, TEXT("Set Todo Options Called"));


	TodoManager->ProcessPotentialTodos();

	
	AssignOptionsToWidget();
}


void UWakeUpBase_OM::HandleOptionSelected(const int InOption)
{
	if (!TaskOptions.IsValidIndex(InOption)) return;
	if (!TodoManager->GetPotentialTodos().IsValidIndex(InOption)) return;

	FTaskOptionData& Opt = TaskOptions[InOption];

	

	if (!Opt.bIsSelected)
	{
		if (TodoManager->GetCurrentTodoArray().Num() == 3)
			return;
		Opt.bIsSelected = true;
		Opt.Button->SetStyle(Opt.SelectedStyle);
		TodoManager->AddToCurrentTodos(TodoManager->GetPotentialTodos()[InOption].Name);
		NotificationAudio->PlayWritingSound();
	}
	else
	{
		Opt.bIsSelected = false;
		Opt.Button->SetStyle(Opt.OriginalStyle);
		TodoManager->RemoveFromCurrentTodos(TodoManager->GetPotentialTodos()[InOption].Name);
		NotificationAudio->PlayCrossingOutSound();
	}
	

	
	UpdateFakeTodoList();
}


void UWakeUpBase_OM::UpdateFakeTodoList()
{
	if (TodoManager->GetCurrentTodoArray().Num() == 3)
	{
		ExitButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ExitButton->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (TodoManager->GetCurrentTodoArray().IsValidIndex(0))
	{
		const FString SelectedTaskString = FString::Format(TEXT("- {0}"), {TodoManager->GetCurrentTodoArray()[0].Name});
		SelectedTask->SetText(FText::FromString(SelectedTaskString));
	}
	else
	{
		SelectedTask->SetText(FText::FromString(TEXT("- ")));
	}
	
	if (TodoManager->GetCurrentTodoArray().IsValidIndex(1))
	{
		const FString SelectedTask1String = FString::Format(TEXT("- {0}"), {TodoManager->GetCurrentTodoArray()[1].Name});
		SelectedTask_1->SetText(FText::FromString(SelectedTask1String));
	}
	else
	{
		SelectedTask_1->SetText(FText::FromString(TEXT("- ")));
	}
	
	if (TodoManager->GetCurrentTodoArray().IsValidIndex(2))
	{
		const FString SelectedTask2String = FString::Format(TEXT("- {0}"), {TodoManager->GetCurrentTodoArray()[2].Name});
		SelectedTask_2->SetText(FText::FromString(SelectedTask2String));
	}
	else
	{
		SelectedTask_2->SetText(FText::FromString(TEXT("- ")));
	}
}

void UWakeUpBase_OM::AssignOptionsToWidget()
{

	TArray<FTodoItem>& Options = TodoManager->GetPotentialTodos();

	for (size_t i = 0; i < Options.Num(); ++i)
	{
		const bool bValid = Options.IsValidIndex(i);
		FTaskOptionData& Opt = TaskOptions[i];

		Opt.Panel->SetVisibility(bValid ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

		if (bValid)
		{
			Opt.Title->SetText(FText::FromString(Options[i].Name));
			Opt.Description->SetText(FText::FromString(Options[i].Desc));
			Opt.Button->OnClicked.RemoveAll(this);

			switch (i)
			{
			case 0: Opt.Button->OnClicked.AddDynamic(this, &UWakeUpBase_OM::HandleOption0Selected); break;
			case 1: Opt.Button->OnClicked.AddDynamic(this, &UWakeUpBase_OM::HandleOption1Selected); break;
			case 2: Opt.Button->OnClicked.AddDynamic(this, &UWakeUpBase_OM::HandleOption2Selected); break;
			case 3: Opt.Button->OnClicked.AddDynamic(this, &UWakeUpBase_OM::HandleOption3Selected); break;
			case 4: Opt.Button->OnClicked.AddDynamic(this, &UWakeUpBase_OM::HandleOption4Selected); break;
			default: break;
			}
		}
	}
}