// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_TalkWithNpc.h"

#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"

UBTTask_TalkWithNpc::UBTTask_TalkWithNpc(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Talk With Npc";
}

EBTNodeResult::Type UBTTask_TalkWithNpc::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		if (auto* NPC = Cast<ANpcBase_OM>(Cont->GetCharacter()))
		{
			NPC->SayHello();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
