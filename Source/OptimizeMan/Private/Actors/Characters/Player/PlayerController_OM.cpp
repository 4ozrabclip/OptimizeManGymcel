// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/Player/PlayerController_OM.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GMB/BedroomGameModeBase_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"
#include "Widgets/Both/Concrete/GamePointsHud_OM.h"
#include "Widgets/Gym/Concrete/GymHud_OM.h"
#include "Widgets/Both/Concrete/HintsWidget_OM.h"
#include "Widgets/Both/Concrete/InteractWidget_OM.h"
#include "Widgets/Both/Concrete/PauseMenuWidget_OM.h"
#include "Widgets/Both/Concrete/TodoCompletePopupWidget_OM.h"
#include "Widgets/Both/Concrete/TodoList_OM.h"
#include "Widgets/Gym/Concrete/ExerciseInteractWidget_OM.h"
#include "Widgets/Gym/Concrete/MuscleViewWidget_OM.h"
#include "Widgets/Gym/Concrete/SocialInteractionWidget_OM.h"
#include "Widgets/Gym/Concrete/VendingMachineWidget_OM.h"
#include "Widgets/Home/Concrete/CalenderWidget_OM.h"
#include "Widgets/Home/Concrete/LaptopWidget_OM.h"
#include "Widgets/Home/Concrete/ShelfWidget_OM.h"
#include "Widgets/Home/Concrete/WakeUpTutorial_OM.h"
#include "Widgets/Home/Concrete/WakeUpWidget_OM.h"


class ALevelSequenceActor;

APlayerController_OM::APlayerController_OM()
{
	DefaultMappingContext = nullptr;
	InputToMove = nullptr;
	InputToLook = nullptr;
	InputToJump = nullptr;
	InputToInteractClick = nullptr;
	InputToInteractToggle = nullptr;
	InputToOpenTodo = nullptr;
	InputToOpenPauseMenu = nullptr;
	PlayerCharacter = nullptr;
	GameInstance = nullptr;
	CurrentPlayModeWidgetInstance = nullptr;

	WidgInteractionComp = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgInteractionComp"));
	WidgInteractionComp->SetupAttachment(RootComponent);
	WidgInteractionComp->InteractionSource = EWidgetInteractionSource::Mouse;
	
}

void APlayerController_OM::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnGymStatsChanged.AddDynamic(this, &APlayerController_OM::UpdateGymHud);
		
		if (UTodoManagementSubsystem* TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>()))
		{
			TodoManager->OnTodoComplete.AddDynamic(this, &APlayerController_OM::TodoCompletedPopUp);
		}
	}

	LoadGamePointsHud();
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

void APlayerController_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (WidgInteractionComp && PlayerCameraManager)
	{
		FVector WorldLocation, WorldDirection;
		if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			WidgInteractionComp->SetWorldLocation(PlayerCameraManager->GetCameraLocation());
			WidgInteractionComp->SetWorldRotation(WorldDirection.Rotation());
		}
	}

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

void APlayerController_OM::PlaySequence(ULevelSequence* InSequence)
{
	ALevelSequenceActor* SequenceActor = nullptr;
	
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.bAutoPlay = true;
	ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
	   GetWorld(),
	   InSequence,
	   PlaybackSettings,
	   SequenceActor);

	if (!SequencePlayer)
		return;


	SequencePlayer->Play();

	if (SequencePlayer->IsPlaying())
	{
		UE_LOG(LogTemp, Error, TEXT("Sequence playing"));
	}
}

void APlayerController_OM::PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn)
{
	RemoveAllActiveWidgets();

	TSubclassOf<UUserWidget> WidgetToCreateClass = nullptr;

	switch (CurrentPlayMode)
	{
	case EPlayModes::CalenderMode:
		WidgetToCreateClass = CalenderWidget;
		break;
	case EPlayModes::LaptopMode:
		WidgetToCreateClass = LaptopWidget;
		break;
	case EPlayModes::MirrorMode:
		WidgetToCreateClass = MirrorWidget;
		break;
	case EPlayModes::PauseMode:
		WidgetToCreateClass = PauseMenuWidget;
		break;
	case EPlayModes::ShelfMode:
		WidgetToCreateClass = ShelfWidget;
		break;
	case EPlayModes::SocialMode:
		WidgetToCreateClass = SocialWidget;
		break;
	case EPlayModes::TodoMode:
		WidgetToCreateClass = TodoWidget;
		break;
	case EPlayModes::WorkoutMode:
		WidgetToCreateClass = WorkoutWidget;
		break;
	case EPlayModes::MuscleViewMode:
		WidgetToCreateClass = MuscleViewWidget;
		break;
	case EPlayModes::WakeUpMode:
		if (GameInstance->GetDayNumber() == 1)
			WidgetToCreateClass = WakeUpWidget_Tutorial;
		else
			WidgetToCreateClass = WakeUpWidget;
		break;
	case EPlayModes::VendingMachine:
		WidgetToCreateClass = VendorWidget;
		break;
	default:
		return;
	}

	CurrentPlayModeWidgetInstance = CreateWidget<UUserWidget>(this, WidgetToCreateClass);
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
		CurrentPlayModeWidgetInstance->AddToViewport();
	}
}

