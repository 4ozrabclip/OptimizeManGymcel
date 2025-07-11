// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_TurnToPlayer.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_TurnToPlayer::UBTTask_TurnToPlayer(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Turn to actor";
}

EBTNodeResult::Type UBTTask_TurnToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		if (const auto* Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			if (auto* Npc = Cont->GetPawn().Get())
			{
				FVector PlayerDirection = (Player->GetActorLocation() - Npc->GetActorLocation()).GetSafeNormal();
				FRotator RotationToTurn = FRotationMatrix::MakeFromX(PlayerDirection).Rotator();
			
				Npc->SetActorRotation(RotationToTurn);

				OwnerComp.GetBlackboardComponent()->SetValueAsRotator(GetSelectedBlackboardKey(), RotationToTurn);
				//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
