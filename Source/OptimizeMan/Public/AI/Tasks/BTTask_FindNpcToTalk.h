// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindNpcToTalk.generated.h"

class ANpcBase_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UBTTask_FindNpcToTalk : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_FindNpcToTalk(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void FindOtherNpcsAvailableForConvo();
	void FindClosestNpcAvailable();

private:
	UPROPERTY()
	ANpcBase_OM* ThisNpc;

	UPROPERTY()
	TArray<TSoftObjectPtr<ANpcBase_OM>> OtherNpcs;
	
	TSoftObjectPtr<ANpcBase_OM> ClosestNpc;
};
