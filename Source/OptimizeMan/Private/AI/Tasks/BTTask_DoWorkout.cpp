// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_DoWorkout.h"

#include "Actors/Other/Gym/Abstract/ExerciseEquipment_OM.h"
#include "Actors/Other/Gym/Concrete/Barbell_OM.h"
#include "Actors/Other/Gym/Concrete/Dumbell_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTTask_DoWorkout::UBTTask_DoWorkout(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Start Workout";
	NPC = nullptr;
}

EBTNodeResult::Type UBTTask_DoWorkout::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		NPC = Cast<ANpcBase_OM>(Cont->GetCharacter());
		if (NPC)
		{
			if (auto* BB = OwnerComp.GetBlackboardComponent())
			{
				const int RepAmont = FMath::RandRange(2, 3);

				BB->SetValueAsInt(FName("RepAmount"), RepAmont);
				if (auto* EquipmentObject = Cast<AExerciseEquipment_OM>(BB->GetValueAsObject(FName("Current Interacted Object"))))
				{
					EnterExercisePosition(EquipmentObject);

					//EquipmentObject->SetIsInteractable(false);
					
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}


void UBTTask_DoWorkout::EnterExercisePosition(AExerciseEquipment_OM* InEquipment)
{
	const FName NeckSocket = FName("NeckSocket");
	const FName LeftHandSocket = FName("LeftHandSocket");
	const FName RightHandSocket = FName("RightHandSocket");

	if (!NPC) return;

	UNpcBaseAnimInstance_OM* AnimInstance = NPC->GetAnimInstance();
	
	if (!AnimInstance) return;

	if (NPC->GetCurrentState() != ENpcState::WorkingOut) return;

	NPC->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	
	if (InEquipment->IsA<ABarbell_OM>())
		RandSetWorkoutType(EExerciseType::Squat, EExerciseType::Squat, EExerciseType::Squat);
	else if (InEquipment->IsA<ADumbell_OM>())
		RandSetWorkoutType(EExerciseType::RightCurl, EExerciseType::RightCurl, EExerciseType::LeftCurl);

	
	const FVector BicepCurlRelativeLocation = FVector(21.f, -1.f, 0.f); //bicepcurl
	switch (NPC->GetCurrentExerciseType())
	{
	case EExerciseType::None:
		return;
	case EExerciseType::Squat:
		//Have a check here to see if equipment is a barbell
		InEquipment->AttachToComponent(NPC->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, NeckSocket);
		AnimInstance->SetIsInSquatPosition(true);
		break;
	case EExerciseType::BicepCurl:
		InEquipment->AttachToComponent(NPC->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, LeftHandSocket);
		InEquipment->SetActorRelativeLocation(BicepCurlRelativeLocation);
		AnimInstance->SetIsInCurlPosition(true);
		break;
	case EExerciseType::OverheadPress:
		AnimInstance->SetIsInOverheadPressPosition(true);
		break;
	case EExerciseType::LeftCurl:
		InEquipment->AttachToComponent(NPC->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, LeftHandSocket);
		AnimInstance->SetIsInLeftCurlPosition(true);
		break;
	case EExerciseType::RightCurl:
		InEquipment->AttachToComponent(NPC->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandSocket);
		AnimInstance->SetIsInRightCurlPosition(true);
		break;
	default:
		return;
	}


	InEquipment->AuraLight->SetVisibility(false);

}

void UBTTask_DoWorkout::RandSetWorkoutType(const EExerciseType InType1, const EExerciseType InType2,
	const EExerciseType InType3)
{
	short ExerciseTypeChoice = FMath::RandRange(0, 2);

	switch (ExerciseTypeChoice)
	{
	case 0:
		NPC->SetCurrentExerciseType(InType1);
		break;
	case 1:
		NPC->SetCurrentExerciseType(InType2); 
		break;
	case 2:
		NPC->SetCurrentExerciseType(InType3);
		break;
	default:
		return;
	}

}

