// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_FindNpcToTalk.h"

#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindNpcToTalk::UBTTask_FindNpcToTalk(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Find Talkable Npc";
	ThisNpc = nullptr;
}

EBTNodeResult::Type UBTTask_FindNpcToTalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		if (auto* NPC = Cast<ANpcBase_OM>(Cont->GetCharacter()))
		{
			ThisNpc = NPC;

			ClosestNpc = ThisNpc->GetNpcsInLevel()[0];

			if (!ClosestNpc->GetIsOpenForConversation())
			{
				ThisNpc->SetCurrentState(ENpcState::Walking);
				return EBTNodeResult::Failed;
			}
			//FindOtherNpcsAvailableForConvo();

			if (ClosestNpc)
			{
				if (ClosestNpc->GetCurrentState() == ENpcState::TalkingWithNpc)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("Interacted Npc In TalkMode"), true);
				}
				else
				{
					ClosestNpc->SetCurrentState(ENpcState::TalkingWithNpc);
					OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("Interacted Npc In TalkMode"), true);
				}
				
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Current Interacted Npc"), ClosestNpc.Get());
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}

void UBTTask_FindNpcToTalk::FindOtherNpcsAvailableForConvo()
{
	if (ThisNpc->GetNpcsInLevel().Num() < 1) return;
	
	for (TSoftObjectPtr<ANpcBase_OM>& Npc : ThisNpc->GetNpcsInLevel())
	{
		if (Npc->GetIsOpenForConversation())
		{
			OtherNpcs.Add(Npc);
		}
	}
	FindClosestNpcAvailable();
}

void UBTTask_FindNpcToTalk::FindClosestNpcAvailable()
{
	ClosestNpc = OtherNpcs[0];

	float MinDistance = FVector::Distance(ClosestNpc->GetActorLocation(), ThisNpc->GetActorLocation());

	for (size_t NpcIndex = 1; NpcIndex < OtherNpcs.Num(); ++NpcIndex)
	{
		float TempDistance = FVector::Distance(OtherNpcs[NpcIndex]->GetActorLocation(), ThisNpc->GetActorLocation());

		if (TempDistance < MinDistance && OtherNpcs[NpcIndex]->GetIsOpenForConversation())
		{
			MinDistance = TempDistance;
			ClosestNpc = OtherNpcs[NpcIndex];
		}
	}
	
	if (ClosestNpc->GetCurrentInteractedNpc() != ThisNpc && ClosestNpc->GetCurrentState() != ENpcState::TalkingWithNpc)
	{
		ClosestNpc->SetCurrentState(ENpcState::TalkingWithNpc);
		ClosestNpc->SetCurrentInteractedNpc(ThisNpc);
	}
	
	ClosestNpc->SetIsInConversationWithNpc(true);
	ThisNpc->SetIsInConversationWithNpc(true);
	//ClosestNpc->SetIsOpenForConversation(false);
	//ThisNpc->SetIsOpenForConversation(false);
	
}