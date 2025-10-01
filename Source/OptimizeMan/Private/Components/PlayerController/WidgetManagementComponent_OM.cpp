// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/PlayerController/WidgetManagementComponent_OM.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/Both/Concrete/GamePointsHud_OM.h"
#include "Widgets/Both/Concrete/InteractWidget_OM.h"
#include "Widgets/Both/Concrete/TodoCompletePopupWidget_OM.h"
#include "Widgets/Both/Concrete/TutorialWidget_OM.h"
#include "Widgets/Both/Concrete/YouDiedWidget_OM.h"

UWidgetManagementComponent_OM::UWidgetManagementComponent_OM()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWidgetManagementComponent_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWidgetManagementComponent_OM::PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn)
{
	RemoveAllActiveWidgets();

	TSubclassOf<UPlayModeBaseWidget_OM> WidgetToCreateClass = nullptr;

	WidgetToCreateClass = *PlayModeWidgets.Find(CurrentPlayMode);

	
	CurrentPlayModeWidgetInstance = CreateWidget<UPlayModeBaseWidget_OM>(this, WidgetToCreateClass);
	if (!CurrentPlayModeWidgetInstance) return;

	ActiveWidgets.Add(CurrentPlayModeWidgetInstance);
	
	if (!CurrentPlayModeWidgetInstance) return;
	if (CurrentPlayModeWidgetInstance->IsInViewport()) return;
	
	if (bHasFadeIn)
	{
		FadeWidgets(nullptr, CurrentPlayModeWidgetInstance);
	}
	else 
	{
		CurrentPlayModeWidgetInstance->AddToViewport(2);
	}
}

void UWidgetManagementComponent_OM::SetTutorialWidget(const UTutorialWidget_OM* InTutorialWidget)
{
	if (InTutorialWidget)
	{
		if (TSubclassOf<UPlayModeBaseWidget_OM>* Tut = PlayModeWidgets.Find(EPlayModes::TutorialMode))
		{
			*Tut = InTutorialWidget->GetClass();
		}
	}
}

void UWidgetManagementComponent_OM::SetWorkoutMinigame(EMinigameType InMiniGame)
{
		if (TSubclassOf<UPlayModeBaseWidget_OM>* Minigame = PlayModeWidgets.Find(EPlayModes::WorkoutMode))
		{
			*Minigame = WorkoutMinigames.Find(InMiniGame);
		}
	}
}

void UWidgetManagementComponent_OM::ShowYouDiedWidget()
{
	if (!YouDiedWidget) return;

	if (UYouDiedWidget_OM* YouDiedWidgetPtr = CreateWidget<UYouDiedWidget_OM>(this, YouDiedWidget))
	{
		ShowExitButton(true);

		if (auto* PC = Cast<APlayerController>(GetOwner()))
		{
			PC->DisableInput(PC);
		
			GetWorld()->GetTimerManager().ClearTimer(YouDiedTimer);
			GetWorld()->GetTimerManager().SetTimer(YouDiedTimer, [this, YouDiedWidgetPtr, PC]()
			{
				PC->EnableInput(PC);
				const FInputModeUIOnly Input;
				PC->SetInputMode(Input);
				RemoveAllActiveWidgets();
				YouDiedWidgetPtr->FadeIn();
			}, 3.f, false);
		}
	}
}


void UWidgetManagementComponent_OM::TodoCompletedPopUp()
{
	if (!TodoWidgetPtr)
	{
		if (TodoCompleteWidget)
		{
			TodoWidgetPtr = CreateWidget<UTodoCompletePopupWidget_OM>(this, TodoCompleteWidget);
		}
		if (!TodoWidgetPtr) return;
	}

	if (!TodoWidgetPtr->IsInViewport())
	{
		TodoWidgetPtr->AddToViewport(2);
	}

	constexpr float PopUpTimeAmount = 4.f;

	GetWorld()->GetTimerManager().ClearTimer(TodoPopUpHandle);
	GetWorld()->GetTimerManager().SetTimer(
		TodoPopUpHandle,
		[this]()
		{
			if (TodoWidgetPtr->IsInViewport())
			{
				TodoWidgetPtr->RemoveFromParent();
			}
		},
		PopUpTimeAmount,
		false
	);
}

void UWidgetManagementComponent_OM::RemoveAllActiveWidgets()
{
	if (CurrentPlayModeWidgetInstance && CurrentPlayModeWidgetInstance->IsInViewport())
	{
		CurrentPlayModeWidgetInstance->RemoveFromParent();
		CurrentPlayModeWidgetInstance = nullptr;
	}

	for (UUserWidget* Widget : ActiveWidgets)
	{
		if (Widget && Widget->IsInViewport())
		{
			Widget->RemoveFromParent();
		}
	}

	if (InteractWidgetPtr && InteractWidgetPtr->IsInViewport())
	{
		InteractWidgetPtr->RemoveFromParent();
	}
	
	ActiveWidgets.Empty();


}

void UWidgetManagementComponent_OM::FadeWidgets(UUserWidget* FadeOutWidget, UUserWidget* FadeInWidget)
{
	if (!FadeOutWidget)
		return;
	
	if (!FadeOutWidget->IsInViewport() && !FadeInWidget->IsInViewport())
	{
		FadeInWidget->AddToViewport(2);
		return;
	}
	if (UParentWidget_OM* WidgetParentClass = Cast<UParentWidget_OM>(FadeInWidget))
	{
		GetWorld()->GetTimerManager().SetTimer(
			SetModeWidgetFadeInTimerHandle,
			[this, FadeOutWidget, WidgetParentClass]()
			{
				if (FadeOutWidget->GetRenderOpacity() < 1.f)
				{
					GetWorld()->GetTimerManager().ClearTimer(SetModeWidgetFadeInTimerHandle);
					WidgetParentClass->FadeIn();
				}
			},
		0.016f, 
		true
		);
	}
}

void UWidgetManagementComponent_OM::LoadPersistentHud(const bool bLoad)
{
	if (!PersistentHudPtr)
	{
		if (PersistentHud)
		{
			PersistentHudPtr = CreateWidget<UGamePointsHud_OM>(this, PersistentHud);
		}
		if (!PersistentHudPtr) return;
	}

	if (bLoad)
	{
		if (!PersistentHudPtr->IsInViewport())
		{
			PersistentHudPtr->AddToViewport(3);
		}
	}
	else
	{
		if (PersistentHudPtr->IsInViewport())
		{
			PersistentHudPtr->RemoveFromParent();
		}
	}
}
