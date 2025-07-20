// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyNegateHitExecCalc_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"

UEnergyNegateHitExecCalc_OM::UEnergyNegateHitExecCalc_OM()
{
}

void UEnergyNegateHitExecCalc_OM::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	constexpr float NegativeHitValue = -0.1f;
	
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(UGymSpecificStats_OM::GetEnergyAttribute(), EGameplayModOp::Additive, NegativeHitValue));
	
}
