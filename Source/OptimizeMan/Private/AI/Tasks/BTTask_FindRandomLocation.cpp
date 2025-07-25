// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_FindRandomLocation.h"
#include "Utils/Structs/NpcStates.h"
#include "NavigationSystem.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		if (auto* Npc = Cont->GetPawn().Get())
		{
			const FVector Origin = Npc->GetActorLocation();

			if (const auto* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}
				
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

				return EBTNodeResult::Succeeded;
			}
			
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, "FAILED TO FIND RANDOM LOCATION");
	return EBTNodeResult::Failed;
	
}