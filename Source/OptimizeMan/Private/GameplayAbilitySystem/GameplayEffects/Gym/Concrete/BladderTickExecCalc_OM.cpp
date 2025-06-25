// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/BladderTickExecCalc_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"

UBladderTickExecCalc_OM::UBladderTickExecCalc_OM()
{
}

void UBladderTickExecCalc_OM::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	OutExecutionOutput.AddOutputModifier(
	FGameplayModifierEvaluatedData(UGymSpecificStats_OM::GetBladderAttribute(), EGameplayModOp::Additive, 0.00005f));
}
