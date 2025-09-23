// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Home/Concrete/WakeUpTutorial_OM.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Game/GMB/BedroomGameModeBase_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

UWakeUpTutorial_OM::UWakeUpTutorial_OM(const FObjectInitializer& ObjectInitializer)
{
	SetIsFocusable(true);
}

void UWakeUpTutorial_OM::NativeConstruct()
{
	Super::NativeConstruct();
	ensureMsgf(TaskOptionPanel_0, TEXT("TaskOptionPanel_0 is null in WakeUpTutorial"));
	ensureMsgf(TaskOptionPanel_1, TEXT("TaskOptionPanel_1 is null in WakeUpTutorial"));
	ensureMsgf(TaskOptionPanel_2, TEXT("TaskOptionPanel_2 is null in WakeUpTutorial"));
	ensureMsgf(TaskOptionPanel_3, TEXT("TaskOptionPanel_3 is null in WakeUpTutorial"));
	ensureMsgf(TaskOptionPanel_4, TEXT("TaskOptionPanel_4 is null in WakeUpTutorial"));

	if (TaskOptionPanel_0) TaskOptionPanel_0->SetVisibility(ESlateVisibility::Visible);
	if (TaskOptionPanel_1) TaskOptionPanel_1->SetVisibility(ESlateVisibility::Visible);
	if (TaskOptionPanel_2) TaskOptionPanel_2->SetVisibility(ESlateVisibility::Visible);
	if (TaskOptionPanel_3) TaskOptionPanel_3->SetVisibility(ESlateVisibility::Visible);
	if (TaskOptionPanel_4) TaskOptionPanel_4->SetVisibility(ESlateVisibility::Visible);

	SetTodoOptions();
	InitiateTutorialSequence();

	CurrentTutorialStep = 0;
	bWaitingForInput = false;
}

void UWakeUpTutorial_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	/*UE_LOG(LogTemp, Warning, TEXT("%s"),
		Welcome_Text->GetVisibility() == ESlateVisibility::Hidden ?
		TEXT("Hidden") : TEXT("Not Hidden"));*/
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

	if (IsValid(InAnimationPart))
		PlayAnimation(InAnimationPart, 0.f, 1);
	float Duration = InAnimationPart->GetEndTime();

	GetWorld()->GetTimerManager().SetTimer(Handle, [this]()
	{
		if (!IsValid(this) || !IsValid(TutPart1)) return;
		PlayContPrompt();
	}, Duration, false);
}
void UWakeUpTutorial_OM::PlayContPrompt()
{
	bWaitingForInput = true;
	
	switch (CurrentTutorialStep)
	{
	case 0:
		{
			if (IsValid(TutPart1_Cont))
				PlayAnimation(TutPart1_Cont, 0.f, 0);
			break;
		}
	default:
		break;
	}
}

void UWakeUpTutorial_OM::HandleOptionSelected(int InOption)
{
	
	if (TodoLisTut_Overlay->GetVisibility() != ESlateVisibility::Hidden)
	{
		TodoLisTut_Overlay->SetVisibility(ESlateVisibility::Hidden);
	}
	Super::HandleOptionSelected(InOption);
}

void UWakeUpTutorial_OM::AdvanceTutorial()
{
	if (!bWaitingForInput) return;

	bWaitingForInput = false;
	StopAllAnimations();
	CurrentTutorialStep++;

	FWidgetAnimationDynamicEvent Delegate;
	Delegate.BindDynamic(this, &UWakeUpTutorial_OM::FinishTutorial);
	BindToAnimationFinished(TutPart1_Cont, Delegate);

}
void UWakeUpTutorial_OM::FinishTutorial()
{
	GetWorld()->GetTimerManager().ClearTimer(Handle);
	
	Welcome_Text->SetVisibility(ESlateVisibility::Hidden);
	Welcome_Text_1->SetVisibility(ESlateVisibility::Hidden);
	Welcome_Text_2->SetVisibility(ESlateVisibility::Hidden);
	PressAnyKey_Text->SetVisibility(ESlateVisibility::Hidden);


	PleaseChooseTasksTut_Text->SetVisibility(ESlateVisibility::HitTestInvisible);
	ChooseTasksTut_Overlay->SetVisibility(ESlateVisibility::Hidden);
	
}

void UWakeUpTutorial_OM::OnExitButtonClicked()
{
	if (auto* TodoManager = GetTodoManagerSafe())
	{
		if (TodoManager->GetCurrentTodoArray().Num() < 3)
			return;

		if (ABedroomGameModeBase_OM* Gm = Cast<ABedroomGameModeBase_OM>(GetWorld()->GetAuthGameMode()))
			Gm->TutorialDay();
	
	}

	
	Super::OnExitButtonClicked();
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
