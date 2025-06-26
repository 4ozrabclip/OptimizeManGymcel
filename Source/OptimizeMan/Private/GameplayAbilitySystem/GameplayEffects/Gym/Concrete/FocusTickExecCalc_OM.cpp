// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTickExecCalc_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"

UFocusTickExecCalc_OM::UFocusTickExecCalc_OM()
{
}

void UFocusTickExecCalc_OM::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	/*FGameplayTagContainer AggregatedTags;
	ExecutionParams.GetOwningSpec().GetAllAssetTags(AggregatedTags);
	

	const FGameplayTag IdleStateTag = FGameplayTag::RequestGameplayTag(TEXT("State.Idle"));
	const FGameplayTag GymLevelTag  = FGameplayTag::RequestGameplayTag(TEXT("Level.Gym"));

	if (!AggregatedTags.HasTag(IdleStateTag) || !AggregatedTags.HasTag(GymLevelTag))
		return;*/
	
	constexpr float FocusDrainPerSecond = -0.001f;

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(UGymSpecificStats_OM::GetFocusAttribute(), EGameplayModOp::Additive, FocusDrainPerSecond));
	
}
