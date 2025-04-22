// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/NPC_AIController_OM.h"

#include "Actors/Characters/NPC/NpcBase_OM.h"
#include "BehaviorTree/BehaviorTree.h"

ANPC_AIController_OM::ANPC_AIController_OM(const FObjectInitializer& ObjectInitializer)
{
}

void ANPC_AIController_OM::BeginPlay()
{
	Super::BeginPlay();
}


void ANPC_AIController_OM::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto* Npc = Cast<ANpcBase_OM>(InPawn))
	{
		if (auto* Tree = Npc->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(Tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(Tree);
		}
	}
}
