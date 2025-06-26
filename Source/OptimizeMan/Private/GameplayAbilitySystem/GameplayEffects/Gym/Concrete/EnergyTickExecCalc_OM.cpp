// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyTickExecCalc_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"

UEnergyTickExecCalc_OM::UEnergyTickExecCalc_OM()
{
}

void UEnergyTickExecCalc_OM::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	

	constexpr float EnergyDrainPerSecond = -0.001f;

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(UGymSpecificStats_OM::GetEnergyAttribute(), EGameplayModOp::Additive, EnergyDrainPerSecond));
	

}
