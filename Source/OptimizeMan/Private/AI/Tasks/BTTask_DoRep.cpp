// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_DoRep.h"

#include "Actors/Characters/NPC/NpcBase_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "AnimInstances/NpcBaseAnimInstance_OM.h"

UBTTask_DoRep::UBTTask_DoRep(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Do a Single Rep";
}

EBTNodeResult::Type UBTTask_DoRep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		if (auto* NPC = Cast<ANpcBase_OM>(Cont->GetCharacter()))
		{
			if (UNpcBaseAnimInstance_OM* AnimInstance = NPC->GetAnimInstance())
			{
				AnimInstance->DoSquatRep();
				FTimerDelegate TimerDel;
				TimerDel.BindLambda([this, &OwnerComp]()
				{
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				});

				GetWorld()->GetTimerManager().SetTimer(RepTimerHandle, TimerDel, 4.f, false);

				return EBTNodeResult::InProgress; // tell BT this task is still running
			}
		}
	}
	return EBTNodeResult::Failed;
}
