// Copyright © 2025 4ozStudio. All rights reserved.

#include "Widgets/Gym/Concrete/ExerciseMinigameWidget_OM.h"


#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
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
		if (auto* ExerciseComponent = Player->GetComponentByClass<UExercise_OM>())
		{
			OnMinigameResult.AddDynamic(ExerciseComponent, &UExercise_OM::MiniGame);
			ExerciseComponent->OnWorkoutStateChanged.RemoveAll(this);
			ExerciseComponent->OnWorkoutStateChanged.AddDynamic(this, &UExerciseMinigameWidget_OM::SetWorkoutState);
			
			ExerciseComponent->PrepareExercise();
		}
	}

	

	CheckAndSetStyles();
}

void UExerciseMinigameWidget_OM::NativeDestruct()
{
	Super::NativeDestruct();
}
void UExerciseMinigameWidget_OM::OnPlayModeChanged(EPlayModes InPlayMode)
{
	if (InPlayMode == EPlayModes::PauseMode)
		OnExitButtonClicked();
}

void UExerciseMinigameWidget_OM::OnExitButtonClicked()
{
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		UE_LOG(LogTemp, Display, TEXT("ExerciseInteractWidget: Recasting to player in OnExitButtonClicked"));
	}
	if (!Player) return;
	

	if (auto* ExerciseComponent = Player->GetComponentByClass<UExercise_OM>())
	{
		ExerciseComponent->LeaveExercise();
	}
		

	
	Super::OnExitButtonClicked();

	if (UPlayerCharacterAnimInstance_OM* AnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(Player->GetMesh()->GetAnimInstance()))
	{
		AnimInstance->SetHasInjury(false);
	}
}
