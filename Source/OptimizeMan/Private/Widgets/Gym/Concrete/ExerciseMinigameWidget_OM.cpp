// Copyright © 2025 4ozStudio. All rights reserved.

#include "Widgets/Gym/Concrete/ExerciseMinigameWidget_OM.h"


#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Components/TextBlock.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Kismet/GameplayStatics.h"

void UExerciseMinigameWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	if (!PlayerController)
	{	
		PlayerController = Cast<APlayerController_OM>(GetOwningPlayer());
	}
	if (!Player && PlayerController)
	{
		Player = Cast<APlayerCharacter_OM>(PlayerController->GetPawn());
	}

	if (Player)
	{
		if (!ExerciseComponent)
			ExerciseComponent = Player->GetComponentByClass<UExercise_OM>();
		if (ExerciseComponent)
		{
			OnMinigameResult.AddDynamic(ExerciseComponent, &UExercise_OM::MiniGame);
			ExerciseComponent->OnWorkoutStateChanged.RemoveAll(this);
			ExerciseComponent->OnWorkoutStateChanged.AddDynamic(this, &UExerciseMinigameWidget_OM::SetWorkoutState);
			
			ExerciseComponent->PrepareExercise();
		}
	}
	
	CheckAndSetStyles();



	/*
	 * Why is this on a 1 second timer??
	 */
	GetWorld()->GetTimerManager().SetTimer(TutorialDelayHandle, [this]()
	{
		bHasPlayedThisMinigame = GameInstance->GetHasPlayedMiniGameInitial(MiniGameType);
	},1.f, false);

	
	CheckStatsForFrontEnd();

}

void UExerciseMinigameWidget_OM::NativeDestruct()
{
	Super::NativeDestruct();
}

void UExerciseMinigameWidget_OM::OnExitButtonClicked()
{
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		UE_LOG(LogTemp, Display, TEXT("ExerciseInteractWidget: Recasting to player in OnExitButtonClicked"));
	}
	if (!Player) return;
	

	if (ExerciseComponent)
	{
		ExerciseComponent->LeaveExercise();
	}
		

	
	Super::OnExitButtonClicked();

	if (UPlayerCharacterAnimInstance_OM* AnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(Player->GetMesh()->GetAnimInstance()))
	{
		AnimInstance->SetHasInjury(false);
	}
}

void UExerciseMinigameWidget_OM::OnMiniGameClick()
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Pointer is NULL"));
		return;
	}
	if (!ExerciseComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ExerciseComponent Pointer is NULL"));
		return;
	}

	if (!bHasPlayedThisMinigame)
	{
		GameInstance->SetHasPlayedMiniGameInitial(MiniGameType);
		bHasPlayedThisMinigame = true;
	}


	SetLocalEnergyLevel(ExerciseComponent->GetEnergy());

}
void UExerciseMinigameWidget_OM::OnPlayModeChanged(EPlayModes InPlayMode)
{
	if (InPlayMode == EPlayModes::PauseMode)
		OnExitButtonClicked();
}

void UExerciseMinigameWidget_OM::SetSetAndRepCountTextBlocks() const
{
	if (!ExerciseComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ExerciseComponent null in SetSetAndRepCountTextBlock"));
		return;
	}
	if (!SetCountTextBlock || !RepCountTextBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("SetCountTextBlock and/or RepCountTextBlock is null"));
		return;
	}

	const int SetCount = ExerciseComponent->GetSetCount();
	const int RepCount = ExerciseComponent->GetRepCount();
	
	const FText SetCountText = FText::Format(FText::FromString(TEXT("Set: {0}")), FText::AsNumber(SetCount));
	const FText RepCountText = FText::Format(FText::FromString(TEXT("Reps: {0}")), FText::AsNumber(RepCount));

	SetCountTextBlock->SetText(SetCountText);
	RepCountTextBlock->SetText(RepCountText);
}


/*
 * Look At other function which SetSetAndRepCountTextBlock is called in
 * 
 */
void UExerciseMinigameWidget_OM::SetNotificationText() const
{
	if (!ExerciseComponent) return;
	
	if (EnergyLevel <= 0.f && CurrentWorkoutState == EWorkoutStates::SetComplete)
	{
		const FText SetCompleteNoEnergyText = FText::FromString("Last Set No Energy");
		NotificationText->SetText(SetCompleteNoEnergyText);
	}
	else if (EnergyLevel <= 0.f)
	{
		const FText NoEnergyText = FText::FromString("No Energy");
		NotificationText->SetText(NoEnergyText);
		
	}
	else if (CurrentWorkoutState == EWorkoutStates::SetComplete)
	{
		const FText SetCompleteText = FText::FromString("Set Complete");
		NotificationText->SetText(SetCompleteText);
	}
}


void UExerciseMinigameWidget_OM::NotificationTextPopUp(const FString& InString)
{
	SetNotificationText();
	constexpr float PopUpTimeShown = 2.f;

	NotificationText->SetText(FText::FromString(InString));
	NotificationText->SetVisibility(ESlateVisibility::Visible);
	
	GetWorld()->GetTimerManager().ClearTimer(TextPopUpDelayHandle);
	GetWorld()->GetTimerManager().SetTimer(
			TextPopUpDelayHandle,
			[this]()
			{
				NotificationText->SetVisibility(ESlateVisibility::Hidden);
			},
			PopUpTimeShown, 
			false 
		);
}
