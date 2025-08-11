// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Home/Concrete/WakeUpTutorial_OM.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Overlay.h"
#include "Game/GMB/BedroomGameModeBase_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

UWakeUpTutorial_OM::UWakeUpTutorial_OM(const FObjectInitializer& ObjectInitializer)
{
	SetIsFocusable(true);
}

void UWakeUpTutorial_OM::NativeConstruct()
{
	Super::NativeConstruct();
	TaskOptionPanel_0->SetVisibility(ESlateVisibility::Visible);
	TaskOptionPanel_1->SetVisibility(ESlateVisibility::Visible);
	TaskOptionPanel_2->SetVisibility(ESlateVisibility::Visible);
	TaskOptionPanel_3->SetVisibility(ESlateVisibility::Visible);
	TaskOptionPanel_4->SetVisibility(ESlateVisibility::Visible);
	SetTodoOptions();
	UpdateFakeTodoList();
	InitiateTutorialSequence();
	CurrentTutorialStep = 0;
	bWaitingForInput = false;
}

void UWakeUpTutorial_OM::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

void UWakeUpTutorial_OM::InitiateTutorialSequence()
{
	TodoLisTut_Overlay->SetVisibility(ESlateVisibility::Visible);
	ChooseTasksTut_Overlay->SetVisibility(ESlateVisibility::Visible);
	PlayTutorialAnimation(TutPart1);

	
}

void UWakeUpTutorial_OM::PlayTutorialAnimation(UWidgetAnimation* InAnimationPart)
{
	if (!InAnimationPart) return;

	GetWorld()->GetTimerManager().ClearTimer(Handle);
	
	PlayAnimation(InAnimationPart, 0.f, 1);
	float Duration = InAnimationPart->GetEndTime();

	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UWakeUpTutorial_OM::PlayContPrompt, Duration, false);
}
void UWakeUpTutorial_OM::PlayContPrompt()
{
	bWaitingForInput = true;
	
	switch (CurrentTutorialStep)
	{
	case 0:
		{
			if (TutPart1_Cont)
				PlayAnimation(TutPart1_Cont, 0.f, 0);
			break;
		}
	case 1:
		{
			if (TutPart2_Cont)
				PlayAnimation(TutPart2_Cont, 0.f, 0);
			break;
		}
	case 2:
		{
			if (TutPart3_Cont)
				PlayAnimation(TutPart3_Cont, 0.f, 0);
			break;
		}
	case 3:
		{
			if (TutPart4_Cont)
				PlayAnimation(TutPart4_Cont, 0.f, 0);
			break;
		}
	default:
		break;
	}
}
void UWakeUpTutorial_OM::AdvanceTutorial()
{
	if (!bWaitingForInput) return;

	bWaitingForInput = false;
	StopAllAnimations();
	CurrentTutorialStep++;
	switch (CurrentTutorialStep)
	{
		case 1:
			{
				PlayTutorialAnimation(TutPart2);
				break;
			}
		case 2:
			{
				PlayTutorialAnimation(TutPart3);
				break;
			}
		case 3:
			{
				PlayTutorialAnimation(TutPart4);
				break;
			}
		default:
			{
				FinishTutorial();
				break;
			}
	}
}
void UWakeUpTutorial_OM::FinishTutorial()
{

	TodoLisTut_Overlay->SetVisibility(ESlateVisibility::Hidden);
	ChooseTasksTut_Overlay->SetVisibility(ESlateVisibility::Hidden);

	
	ExitButton->SetVisibility(ESlateVisibility::Visible);
}

void UWakeUpTutorial_OM::OnExitButtonClicked()
{
	Super::OnExitButtonClicked();

	if (TodoManager->GetCurrentTodoArray().Num() < 3) return;
	
	if (ABedroomGameModeBase_OM* Gm = Cast<ABedroomGameModeBase_OM>(GetWorld()->GetAuthGameMode()))
	{
		Gm->TutorialDay();
	}
}


FReply UWakeUpTutorial_OM::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (bWaitingForInput)
	{
		AdvanceTutorial(); 
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply UWakeUpTutorial_OM::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bWaitingForInput)
	{
		AdvanceTutorial(); 
		return FReply::Handled();
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
