// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/GMB/BedroomGameModeBase_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Components/PlayerController/WidgetManagementComponent_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Home/Concrete/DisplayDayWidget_OM.h"
#include "OptimizeMan/Public/Game/Persistent/GameInstance_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"
#include "Utils/Static Helpers/Helper.h"


ABedroomGameModeBase_OM::ABedroomGameModeBase_OM()
{
	GameInstance = nullptr;
	bIsFadingOut = false;
	bWidgetIsVisible = false;
	bHasOpenedTodoList = false;
	ShowDayWidget = nullptr;
	Player = nullptr;
}

void ABedroomGameModeBase_OM::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

void ABedroomGameModeBase_OM::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	
	GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;
	PlayerController = Cast<APlayerController_OM>(NewPlayer);
	if (!PlayerController) return;
	Player = Cast<APlayerCharacter_OM>(PlayerController->GetPawn());
	if (!Player) return;

	Player->SwitchLevelTag(FGameplayTag::RequestGameplayTag("Level.Home"));
	
	
	if (!GameInstance->GetHasBeenToGymToday())
	{
		WakeUp();
	}
	if (GameInstance->GetDayNumber() > 1)
		ProcessIncompleteTodos();
	else
	{
		if (!GameInstance) return;
		if (GameInstance->GetHasBeenToGymToday()) return;
		if (UNotificationAudio_OM* Not = Cast<UNotificationAudio_OM>(Player->GetComponentByClass<UNotificationAudio_OM>()))
			Not->PlaySplatSound();
	}
}


void ABedroomGameModeBase_OM::ProcessIncompleteTodos()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance needs to be recasted in bedroom game mode base"));
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}

	if (auto* TodoManager = Helper::GetTodoManager(this))
	{
		TArray<FTodoItem>& CurrentTodos = TodoManager->GetCurrentTodoArray();
		FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();
		bool bPlayerUpset = false;
		for (FTodoItem& Todo: CurrentTodos)
		{
			UE_LOG(LogTemp, Display, TEXT("Processing Incomplete Todos"));
			if (!Todo.bIsCompleted)
			{
				UE_LOG(LogTemp, Display, TEXT("Incomplete Todo Found"));
				GameInstance->AddEgo(-1.f);
				bPlayerUpset = true;
			}
		}
		if (bPlayerUpset)
		{
			Player->ShitDay();
		}
	}
}
void ABedroomGameModeBase_OM::WakeUp()
{
	if (!Player) return;
	
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		Player->SetCurrentPlayMode(EPlayModes::WakeUpMode);
	});
	
	
}
void ABedroomGameModeBase_OM::TutorialDay()
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Pointer is NULL in TutorialDay, recasted"));
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, "Tutorial sequence begin");
	//GameInstance->FirstDay();
	
	GetWorld()->GetTimerManager().SetTimer(
		ShowInteractTimerHandle,
		this,
		&ABedroomGameModeBase_OM::ShowInteractHint,
		1.f,
		true
		);
}
void ABedroomGameModeBase_OM::ShowInteractHint()
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Pointer is NULL in ShowTodoHint, recasted"));
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	
	if (!GameInstance->GetHasInteractedInitial())
	{
		const FString TodoHintText = TEXT("Left Click or press E to Interact with objects");
		
		PlayerController->GetWidgetManagementComponent()->ShowOrHideHint(TodoHintText);
	}
	else  //CLEAR TODOLIST TIMER
	{
		PlayerController->GetWidgetManagementComponent()->ShowOrHideHint(TEXT(""), 0.f,  true);
		GetWorld()->GetTimerManager().ClearTimer(ShowInteractTimerHandle);
		
		GetWorld()->GetTimerManager().SetTimer(
			ShowTodoTimerHandle,
			this,
			&ABedroomGameModeBase_OM::ShowTodoHint,
			1.f,
			true
			);
	}
}
void ABedroomGameModeBase_OM::ShowTodoHint()
{
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	if (!GameInstance->GetHasOpenedTodoListInitial())
	{
		const FString TodoHintText = TEXT("Press T to open Todo List");
		
		PlayerController->GetWidgetManagementComponent()->ShowOrHideHint(TodoHintText);
	}
	else  //CLEAR TODOLIST TIMER
	{
		PlayerController->GetWidgetManagementComponent()->ShowOrHideHint(TEXT(""), 0.f,  true);
		GetWorld()->GetTimerManager().ClearTimer(ShowTodoTimerHandle);
		
		GetWorld()->GetTimerManager().SetTimer(
			ShowPauseMenuTimerHandle,
			this,
			&ABedroomGameModeBase_OM::ShowPauseMenuHint,
			1.f,
			true
			);
	}
}
void ABedroomGameModeBase_OM::ShowPauseMenuHint()
{
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	
	if (!GameInstance->GetHasOpenedPauseMenuInitial())
	{
		const FString PauseMenuHintText = TEXT("Press Esc to open settings");
		
		PlayerController->GetWidgetManagementComponent()->ShowOrHideHint(PauseMenuHintText);
	}
	else  //CLEAR TODOLIST TIMER
	{
		PlayerController->GetWidgetManagementComponent()->ShowOrHideHint(TEXT(""), 0.f,  true);
		GetWorld()->GetTimerManager().ClearTimer(ShowPauseMenuTimerHandle);
		
	}
}

