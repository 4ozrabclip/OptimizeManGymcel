// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_CheckLocation.h"

#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckLocation::UBTTask_CheckLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Check Target Location";
	LocationTolerance = 20.f;
}

EBTNodeResult::Type UBTTask_CheckLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		if (auto* NPC = Cast<ANpcBase_OM>(Cont->GetCharacter()))
		{
			TSoftObjectPtr<ANpcBase_OM> OtherNpc = NPC->GetCurrentInteractedNpc();

			if (!OtherNpc)
				return EBTNodeResult::Failed;

			FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("TargetLocation"));

			const bool bThisNpcAtTarget = FVector::DistSquared2D(NPC->GetActorLocation(), TargetLocation) < FMath::Square(LocationTolerance);
			const bool bOtherNpcAtTarget = FVector::DistSquared2D(OtherNpc->GetActorLocation(), TargetLocation) < FMath::Square(LocationTolerance);

			if (bThisNpcAtTarget && bOtherNpcAtTarget)
				return EBTNodeResult::Succeeded;
			
			return EBTNodeResult::Failed;
			
		}
	}

	return EBTNodeResult::Failed;

}
