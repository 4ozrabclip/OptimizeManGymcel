// Copyright © 2025 4ozStudio. All rights reserved.


#include "AnimInstances/Notifies/InjuryRepComplete_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Components/Character/Concrete/Exercise_OM.h"

void UInjuryRepComplete_OM::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (auto* Player = Cast<APlayerCharacter_OM>(MeshComp->GetOwner()))
	{
		if (auto* AnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(Player->GetCachedAnimInstance()))
		{
			AnimInstance->SetHasInjury(false);
			if (auto* ExerciseComp = Cast<UExercise_OM>(Player->GetComponentByClass<UExercise_OM>()))
			{
				ExerciseComp->SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
			}
		}

	}
	
}
