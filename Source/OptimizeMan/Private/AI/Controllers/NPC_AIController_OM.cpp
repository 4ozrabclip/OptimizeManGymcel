// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Controllers/NPC_AIController_OM.h"
#include "Actors/Characters/NPC/NpcBase_OM.h"
#include "BehaviorTree/BehaviorTree.h"

ANPC_AIController_OM::ANPC_AIController_OM(const FObjectInitializer& ObjectInitializer)
{
	Npc = nullptr;

	PrimaryActorTick.bCanEverTick = true;
	
	
}

void ANPC_AIController_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC_AIController_OM::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!Npc)
	{
		UE_LOG(LogTemp, Error, TEXT("NPC_AIController_OM::Tick No NPC"));
	}
	

	// ---- This will not be walking in the future
	if (Npc->GetCurrentState() == ENpcState::Walking)
	{
		TimeSinceLastActivityChange += DeltaSeconds;

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

void ANPC_AIController_OM::ActivityChangeDiceRoll()
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
void ANPC_AIController_OM::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Npc = Cast<ANpcBase_OM>(InPawn);
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
