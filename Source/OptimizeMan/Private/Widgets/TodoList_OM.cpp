// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TodoList_OM.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Utils/GameInstance_OM.h"
#include "Utils/TodoManagementSubsystem.h"

void UTodoList_OM::NativePreConstruct()
{
	Super::NativePreConstruct();

	Task1->SetText(FText::FromString(""));
	Task2->SetText(FText::FromString(""));
	Task3->SetText(FText::FromString(""));
	Task4->SetText(FText::FromString(""));

	Task1CheckBox->SetVisibility(ESlateVisibility::Hidden);
	Task2CheckBox->SetVisibility(ESlateVisibility::Hidden);
	Task3CheckBox->SetVisibility(ESlateVisibility::Hidden);
	Task4CheckBox->SetVisibility(ESlateVisibility::Hidden);
}
 
void UTodoList_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (UTodoManagementSubsystem* TodoManagement = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>()))
	{
		FString Task1String = FString::Format(TEXT("{0}"), {TodoManagement->GetTodoName(0)});
		FString Task2String = FString::Format(TEXT("{0}"), {TodoManagement->GetTodoName(1)});
		FString Task3String = FString::Format(TEXT("{0}"), {TodoManagement->GetTodoName(2)});
		FString Task4String = FString::Format(TEXT("{0}"), {TodoManagement->GetTodoName(3)});
		
		Task1->SetText(FText::FromString(Task1String));
		Task2->SetText(FText::FromString(Task2String));
		Task3->SetText(FText::FromString(Task3String));
		Task4->SetText(FText::FromString(Task4String));

		TArray<FTodoItem>& CurrentTodos = TodoManagement->GetCurrentTodoArray();

		if (CurrentTodos.IsValidIndex(0))
		{
			Task1CheckBox->SetVisibility(ESlateVisibility::HitTestInvisible);
			if (CurrentTodos[0].bIsCompleted)
			{
				Task1CheckBox->SetCheckedState(ECheckBoxState::Checked);
			}
			else
			{
				Task1CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
			}
		}
		if (CurrentTodos.IsValidIndex(1))
		{
			Task2CheckBox->SetVisibility(ESlateVisibility::HitTestInvisible);
			if (CurrentTodos[1].bIsCompleted)
			{
				Task2CheckBox->SetCheckedState(ECheckBoxState::Checked);
			}
			else
			{
				Task2CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
			}
		}
		if (CurrentTodos.IsValidIndex(2))
		{
			Task3CheckBox->SetVisibility(ESlateVisibility::HitTestInvisible);
			if (CurrentTodos[2].bIsCompleted)
			{
				Task3CheckBox->SetCheckedState(ECheckBoxState::Checked);
			}
			else
			{
				Task3CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
			}
		}
		if (CurrentTodos.IsValidIndex(3))
		{
			Task4CheckBox->SetVisibility(ESlateVisibility::HitTestInvisible);
			if (CurrentTodos[3].bIsCompleted)
			{
				Task4CheckBox->SetCheckedState(ECheckBoxState::Checked);
			}
			else
			{
				Task4CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
			}
		}
	}
}