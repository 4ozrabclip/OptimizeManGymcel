// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/BedroomGameModeBase_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Kismet/GameplayStatics.h"
#include "OptimizeMan/Public/Widgets/DisplayDayWidget_OM.h"
#include "OptimizeMan/Public/Utils/GameInstance_OM.h"
#include "Utils/TodoManagementSubsystem.h"


ABedroomGameModeBase_OM::ABedroomGameModeBase_OM()
{
	GameInstance = nullptr;
	bIsFadingOut = false;
	bWidgetIsVisible = false;
	bHasOpenedTodoList = false;
	ShowDayWidget = nullptr;
	Player = nullptr;
	TodoManager = nullptr;
}

void ABedroomGameModeBase_OM::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is null"));
		return;
	}
	GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is null"));
		return;
	}
	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("TodoManager is null in bedroom gamemode base"));
		return;
	}

	
	if (!GameInstance->GetHasBeenToGymToday())
	{
		ShowCurrentDay();
		
		if (GameInstance->GetDayNumber() > 1) WakeUp();
	}
	if (GameInstance->GetDayNumber() == 1)
	{
		TutorialDay();
	}
	else
	{
		ProcessIncompleteTodos();
	}
}
void ABedroomGameModeBase_OM::ProcessIncompleteTodos()
{
	if (!TodoManager)
	{
		TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance needs to be recasted in bedroom game mode base"));
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	TArray<FTodoItem>& CurrentTodos = TodoManager->CurrentTodoArray;
	FPlayerData& PlayerData = GameInstance->GetPlayerData();
	bool bPlayerUpset = false;
	for (FTodoItem& Todo: CurrentTodos)
	{
		UE_LOG(LogTemp, Display, TEXT("Processing Incomplete Todos"));
		if (!Todo.bIsCompleted)
		{
			UE_LOG(LogTemp, Display, TEXT("Incomplete Todo Found"));
			PlayerData.AddStat(PlayerData.Ego, -1.f);
			bPlayerUpset = true;
		}
	}
	if (bPlayerUpset)
	{
		Player->ShitDay();
	}
}
void ABedroomGameModeBase_OM::WakeUp()
{
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("Waking up"));
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
	GameInstance->FirstDay();
	
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
		
		Player->ShowOrHideHint(TodoHintText);
	}
	else  //CLEAR TODOLIST TIMER
	{
		Player->ShowOrHideHint(TEXT(""), 0.f,  true);
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
		
		Player->ShowOrHideHint(TodoHintText);
	}
	else  //CLEAR TODOLIST TIMER
	{
		Player->ShowOrHideHint(TEXT(""), 0.f,  true);
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
		
		Player->ShowOrHideHint(PauseMenuHintText);
	}
	else  //CLEAR TODOLIST TIMER
	{
		Player->ShowOrHideHint(TEXT(""), 0.f,  true);
		GetWorld()->GetTimerManager().ClearTimer(ShowPauseMenuTimerHandle);
		
	}
}

void ABedroomGameModeBase_OM::ShowCurrentDay()
{
	if (const TSubclassOf<UUserWidget> WidgetClass = ShowDayWidget->GetClass())
	{
		ShowDayWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		
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
			ShowDayWidget->AddToViewport();
			SetWidgetIsVisible(true);
		}
		
		GetWorld()->GetTimerManager().SetTimer(
			DelayTilFadeHandle,
			[this]()
			{
				StartFadeOut();
			},
			5.0f,
			false
		);
	}
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
			const float CurrentOpacity = ShowDayWidget->GetRenderOpacity();
			const float NewOpacity = FMath::FInterpConstantTo(CurrentOpacity, 0.0f, GetWorld()->GetDeltaSeconds(), 1.0f);
            
			ShowDayWidget->SetRenderOpacity(NewOpacity);
			
			if (NewOpacity <= 0.0f)
			{
				ShowDayWidget->RemoveFromParent();
				SetWidgetIsVisible(false);
				bIsFadingOut = false;
				GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);
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

bool ABedroomGameModeBase_OM::GetWidgetIsVisible() const
{
	return bWidgetIsVisible;
}

void ABedroomGameModeBase_OM::SetWidgetIsVisible(const bool InWidgetIsVisible)
{
	bWidgetIsVisible = InWidgetIsVisible;
}
