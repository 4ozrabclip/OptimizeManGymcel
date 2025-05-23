// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/Player/PlayerController_OM.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/BedroomGameModeBase_OM.h"
#include "Utils/TodoManagementSubsystem.h"
#include "Widgets/GymHud_OM.h"
#include "Widgets/HintsWidget_OM.h"
#include "Widgets/InteractWidget_OM.h"

void APlayerController_OM::BeginPlay()
{
	Super::BeginPlay();
	
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		GameInstance->OnGymStatsChanged.AddDynamic(this, &APlayerController_OM::UpdateGymHud);
		
		if (UTodoManagementSubsystem* TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>()))
		{
			TodoManager->OnTodoComplete.AddDynamic(this, &APlayerController_OM::TodoCompletedPopUp);
		}
	}
}
void APlayerController_OM::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerCharacter = Cast<APlayerCharacter_OM>(InPawn);
	
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	BindInputMapping();
}

void APlayerController_OM::BindInputMapping()
{
	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (!PlayerCharacter) return;
		EnhancedInputComponent->BindAction(InputToLook, ETriggerEvent::Triggered, PlayerCharacter, &APlayerCharacter_OM::Look);
		EnhancedInputComponent->BindAction(InputToMove, ETriggerEvent::Triggered, PlayerCharacter, &APlayerCharacter_OM::Move);
		EnhancedInputComponent->BindAction(InputToJump, ETriggerEvent::Triggered, PlayerCharacter, &APlayerCharacter_OM::Jump);
		EnhancedInputComponent->BindAction(InputToInteractClick, ETriggerEvent::Completed, PlayerCharacter, &APlayerCharacter_OM::InteractClick);
		EnhancedInputComponent->BindAction(InputToInteractToggle, ETriggerEvent::Completed, PlayerCharacter, &APlayerCharacter_OM::InteractToggle);
		EnhancedInputComponent->BindAction(InputToOpenTodo, ETriggerEvent::Completed, PlayerCharacter, &APlayerCharacter_OM::ToggleTodoMode);
		EnhancedInputComponent->BindAction(InputToOpenPauseMenu, ETriggerEvent::Completed, PlayerCharacter, &APlayerCharacter_OM::TogglePauseMode);
	}
}

void APlayerController_OM::PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn)
{
	SetCurrentPlayModeWidget(CurrentPlayMode);
	if (CurrentPlayModeWidget->IsInViewport()) return;
	
	if (bHasFadeIn)
	{
		FadeWidgets(nullptr, CurrentPlayModeWidget);
		ActiveWidgets.Add(CurrentPlayModeWidget);
	}
	else 
	{
		CurrentPlayModeWidget->AddToViewport();
		ActiveWidgets.Add(CurrentPlayModeWidget);
	}
}


void APlayerController_OM::SetCurrentPlayModeWidget(EPlayModes CurrentPlayMode)
{
	switch (CurrentPlayMode)
	{
	case EPlayModes::CalenderMode:
		CurrentPlayModeWidget = CalenderWidget;
		break;
	case EPlayModes::LaptopMode:
		CurrentPlayModeWidget = LaptopWidget;
		break;
	case EPlayModes::MirrorMode:
		CurrentPlayModeWidget = MirrorWidget;
		break;
	case EPlayModes::PauseMode:
		CurrentPlayModeWidget = PauseMenuWidget;
		break;
		
	case EPlayModes::ShelfMode:
		CurrentPlayModeWidget = ShelfWidget;
		break;
		
	case EPlayModes::SocialMode:
		CurrentPlayModeWidget = SocialWidget;
		break;
		
	case EPlayModes::TodoMode:
		CurrentPlayModeWidget = TodoWidget;
		break;
		
	case EPlayModes::WorkoutMode:
		CurrentPlayModeWidget = WorkoutWidget;
		break;
		
	case EPlayModes::MuscleViewMode:
		CurrentPlayModeWidget = MuscleViewWidget;
		break;
		
	case EPlayModes::WakeUpMode:
		CurrentPlayModeWidget = WakeUpWidget;
		break;
		
	default:
		CurrentPlayModeWidget = nullptr;
		break;
	}
}
void APlayerController_OM::UpdateGymHud()
{
	if (!GymHudWidget->IsInViewport()) return;
	if (UGymHud_OM* HudClass = Cast<UGymHud_OM>(GymHudWidget))
	{
		HudClass->UpdateProgressBars();
	}
}
void APlayerController_OM::SetGymHud(bool bLoad)
{
	if (!GymHudWidget) return;

	if (bLoad)
	{
		if (GymHudWidget->IsInViewport()) return;

		GymHudWidget->AddToViewport();
	}
	else
	{
		if (!GymHudWidget->IsInViewport()) return;

		GymHudWidget->RemoveFromParent();
	}
}

