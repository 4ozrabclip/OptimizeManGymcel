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

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(UGymSpecificStats_OM::GetFocusAttribute(), EGameplayModOp::Additive, -0.0000f));

	
//	Mod.SourceTags.RequireTags.AddTag(FGameplayTag::RequestGameplayTag("State.Idle"));
//	Mod.SourceTags.RequireTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Level.Gym")));
	
}