void APlayerController_OM::UpdateGymHud()
{
	if (!GymHudPtr) return; // Ensure it's created
	if (!GymHudPtr->IsInViewport()) return; // Only update if visible

	if (UGymHud_OM* HudClass = Cast<UGymHud_OM>(GymHudPtr))
	{
		HudClass->UpdateProgressBars();
	}
}
void APlayerController_OM::SetGymHud(bool bLoad)
{
	if (!GymHudPtr)
	{
		if (GymHudWidget)
		{
			GymHudPtr = CreateWidget<UGymHud_OM>(this, GymHudWidget);
		}
		if (!GymHudPtr) return; 
	}

	if (bLoad)
	{
		if (!GymHudPtr->IsInViewport())
		{
			GymHudPtr->AddToViewport();
		}
	}
	else
	{
		if (GymHudPtr->IsInViewport())
		{
			GymHudPtr->RemoveFromParent();
		}
	}
}
void APlayerController_OM::LoadGamePointsHud(const bool bLoad)
{
	if (!GamePointsHudPtr)
	{
		if (GamePointsWidget)
		{
			GamePointsHudPtr = CreateWidget<UGamePointsHud_OM>(this, GamePointsWidget);
		}
		if (!GamePointsHudPtr) return;
	}

	if (bLoad)
	{
		if (!GamePointsHudPtr->IsInViewport())
		{
			GamePointsHudPtr->AddToViewport();
		}
	}
	else
	{
		if (GamePointsHudPtr->IsInViewport())
		{
			GamePointsHudPtr->RemoveFromParent();
		}
	}
}





void APlayerController_OM::ShowOrHideHint(const FString& HintText, float HintLength, bool HideHint, bool RemoveFully) const // Move this out of the player class
{ 
	APlayerController_OM* ThisPC = const_cast<APlayerController_OM*>(this);

	if (!ThisPC->HintsPtr)
	{
		if (HintWidget)
		{
			ThisPC->HintsPtr = CreateWidget<UHintsWidget_OM>(ThisPC, HintWidget);
		}
		if (!ThisPC->HintsPtr) return;
	}

	UHintsWidget_OM* HintWidgetClassCast = Cast<UHintsWidget_OM>(ThisPC->HintsPtr);
	if (!HintWidgetClassCast) return;

	const FText HintInputText = FText::FromString(*HintText);

	if (RemoveFully && ThisPC->HintsPtr->IsInViewport())
		ThisPC->HintsPtr->RemoveFromParent();

	if (HideHint && ThisPC->HintsPtr->IsInViewport())
	{
		HintWidgetClassCast->HideHint();
	}
	else if (!HideHint && !ThisPC->HintsPtr->IsInViewport())
	{
		ThisPC->HintsPtr->AddToViewport();
		if (HintLength > 0.f)
		{
			HintWidgetClassCast->ShowHint(HintInputText, HintLength);
		}
		else
		{
			HintWidgetClassCast->ShowHint(HintInputText);
		}
	}
	else if (!HideHint && ThisPC->HintsPtr->IsInViewport())
	{
		if (HintLength > 0.f)
		{
			HintWidgetClassCast->ShowHint(HintInputText, HintLength);
		}
		else
		{
			HintWidgetClassCast->ShowHint(HintInputText);
		}
	}
}

void APlayerController_OM::HideGamePointsHud(bool bHide)
{
	if (GamePointsHudPtr)
	{
		if (bHide)
			GamePointsHudPtr->SetVisibility(ESlateVisibility::Hidden);
		else
			GamePointsHudPtr->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void APlayerController_OM::TodoCompletedPopUp()
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
		TodoWidgetPtr->AddToViewport();
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


void APlayerController_OM::WidgetInteraction(const TScriptInterface<IInteractableInterface_OM>& InteractedActorInterface)
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
			InteractWidgetPtr->AddToViewport();

		}

	}

}


void APlayerController_OM::HideUnhideInteractableWidget(const bool bHide)
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

void APlayerController_OM::ToggleInteractWidgetFromViewport(bool bRemove)
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
            InteractWidgetPtr->AddToViewport();
        }
        InteractWidgetPtr->SetVisibility(ESlateVisibility::Visible);
    }
}

bool APlayerController_OM::GetIsInteractableWidgetOnViewport()
{
    return (InteractWidgetPtr && InteractWidgetPtr->IsInViewport());
}
