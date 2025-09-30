// Copyright © 2025 4ozStudio. All rights reserved.

#include "Widgets/Gym/Concrete/ExerciseInteractWidget_OM.h"


#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Kismet/GameplayStatics.h"

void UExerciseInteractWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
}

void UExerciseInteractWidget_OM::NativeDestruct()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(Minigame);
	Super::NativeDestruct();
}
void UExerciseInteractWidget_OM::OnPlayModeChanged(EPlayModes InPlayMode)
{
	if (InPlayMode == EPlayModes::PauseMode)
		OnExitButtonClicked();
}

void UExerciseInteractWidget_OM::OnExitButtonClicked()
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
