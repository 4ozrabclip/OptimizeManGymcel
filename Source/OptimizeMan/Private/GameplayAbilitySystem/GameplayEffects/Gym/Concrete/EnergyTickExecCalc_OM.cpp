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

	
	
	FGameplayTagContainer AggregatedTags;
	ExecutionParams.GetOwningSpec().GetAllAssetTags(AggregatedTags);

	const FGameplayTag IdleStateTag = FGameplayTag::RequestGameplayTag(TEXT("State.Idle"));
	const FGameplayTag GymLevelTag  = FGameplayTag::RequestGameplayTag(TEXT("Level.Gym"));
	const FGameplayTag FocusHighTag = FGameplayTag::RequestGameplayTag(TEXT("Stats.Gym.Focus.High"));

	if (!AggregatedTags.HasTag(IdleStateTag) || !AggregatedTags.HasTag(GymLevelTag))
		return;
	
	if (AggregatedTags.HasTag(FocusHighTag))
		return;

	

	constexpr float EnergyDrainPerSecond = -0.00005f;

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(UGymSpecificStats_OM::GetEnergyAttribute(), EGameplayModOp::Additive, EnergyDrainPerSecond));
	

}
