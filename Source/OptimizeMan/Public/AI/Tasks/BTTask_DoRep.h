// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_DoRep.generated.h"

class UNpcBaseAnimInstance_OM;
class ANpcBase_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UBTTask_DoRep : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_DoRep(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	void DoSingleRep(UBehaviorTreeComponent& OwnerComp);

	UFUNCTION()
	void TickRep(UBehaviorTreeComponent* OwnerComp);

private:
	UPROPERTY()
	ANpcBase_OM* NPC;
	UPROPERTY()
	UNpcBaseAnimInstance_OM* AnimInstance;

	
	FTimerHandle RepTimerHandle;
	FTimerHandle FinalRepTimerHandle;

	int RepCount = 0;

	int MaxReps;



	
	
};

