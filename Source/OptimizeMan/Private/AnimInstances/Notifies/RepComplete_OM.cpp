// Copyright © 2025 4ozStudio. All rights reserved.


#include "AnimInstances/Notifies/RepComplete_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Character/Concrete/Exercise_OM.h"

void URepComplete_OM::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (auto* Player = Cast<APlayerCharacter_OM>(MeshComp->GetOwner()))
	{
		if (auto* ExerciseComp = Cast<UExercise_OM>(Player->GetComponentByClass<UExercise_OM>()))
		{
			ExerciseComp->SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
		}
	}
	
}
