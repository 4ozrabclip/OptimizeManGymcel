// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/PlayerController/WidgetManagementComponent_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Blueprint/UserWidget.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "Utils/Static Helpers/Helper.h"
#include "Widgets/Both/Concrete/GamePointsHud_OM.h"
#include "Widgets/Both/Concrete/HintsWidget_OM.h"
#include "Widgets/Both/Concrete/InteractWidget_OM.h"
#include "Widgets/Both/Concrete/TodoCompletePopupWidget_OM.h"
#include "Widgets/Both/Concrete/TutorialWidget_OM.h"
#include "Widgets/Both/Concrete/YouDiedWidget_OM.h"
#include "Widgets/Gym/Concrete/ExerciseMinigameWidget_OM.h"

UWidgetManagementComponent_OM::UWidgetManagementComponent_OM()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWidgetManagementComponent_OM::BeginPlay()
{
	Super::BeginPlay();
	auto* PC = Cast<APlayerController>(GetOwner());
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetManagementComponent: Coudn't Get PC in BeginPlay"));
		return;
	}
	
	auto* PlayerCharacter = Cast<APlayerCharacter_OM>(PC->GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetManagementComponent: Coudn't Get Player Pawn in BeginPlay"));
		return;
	}
	if (auto* ExerciseComponent = PlayerCharacter->GetComponentByClass<UExercise_OM>())
	{
		if (!ExerciseComponent->OnMinigameSelected.IsAlreadyBound(this, &UWidgetManagementComponent_OM::SetWorkoutMinigame))
			ExerciseComponent->OnMinigameSelected.AddDynamic(this, &UWidgetManagementComponent_OM::SetWorkoutMinigame);
	}
	
	if (auto* AbSysComp = Cast<UAbilitySystemComponent_OM>(PlayerCharacter->GetAbilitySystemComponent()))
	{
		if (auto* GymStats = AbSysComp->GetSet<UGymSpecificStats_OM>())
		{
			if (auto MutableStats = const_cast<UGymSpecificStats_OM*>(GymStats))
			{
				if (!MutableStats->OnEnergyEmpty.IsAlreadyBound(this, &UWidgetManagementComponent_OM::ShowYouDiedWidget))
					MutableStats->OnEnergyEmpty.AddDynamic(this, &UWidgetManagementComponent_OM::ShowYouDiedWidget);
			}
		}
	}
	if (auto* TodoManager = Helper::GetTodoManager(this))
	{
		TodoManager->OnTodoComplete.AddDynamic(this, &UWidgetManagementComponent_OM::TodoCompletedPopUp);
	}


	LoadPersistentHud();
}

