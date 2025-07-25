// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_FinishWorkout.h"

#include "Actors/Other/Gym/Abstract/ExerciseEquipment_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_FinishWorkout::UBTTask_FinishWorkout(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Finish Workout";
	Equipment = nullptr;
	NPC = nullptr;
}

EBTNodeResult::Type UBTTask_FinishWorkout::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		NPC = Cast<ANpcBase_OM>(Cont->GetCharacter());
		if (!NPC) return EBTNodeResult::Failed;
		if (auto* BB = OwnerComp.GetBlackboardComponent())
		{
			Equipment = Cast<AExerciseEquipment_OM>(BB->GetValueAsObject(FName("Current Interacted Object")));
			if (!Equipment) return EBTNodeResult::Failed;
			
			ExitAnim(NPC->GetCurrentExerciseType());
			DetachEquipment();
			NPC->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

			Equipment->SetIsInteractable(true);
			Equipment->AuraLight->SetVisibility(true);

			NPC->SetCurrentInteractedItem(nullptr);

			BB->SetValueAsObject(FName("Current Interacted Object"), nullptr);
			
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}

void UBTTask_FinishWorkout::DetachEquipment()
{
	if (!Equipment)	return;

	Equipment->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Equipment->SetActorTransform(Equipment->GetOriginalPosition());
}

void UBTTask_FinishWorkout::ExitAnim(EExerciseType InExerciseType)
{
	UNpcBaseAnimInstance_OM* AnimInstance = NPC->GetAnimInstance();
	switch (InExerciseType)
	{
	case EExerciseType::None:
		break;
	case EExerciseType::Squat:
		AnimInstance->ExitSquatPosition();
		break;
	case EExerciseType::BicepCurl:
		AnimInstance->ExitCurlPosition();
		break;
	case EExerciseType::OverheadPress:
		AnimInstance->ExitOverheadPressPosition();
		break;
	case EExerciseType::LeftCurl:
		AnimInstance->ExitLeftCurlPosition();
		break;
	case EExerciseType::RightCurl:
		AnimInstance->ExitRightCurlPosition();
		break;
	default:
		break;
	}

}