void ABedroomGameModeBase_OM::ShowCurrentDay()
{
	TSubclassOf<UDisplayDayWidget_OM> WidgetClass = GetShowDayWidgetClass();
	if (!WidgetClass && IsValid(ShowDayWidget))
	{
		WidgetClass = ShowDayWidget->GetClass();
	}

	if (!WidgetClass) return;

	ShowDayWidget = CreateWidget<UDisplayDayWidget_OM>(GetWorld(), WidgetClass);
	if (!ShowDayWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("ShowCurrentDay: Failed to create ShowDayWidget instance."));
		return;
	}

	if (UDisplayDayWidget_OM* DisplayDayWidget = Cast<UDisplayDayWidget_OM>(ShowDayWidget))
	{
		const FString CurrentDay = GameInstance->GetCurrentDayName();
		const int32 DayNumber = GameInstance->GetDayNumber();
		const FString DisplayDayText = FString::Format(TEXT("Day {0}, {1}"), {DayNumber, CurrentDay});
		DisplayDayWidget->SetText(DisplayDayText);
	}

	ShowDayWidget->SetRenderOpacity(1.0f);
	if (!ShowDayWidget->IsInViewport())
	{
		ShowDayWidget->AddToViewport(2);
		SetWidgetIsVisible(true);
	}

	GetWorld()->GetTimerManager().ClearTimer(DelayTilFadeHandle);
	GetWorld()->GetTimerManager().SetTimer(
		DelayTilFadeHandle,
		this,
		&ABedroomGameModeBase_OM::StartFadeOut,
		5.0f,
		false
	);
}


void ABedroomGameModeBase_OM::StartFadeOut()
{
	if (!ShowDayWidget || !ShowDayWidget->IsInViewport())
		return;

	bIsFadingOut = true;
	GetWorld()->GetTimerManager().SetTimer(
		FadeTimerHandle,
		[this]()
		{
			if (!IsValid(ShowDayWidget))
			{
				bIsFadingOut = false;
				GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);
				return;
			}

			const float CurrentOpacity = ShowDayWidget->GetRenderOpacity();
			const float NewOpacity = FMath::FInterpConstantTo(CurrentOpacity, 0.0f, GetWorld()->GetDeltaSeconds(), 1.0f);
        
			ShowDayWidget->SetRenderOpacity(NewOpacity);

			if (NewOpacity <= 0.0f)
			{
				if (IsValid(ShowDayWidget))
				{
					ShowDayWidget->RemoveFromParent();
				}
				
				SetWidgetIsVisible(false);
				bIsFadingOut = false;
				GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);

				ShowDayWidget = nullptr;
			}
		},
		0.016f, 
		true
	);

}

bool ABedroomGameModeBase_OM::GetIsFadingOut()
{
	return bIsFadingOut;
}

UDisplayDayWidget_OM* ABedroomGameModeBase_OM::GetShowDayWidget() const
{
	return IsValid(ShowDayWidget) ? ShowDayWidget : nullptr;
}

bool ABedroomGameModeBase_OM::GetWidgetIsVisible() const
{
	return bWidgetIsVisible;
}

void ABedroomGameModeBase_OM::SetWidgetIsVisible(const bool InWidgetIsVisible)
{
	bWidgetIsVisible = InWidgetIsVisible;
}