void UWidgetManagementComponent_OM::PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn)
{
	RemoveAllActiveWidgets();

	TSubclassOf<UPlayModeBaseWidget_OM> WidgetToCreateClass = nullptr;

	WidgetToCreateClass = *PlayModeWidgets.Find(CurrentPlayMode);
	
	CurrentPlayModeWidgetInstance = CreateWidget<UPlayModeBaseWidget_OM>(GetWorld(), WidgetToCreateClass);
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

void UWidgetManagementComponent_OM::WidgetInteraction(
	const TScriptInterface<IInteractableInterface_OM>& InteractedActorInterface)
{
	if (InteractWidgetPtr && InteractWidgetPtr->IsInViewport())
	{
		InteractWidgetPtr->SetText(InteractedActorInterface->GetInteractionWidgetText());
		InteractWidgetPtr->SetVisibility(ESlateVisibility::Visible);
		return; 
	}

	if (const TSubclassOf<UUserWidget> WidgetClass = InteractedActorInterface->GetInteractableWidget())
	{
		InteractWidgetPtr = CreateWidget<UInteractWidget_OM>(GetWorld(), WidgetClass);
		
		InteractWidgetPtr->SetText(InteractedActorInterface->GetInteractionWidgetText());

		if (!InteractWidgetPtr->IsInViewport())
		{
			InteractWidgetPtr->AddToViewport(3);
		}
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
		if (TSubclassOf<UExerciseMinigameWidget_OM>* Ex = WorkoutMinigames.Find(InMiniGame))
		{
			*Minigame = Ex->Get();
		}
	}
}


void UWidgetManagementComponent_OM::ShowYouDiedWidget()
{
	if (!YouDiedWidget) return;

	if (UYouDiedWidget_OM* YouDiedWidgetPtr = CreateWidget<UYouDiedWidget_OM>(GetWorld(), YouDiedWidget))
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

	if (!PersistentHudPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("PersistentHudPtr null"));
		return;
	}
	
	if (!PersistentHudPtr->GetTodoPopupIsVisible())
	{
		PersistentHudPtr->SetTodoCompletePopupVisibility(true);
	}
	
	constexpr float PopUpTimeAmount = 4.f;

	GetWorld()->GetTimerManager().ClearTimer(TodoPopUpHandle);
	GetWorld()->GetTimerManager().SetTimer(
		TodoPopUpHandle,
		[this]()
		{
			if (PersistentHudPtr->GetTodoPopupIsVisible())
			{
				PersistentHudPtr->SetTodoCompletePopupVisibility(false);
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
			PersistentHudPtr = CreateWidget<UGamePointsHud_OM>(GetWorld(), PersistentHud);
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

void UWidgetManagementComponent_OM::ResetUI()
{
	RemoveAllActiveWidgets();

	if (PersistentHudPtr)
	{
		PersistentHudPtr->RemoveFromParent();
		PersistentHudPtr = nullptr;
	}

	if (InteractWidgetPtr)
	{
		InteractWidgetPtr->RemoveFromParent();
		InteractWidgetPtr = nullptr;
	}
}

void UWidgetManagementComponent_OM::ToggleInteractWidgetFromViewport(bool bRemove)
{
	if (!InteractWidgetPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("No interact widget ptr"));
		return;
	}

	if (bRemove)
	{
		InteractWidgetPtr->RemoveFromParent();
		InteractWidgetPtr = nullptr; 
	}
	else
	{
		if (!InteractWidgetPtr->IsInViewport())
		{
			InteractWidgetPtr->AddToViewport(3);
		}
		InteractWidgetPtr->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWidgetManagementComponent_OM::HideUnhideInteractableWidget(bool bHide) const
{
	if (!InteractWidgetPtr) return;

	if (bHide)
	{
		InteractWidgetPtr->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		InteractWidgetPtr->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWidgetManagementComponent_OM::ShowOrHideHint(const FString& HintText, float HintLength, bool HideHint,
                                                   bool RemoveFully)
{
	if (PersistentHudPtr)
		PersistentHudPtr->HintSystem(HintText, HintLength, HideHint, RemoveFully);
}

void UWidgetManagementComponent_OM::HidePersistentHud(bool bHide) const
{
	if (PersistentHudPtr)
	{
		if (bHide)
			PersistentHudPtr->SetVisibility(ESlateVisibility::Hidden);
		else
			PersistentHudPtr->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UWidgetManagementComponent_OM::HideMentalHealthStats(float TimeHidden)
{
	if (PersistentHudPtr)
	{
		PersistentHudPtr->SetMentalStatVisibility(false);
	}
	GetWorld()->GetTimerManager().ClearTimer(HideMentalStats);
	GetWorld()->GetTimerManager().SetTimer(HideMentalStats, [this]()
	{
		if (PersistentHudPtr)
		{
			PersistentHudPtr->SetMentalStatVisibility(true);
		}
	}, TimeHidden, false);
}
void UWidgetManagementComponent_OM::ShowExitButton(bool bHide) const
{
	if (PersistentHudPtr)
		PersistentHudPtr->SetExitButtonVisibility(!bHide);
}

void UWidgetManagementComponent_OM::FlashExitButton(int LoopsToPlay) const
{
	if (PersistentHudPtr)
		PersistentHudPtr->FlashExitButton(LoopsToPlay);
}

bool UWidgetManagementComponent_OM::GetIsInteractableWidgetOnViewport() const
{
	return (InteractWidgetPtr && InteractWidgetPtr->IsInViewport());
}