void APlayerController_OM::ShowOrHideHint(const FString& HintText, float HintLength, bool HideHint, bool RemoveFully) const // Move this out of the player class
{ 
	if (!HintWidget) return;
	UHintsWidget_OM* HintWidgetClass = Cast<UHintsWidget_OM>(HintWidget);
	if (!HintWidgetClass) return;

	const FText HintInputText = FText::FromString(*HintText);

	if (RemoveFully && HintWidget->IsInViewport())
		HintWidget->RemoveFromParent();
	
	if (HideHint && HintWidget->IsInViewport())
	{
		HintWidgetClass->HideHint();
	}
	else if (!HideHint && !HintWidget->IsInViewport())
	{
		HintWidget->AddToViewport();
		if (HintLength > 0.f)
		{
			HintWidgetClass->ShowHint(HintInputText, HintLength);
		}
		else
		{
			HintWidgetClass->ShowHint(HintInputText);
		}
	}
	else if (!HideHint && HintWidget->IsInViewport())
	{
		if (HintLength > 0.f)
		{
			HintWidgetClass->ShowHint(HintInputText, HintLength);
		}
		else
		{
			HintWidgetClass->ShowHint(HintInputText);
		}
	}
}
void APlayerController_OM::TodoCompletedPopUp()
{
	if (TodoCompleteWidget && !TodoCompleteWidget->IsInViewport())
	{
		TodoCompleteWidget->AddToViewport();
	}
	
	constexpr float PopUpTimeAmount = 4.f;

	GetWorld()->GetTimerManager().ClearTimer(TodoPopUpHandle);
	GetWorld()->GetTimerManager().SetTimer(
		TodoPopUpHandle,
		[this]()
		{
			if (TodoCompleteWidget->IsInViewport())
			{
				TodoCompleteWidget->RemoveFromParent();
			}
		},
		PopUpTimeAmount,
		false
		);
}

void APlayerController_OM::FadeWidgets(UUserWidget* FadeOutWidget, UUserWidget* FadeInWidget)
{
	ABedroomGameModeBase_OM* BedroomGameMode = Cast<ABedroomGameModeBase_OM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!FadeOutWidget && BedroomGameMode)
		FadeOutWidget = BedroomGameMode->GetShowDayWidget(); 
	if (!FadeOutWidget)
		return;
	
	if (!FadeOutWidget->IsInViewport() && !FadeInWidget->IsInViewport())
	{
		FadeInWidget->AddToViewport();
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

void APlayerController_OM::RemoveAllActiveWidgets()
{
	if (InteractableActorWidget && InteractableActorWidget->IsInViewport())
	{
		InteractableActorWidget->RemoveFromParent();
	}
	for (UUserWidget* Widget : ActiveWidgets)
	{
		if (Widget && Widget->IsInViewport())
		{
			UE_LOG(LogTemp, Error, TEXT("Removing widget from viewport"));
			Widget->RemoveFromParent();
		}
	}
	ActiveWidgets.Empty();
}

void APlayerController_OM::WidgetInteraction(const TScriptInterface<IInteractableInterface_OM>& InteractedActorInterface)
{
	if (InteractableActorWidget) return;
	
	if (const TSubclassOf<UUserWidget> WidgetClass = InteractedActorInterface->GetInteractableWidget())
	{
		InteractableActorWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (UInteractWidget_OM* InteractWidget = Cast<UInteractWidget_OM>(InteractableActorWidget))
		{
			//InteractWidget->CheckAndSetTextColour();
			InteractWidget->SetText(InteractedActorInterface->GetInteractionWidgetText());
		}
		if (!InteractableActorWidget->IsInViewport())
		{
			InteractableActorWidget->AddToViewport();
		}
	}
}
void APlayerController_OM::HideUnhideInteractableWidget(const bool bHide)
{
	if (!InteractableActorWidget) return;

	if (bHide)
		InteractableActorWidget->SetVisibility(ESlateVisibility::Hidden);
	else
		InteractableActorWidget->SetVisibility(ESlateVisibility::Visible);
}

void APlayerController_OM::ToggleInteractWidgetFromViewport(bool bRemove)
{
	if (bRemove)
	{
		InteractableActorWidget->RemoveFromParent();
		InteractableActorWidget = nullptr;
	}
	else
	{
		if (InteractableActorWidget)
			InteractableActorWidget->AddToViewport();
	}

}
bool APlayerController_OM::GetIsInteractableWidgetOnViewport()
{
	return (InteractableActorWidget && InteractableActorWidget->IsInViewport());
}
