// Copyright © 2025 4ozStudio. All rights reserved.


#include "AI/Tasks/BTTask_DoRep.h"

#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "AnimInstances/NpcBaseAnimInstance_OM.h"

UBTTask_DoRep::UBTTask_DoRep(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Do a Single Rep";
	NPC = nullptr;
	AnimInstance = nullptr;
	MaxReps = 2;
}

EBTNodeResult::Type UBTTask_DoRep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* Cont = Cast<ANPC_AIController_OM>(OwnerComp.GetAIOwner()))
	{
		NPC = Cast<ANpcBase_OM>(Cont->GetCharacter());
		if (NPC)
		{
			AnimInstance = NPC->GetAnimInstance();
			if (AnimInstance)
			{
				MaxReps = FMath::RandRange(2, 6);
				
				DoSingleRep(OwnerComp);

				FTimerManager& TimerManager = GetWorld()->GetTimerManager();

				TimerManager.ClearTimer(RepTimerHandle);

				FTimerDelegate TimerDel;
				TimerDel.BindLambda([this, &OwnerComp]()
				{
					DoSingleRep(OwnerComp);
				});
				TimerManager.SetTimer(RepTimerHandle, TimerDel, 0.7f, true);

				//UE_LOG(LogTemp, Error, TEXT("RepCount: %d"), RepCount);
				return EBTNodeResult::InProgress;
				}
			}
		}
	return EBTNodeResult::Failed;
}

void UBTTask_DoRep::DoSingleRep(UBehaviorTreeComponent& OwnerComp)
{
	//if (RepCount >= MaxReps)
	//{
	//	GetWorld()->GetTimerManager().ClearTimer(RepTimerHandle);
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}
	if (RepCount == MaxReps - 1)
	{
		AnimInstance->DoSquatRep();
		GetWorld()->GetTimerManager().ClearTimer(RepTimerHandle);
		FTimerDelegate TimerDel;
		TimerDel.BindLambda([this, &OwnerComp]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});
		GetWorld()->GetTimerManager().SetTimer(RepTimerHandle, TimerDel, 4.f, false);
	}
	if (!AnimInstance->GetIsSquatting())
	{
		RepCount++;
	}
}