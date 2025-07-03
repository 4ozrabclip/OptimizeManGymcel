// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/Player/PlayerController_OMG.h"

#include "EnhancedInputComponent.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Game/GMB/BedroomGameModeBase_OM.h"
#include "Game/Persistent/GameInstance_OMG.h"
#include "Game/SubSystems/TodoManagementSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Structs/PlayModes_Gymcel.h"
#include "Widgets/InteractWidget_OM.h"
#include "Widgets/Both/Concrete/PauseMenuWidget_OM.h"
#include "Widgets/Both/Concrete/TodoCompletePopupWidget_OM.h"
#include "Widgets/Both/Concrete/TodoList_OM.h"
#include "Widgets/Gym/Concrete/ExerciseInteractWidget_OM.h"
#include "Widgets/Gym/Concrete/GymHud_OM.h"
#include "Utils/UtilityHelpers_OMG.h"
#include "Widgets/Both/Concrete/HintsWidget_OM.h"
#include "Widgets/Gym/Concrete/MuscleViewWidget_OM.h"
#include "Widgets/Gym/Concrete/SocialInteractionWidget_OM.h"
#include "Widgets/Home/Concrete/CalenderWidget_OM.h"
#include "Widgets/Home/Concrete/LaptopWidget_OM.h"
#include "Widgets/Home/Concrete/MirrorWidget_OM.h"
#include "Widgets/Home/Concrete/ShelfWidget_OM.h"
#include "Widgets/Home/Concrete/WakeUpTutorial_OM.h"
#include "Widgets/Home/Concrete/WakeUpWidget_OM.h"


APlayerController_OMG::APlayerController_OMG()
{
}
void APlayerController_OMG::BindInputMapping()
{
	Super::BindInputMapping();
	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputToOpenTodo, ETriggerEvent::Completed, GymcelUtils::GetPlayer_Gymcel(GetWorld()), &APlayerCharacter_OM::ToggleTodoMode);
		EnhancedInputComponent->BindAction(InputToOpenPauseMenu, ETriggerEvent::Completed, GymcelUtils::GetPlayer_Gymcel(GetWorld()), &APlayerCharacter_OM::TogglePauseMode);
	}
}
void APlayerController_OMG::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UGameInstance_OMG>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		GymcelUtils::GetGameInstance_Gymcel(GetWorld())->OnGymStatsChanged.AddDynamic(this, &APlayerController_OMG::UpdateGymHud);
		
		if (UTodoManagementSubsystem* TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>()))
		{
			TodoManager->OnTodoComplete.AddDynamic(this, &APlayerController_OMG::TodoCompletedPopUp);
		}
	}
	
}


void APlayerController_OMG::PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn)
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


void APlayerController_OMG::UpdateGymHud()
{
	if (!GymHudPtr) return; // Ensure it's created
	if (!GymHudPtr->IsInViewport()) return; // Only update if visible

	if (UGymHud_OM* HudClass = Cast<UGymHud_OM>(GymHudPtr))
	{
		HudClass->UpdateProgressBars();
	}
}
void APlayerController_OMG::SetGymHud(bool bLoad)
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

void APlayerController_OMG::TodoCompletedPopUp()
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

void APlayerController_OMG::FadeWidgets(UUserWidget* FadeOutWidget, UUserWidget* FadeInWidget)
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

void APlayerController_OMG::RemoveAllActiveWidgets()
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

APlayerCharacter_OM* APlayerController_OMG::GetPlayer_Gymcel() const
{
	return Cast<APlayerCharacter_OM>(PlayerCharacter);
}

void APlayerController_OMG::ShowOrHideHint(const FString& HintText, float HintLength, bool HideHint, bool RemoveFully) const 
{ 
	APlayerController_OMG* ThisPC = const_cast<APlayerController_OMG*>(this);

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




void APlayerController_OMG::PlaySequence(ULevelSequence* InSequence)
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
