// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_ChangeState.h"

#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"

UBTTask_ChangeState::UBTTask_ChangeState(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Change NPC State";
}

EBTNodeResult::Type UBTTask_ChangeState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		if (auto* NPC = Cast<ANpcBase_OM>(Cont->GetCharacter()))
		{
			NPC->SetCurrentState(ENpcState::Walking);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
