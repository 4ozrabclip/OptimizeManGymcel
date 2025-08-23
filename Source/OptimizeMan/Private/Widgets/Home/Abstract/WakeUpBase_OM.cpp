// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Home/Abstract/WakeUpBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
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
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is null in WakeUpBase"));
		return;
	}


	TodoManager = GameInstance->GetSubsystem<UTodoManagementSubsystem>();
	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("TodoManager is null in WakeUpBase"));
		return;
	}

	if (const APawn* OwningPawn = GetOwningPlayerPawn())
	{
		NotificationAudio = Cast<UNotificationAudio_OM>(
			OwningPawn->GetComponentByClass(UNotificationAudio_OM::StaticClass()));
	}

	pc = Cast<APlayerController_OM>(GetOwningPlayer());
	


	InitializeTaskOptions();
	CurrentButtonStyle = OriginalStyle_1;
	OpenWindow(FName("MainWindow"));
}

void UWakeUpBase_OM::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UWakeUpBase_OM::InitWindowsArray()
{
	Super::InitWindowsArray();
	
	TArray<FFocusableWidgetStruct> FocusableButtons = {
		MakeButton(TaskOptionButton, TaskOptionButton->GetStyle()),
		MakeButton(TaskOptionButton_1, TaskOptionButton_1->GetStyle()),
		MakeButton(TaskOptionButton_2, TaskOptionButton_2->GetStyle()),
		MakeButton(TaskOptionButton_3, TaskOptionButton_3->GetStyle()),
		MakeButton(TaskOptionButton_4, TaskOptionButton_4->GetStyle()),
	};
	
	FUserInterfaceWindow MainWindow;
	MainWindow.WindowName = FName("MainWindow");
	MainWindow.Window = MainCanvas;
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

	TaskOptions.Empty();
	
	TaskOptions.Add(FTaskOptionData(TaskOptionPanel_0, TaskOptionButton, TaskOption, TaskOptionDesc, OriginalStyle_1, CheckedStyle_1));
	TaskOptions.Add(FTaskOptionData(TaskOptionPanel_1, TaskOptionButton_1, TaskOption_1, TaskOptionDesc_1, OriginalStyle_2, CheckedStyle_2));
	TaskOptions.Add(FTaskOptionData(TaskOptionPanel_2, TaskOptionButton_2, TaskOption_2, TaskOptionDesc_2, OriginalStyle_1, CheckedStyle_1));
	TaskOptions.Add(FTaskOptionData(TaskOptionPanel_3, TaskOptionButton_3, TaskOption_3, TaskOptionDesc_3, OriginalStyle_2, CheckedStyle_2));
	TaskOptions.Add(FTaskOptionData(TaskOptionPanel_4, TaskOptionButton_4, TaskOption_4, TaskOptionDesc_4, OriginalStyle_1, CheckedStyle_1));
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
	if (!TodoManager)
		TodoManager = GameInstance->GetSubsystem<UTodoManagementSubsystem>();

	if (TodoManager)
	{
		TodoManager->ProcessPotentialTodos();
		AssignOptionsToWidget();
	}
	
}


void UWakeUpBase_OM::HandleOptionSelected(const int InOption)
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;
	
	if (!TodoManager)
		TodoManager = GameInstance->GetSubsystem<UTodoManagementSubsystem>();
	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("cl(WakeUpBase), fn(HandleOptionSelected): Cant get Todo Manager."));
		return;
	}
	if (!TaskOptions.IsValidIndex(InOption)) return;
	if (!TodoManager->GetPotentialTodos().IsValidIndex(InOption)) return;

	FTaskOptionData& Opt = TaskOptions[InOption];

	
	if (!Opt.bIsSelected)
	{
		if (TodoManager->GetCurrentTodoArray().Num() >= 3)
			return;
		Opt.bIsSelected = true;
		Opt.Button->SetStyle(Opt.SelectedStyle);
		TodoManager->AddToCurrentTodos(TodoManager->GetPotentialTodos()[InOption].Name);
		if (NotificationAudio) NotificationAudio->PlayWritingSound();
	}
	else
	{
		Opt.bIsSelected = false;
		Opt.Button->SetStyle(Opt.OriginalStyle);
		TodoManager->RemoveFromCurrentTodos(TodoManager->GetPotentialTodos()[InOption].Name);
		if (NotificationAudio) NotificationAudio->PlayCrossingOutSound();
	}
	

	
	UpdateFakeTodoList();
}


void UWakeUpBase_OM::UpdateFakeTodoList()
{
	if (!TodoManager) return;
	if (TodoManager->GetCurrentTodoArray().Num() == 3)
	{
		if (pc)
			pc->ShowExitButton();
	}
	else
	{
		if (pc)
			pc->ShowExitButton(true);
		
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

	const int32 NumItems = FMath::Min(TaskOptions.Num(), Options.Num());

	for (int32 i = 0; i < NumItems; ++i)
	{
		const bool bValid = Options.IsValidIndex(i) && TaskOptions.IsValidIndex(i);
		if (bValid)
		{
			FTaskOptionData& Opt = TaskOptions[i];
			Opt.Panel->SetVisibility(ESlateVisibility::Visible);
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
	
	for (int32 i = NumItems; i < TaskOptions.Num(); ++i)
	{
		TaskOptions[i].Panel->SetVisibility(ESlateVisibility::Collapsed);
	}
}