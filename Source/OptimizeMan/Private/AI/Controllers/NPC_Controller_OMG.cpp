// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Controllers/NPC_Controller_OMG.h"

#include "Actors/Characters/NPC/Abstract/NpcBase_OMG.h"
#include "BehaviorTree/BehaviorTree.h"


ANPC_Controller_OMG::ANPC_Controller_OMG()
{
	PrimaryActorTick.bCanEverTick = true;
	Npc = nullptr;
}
void ANPC_Controller_OMG::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Npc = Cast<ANpcBase_OMG>(InPawn);
	if (Npc)
	{
		if (auto* Tree = Npc->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(Tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(Tree);

			SetActorTickEnabled(true);
		}
	}
}

void ANPC_Controller_OMG::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC_Controller_OMG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	// ---- This will not be walking in the future
	if (Npc->GetCurrentState() == ENpcState::Walking)
	{
		TimeSinceLastActivityChange += DeltaTime;

		if (TimeSinceLastActivityChange >= RandDurationBetweenRolls)
		{
			ActivityChangeDiceRoll();
		}
	}
	else
	{
		TimeSinceLastActivityChange = 0.f;
	}
}


void ANPC_Controller_OMG::ActivityChangeDiceRoll()
{
	int DiceRoll = FMath::RandRange(1, 8);

	UE_LOG(LogTemp, Display, TEXT("DiceRoll: %d"), DiceRoll);
	
	switch (DiceRoll)
	{
	case 1:
	case 2:
	case 3:
		Npc->SetIsOpenForConversation(false);
		Npc->SetCurrentState(ENpcState::Walking);
		break;
	case 4:
	case 5:
	case 6:
		Npc->SetIsOpenForConversation(true);
		Npc->SetCurrentState(ENpcState::TalkingWithNpc);
		break;
	case 7:
	case 8:
		Npc->SetIsOpenForConversation(false);
		if (Npc->GetCurrentState() == ENpcState::TalkingWithNpc)
			Npc->SetCurrentState(ENpcState::Walking);
		else
			Npc->SetCurrentState(ENpcState::WorkingOut);
		break;
	default:
		break;
	}
	TimeSinceLastActivityChange = 0.f;
	RandDurationBetweenRolls = FMath::RandRange(10.f, 20.f);
}