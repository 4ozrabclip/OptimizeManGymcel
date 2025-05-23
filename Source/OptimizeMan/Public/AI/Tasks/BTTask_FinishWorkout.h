// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Utils/Structs/ExerciseData.h"
#include "BTTask_FinishWorkout.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UBTTask_FinishWorkout : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_FinishWorkout(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void DetachEquipment();
	void ExitAnim(EExerciseType InExerciseType);

private:
	UPROPERTY()
	class AExerciseEquipment_OM* Equipment;
	UPROPERTY()
	class ANpcBase_OM* NPC;
	
};
