// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Utils/Structs/ExerciseData.h"
#include "BTTask_DoWorkout.generated.h"

class ANpcBase_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UBTTask_DoWorkout : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_DoWorkout(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void EnterExercisePosition(class AExerciseEquipment_OM* InEquipment);
	void RandSetWorkoutType(const EExerciseType InType1, const EExerciseType InType2, const EExerciseType InType3);

private:
	UPROPERTY()
	ANpcBase_OM* NPC;
};
