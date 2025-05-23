// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_TurnToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UBTTask_TurnToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_TurnToPlayer(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	
};
