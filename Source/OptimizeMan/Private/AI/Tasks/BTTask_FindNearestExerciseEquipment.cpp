// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_FindNearestExerciseEquipment.h"

#include "NavigationSystem.h"
#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "Actors/Other/Gym/Abstract/ExerciseEquipment_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindNearestExerciseEquipment::UBTTask_FindNearestExerciseEquipment(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Find Nearest Workout Equipment";
}

EBTNodeResult::Type UBTTask_FindNearestExerciseEquipment::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		if (auto* NPC = Cast<ANpcBase_OM>(Cont->GetCharacter()))
		{
			TArray<TSoftObjectPtr<AExerciseEquipment_OM>> EquipInLevel = NPC->GetEquipmentInLevel();
			if (EquipInLevel.Num() <= 0)
			{
				UE_LOG(LogTemp, Error, TEXT("Equip IN Level Is zero or under"));
				return EBTNodeResult::Failed;
			}
			int InitialEquipmentIndex = 0;
			for (size_t LevelEquipmentIndex = 0; LevelEquipmentIndex < EquipInLevel.Num(); LevelEquipmentIndex++)
			{
				if (EquipInLevel[LevelEquipmentIndex]->InteractableInterfaceProperties.bIsInteractable)
				{
					InitialEquipmentIndex = LevelEquipmentIndex;
					break;
				}
			}

			float MinDistance = FVector::Distance(EquipInLevel[InitialEquipmentIndex]->GetActorLocation(), NPC->GetActorLocation());

			FVector TargetLocation = EquipInLevel[0]->GetActorLocation();
			TSoftObjectPtr<AExerciseEquipment_OM> ClosestEquipment = EquipInLevel[0];
			for (size_t LevelEquipmentIndex = 0; LevelEquipmentIndex < EquipInLevel.Num(); LevelEquipmentIndex++)
			{
				if (LevelEquipmentIndex == InitialEquipmentIndex) continue;
				if (!EquipInLevel[LevelEquipmentIndex]->InteractableInterfaceProperties.bIsInteractable) continue;
				float TempDistance = FVector::Distance(EquipInLevel[LevelEquipmentIndex]->GetActorLocation(), NPC->GetActorLocation());
				if (TempDistance < MinDistance)
				{
					MinDistance = TempDistance;
					TargetLocation = FVector(
											static_cast<int16>(EquipInLevel[LevelEquipmentIndex]->GetActorLocation().X),
											static_cast<int16>(EquipInLevel[LevelEquipmentIndex]->GetActorLocation().Y),
											5.f);
					ClosestEquipment = EquipInLevel[LevelEquipmentIndex];
				}
			}
			
			if (const auto* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation ProjectedLocation;
				bool bFoundLocation = NavSys && NavSys->ProjectPointToNavigation(
					TargetLocation,
					ProjectedLocation,
					FVector(100.f, 100.f, 200.f)
				);
				if (bFoundLocation)
					TargetLocation = ProjectedLocation.Location;
				else
					return EBTNodeResult::Failed;

				NPC->SetCurrentInteractedItem(ClosestEquipment.Get());
				FNavLocation Loc;
				Loc.Location = TargetLocation;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);

				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Current Interacted Object"), ClosestEquipment.Get());
				ClosestEquipment->SetIsInteractable(false);

				//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}