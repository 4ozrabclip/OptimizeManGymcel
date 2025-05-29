// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Controllers/NPC_AIController_OM.h"
#include "Actors/Characters/NPC/NpcBase_OM.h"
#include "BehaviorTree/BehaviorTree.h"

ANPC_AIController_OM::ANPC_AIController_OM(const FObjectInitializer& ObjectInitializer)
{
	Npc = nullptr;
	
}

void ANPC_AIController_OM::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
}

void ANPC_AIController_OM::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!Npc) return;

	UE_LOG(LogTemp, Warning, TEXT("%.2f"), TimeSinceLastActivityChange);

	// ---- This will not be walking in the future
	if (Npc->GetCurrentState() == ENpcState::Walking)
	{
		TimeSinceLastActivityChange += DeltaSeconds;

		if (TimeSinceLastActivityChange >= 5.f)
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
	int DiceRoll = FMath::RandRange(1, 3);
	

	switch (DiceRoll)
	{
		case 1:
			UE_LOG(LogTemp, Warning, TEXT("DICE ROLL WALKING"));
			Npc->SetCurrentState(ENpcState::Walking);
			break;
		case 2:
			UE_LOG(LogTemp, Warning, TEXT("DICE ROLL Talking"));
			Npc->SetIsOpenForConversation(true);
			Npc->SetCurrentState(ENpcState::TalkingWithNpc);
			break;
		case 3:
			UE_LOG(LogTemp, Warning, TEXT("DICE ROLL Working Out"));
			Npc->SetCurrentState(ENpcState::WorkingOut);
			break;
		default:
			break;
	}
	TimeSinceLastActivityChange = 0.f;
	
}
void ANPC_AIController_OM::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Error, TEXT("POSSESS CALLED"));
	Npc = Cast<ANpcBase_OM>(InPawn);
	if (Npc)
	{
		UE_LOG(LogTemp, Error, TEXT("NPC CASTED ON POSSESS "));
		if (auto* Tree = Npc->GetBehaviorTree())
		{
			UE_LOG(LogTemp, Error, TEXT("BB COMPONENT FOUND"));
			UBlackboardComponent* b;
			UseBlackboard(Tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(Tree);

			SetActorTickEnabled(true);
		}
	}
}
