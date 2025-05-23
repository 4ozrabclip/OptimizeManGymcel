// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WakeUpWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/Components/NotificationAudio_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Utils/GameInstance_OM.h"
#include "Utils/TodoManagementSubsystem.h"

void UWakeUpWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("Wake up Construct Called"));
	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("TodoManager is null.  Cast failed"));
		return;
	}

	// NEED TO MAYBE FIGURE OUT HOW YOU WILL REFERENCE THIS COMPONENT COS THERE ARE MULTIPLE UPLAYERAUDIOS ON PLAYER
	
	NotificationAudio = Cast<UNotificationAudio_OM>(Player->GetComponentByClass(UNotificationAudio_OM::StaticClass()));

	TaskOptionPanel_0->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionPanel_1->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionPanel_2->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionPanel_3->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionPanel_4->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionButton->SetIsEnabled(true);
	TaskOptionButton_1->SetIsEnabled(true);
	TaskOptionButton_2->SetIsEnabled(true);
	TaskOptionButton_3->SetIsEnabled(true);
	TaskOptionButton_4->SetIsEnabled(true);
	
	
	
	SetTodoOptions();
	UpdateFakeTodoList();
	
}

void UWakeUpWidget_OM::OnExitButtonClicked()
{
	if (TodoManager->GetCurrentTodoArray().Num() < 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Havent set all todos yet"));
		return;
	}
	Super::OnExitButtonClicked();
}

void UWakeUpWidget_OM::SetTodoOptions()
{

	UE_LOG(LogTemp, Warning, TEXT("Set Todo Options Called"));


	TodoManager->ProcessPotentialTodos();

	
	AssignOptionsToWidget();
}


void UWakeUpWidget_OM::HandleOptionSelected(const int InOption)
{
	TArray<FTodoItem>& Options = TodoManager->GetPotentialTodos();

	if (!Options.IsValidIndex(InOption))
	{
		UE_LOG(LogTemp, Error, TEXT("OPTION INDEX IS INVALID FOR POTENTIAL TODOS"));
		return;
	}

	switch (InOption)
	{
	case 0:
		TaskOptionButton->SetIsEnabled(false);
		break;
	case 1:
		TaskOptionButton_1->SetIsEnabled(false);
		break;
	case 2:
		TaskOptionButton_2->SetIsEnabled(false);
		break;
	case 3:
		TaskOptionButton_3->SetIsEnabled(false);
		break;
	case 4:
		TaskOptionButton_4->SetIsEnabled(false);
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Option Selected"));
	}
		
	TodoManager->AddToCurrentTodos(Options[InOption].Name);
	NotificationAudio->PlayWritingSound();
	
	UpdateFakeTodoList();
}


void UWakeUpWidget_OM::UpdateFakeTodoList()
{
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

void UWakeUpWidget_OM::AssignOptionsToWidget()
{
	if (!TaskOption || !TaskOptionButton)
	{
		UE_LOG(LogTemp, Error, TEXT("Task option button or text is null"));
		return;
	}

	TArray<FTodoItem>& Options = TodoManager->GetPotentialTodos();
	
	if (Options.IsValidIndex(0))
	{
		TaskOptionPanel_0->SetVisibility(ESlateVisibility::Visible);
		
		TaskOption->SetText(FText::FromString(Options[0].Name));
		TaskOptionDesc->SetText(FText::FromString(Options[0].Desc));
		
		TaskOptionButton->OnClicked.RemoveAll(this);
		TaskOptionButton->OnClicked.AddDynamic(this, &UWakeUpWidget_OM::HandleOption0Selected);
	}
	else
	{
		TaskOption->SetText(FText::FromString(""));
		TaskOptionDesc->SetText(FText::FromString(""));
	}
	
	if (Options.IsValidIndex(1))
	{
		TaskOptionPanel_1->SetVisibility(ESlateVisibility::Visible);
		
		TaskOption_1->SetText(FText::FromString(Options[1].Name));
		TaskOptionDesc_1->SetText(FText::FromString(Options[1].Desc));

		TaskOptionButton_1->OnClicked.RemoveAll(this);
		TaskOptionButton_1->OnClicked.AddDynamic(this, &UWakeUpWidget_OM::HandleOption1Selected);
	}
	else
	{
		TaskOption_1->SetText(FText::FromString(""));
		TaskOptionDesc_1->SetText(FText::FromString(""));
	}
	
	if (Options.IsValidIndex(2))
	{
		TaskOptionPanel_2->SetVisibility(ESlateVisibility::Visible);
		
		TaskOption_2->SetText(FText::FromString(Options[2].Name));
		TaskOptionDesc_2->SetText(FText::FromString(Options[2].Desc));
		
		TaskOptionButton_2->OnClicked.RemoveAll(this);
		TaskOptionButton_2->OnClicked.AddDynamic(this, &UWakeUpWidget_OM::HandleOption2Selected);
	}
	else
	{
		TaskOption_2->SetText(FText::FromString(""));
		TaskOptionDesc_2->SetText(FText::FromString(""));
	}
	
	if (Options.IsValidIndex(3))
	{
		TaskOptionPanel_3->SetVisibility(ESlateVisibility::Visible);
		
		TaskOption_3->SetText(FText::FromString(Options[3].Name));
		TaskOptionDesc_3->SetText(FText::FromString(Options[3].Desc));

		TaskOptionButton_3->OnClicked.RemoveAll(this);
		TaskOptionButton_3->OnClicked.AddDynamic(this, &UWakeUpWidget_OM::HandleOption3Selected);
	}
	else
	{
		TaskOption_3->SetText(FText::FromString(""));
		TaskOptionDesc_3->SetText(FText::FromString(""));
	}
	
	if (Options.IsValidIndex(4))
	{
		TaskOptionPanel_4->SetVisibility(ESlateVisibility::Visible);
		
		TaskOption_4->SetText(FText::FromString(Options[4].Name));
		TaskOptionDesc_4->SetText(FText::FromString(Options[4].Desc));
		
		TaskOptionButton_4->OnClicked.RemoveAll(this);
		TaskOptionButton_4->OnClicked.AddDynamic(this, &UWakeUpWidget_OM::HandleOption4Selected);
	}
	else
	{
		TaskOption_4->SetText(FText::FromString(""));
		TaskOptionDesc_4->SetText(FText::FromString(""));
	}
}