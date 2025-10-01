// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/UseEnergyDrinkExecCalc_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"

UUseEnergyDrinkExecCalc_OM::UUseEnergyDrinkExecCalc_OM()
{
}

void UUseEnergyDrinkExecCalc_OM::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(UGymSpecificStats_OM::GetEnergyAttribute(), EGameplayModOp::Override, 1.f));
	
	/*FGameplayModifierInfo Mod;
	Mod.Attribute = UGymSpecificStats_OM::GetFocusAttribute();
	Mod.ModifierOp = EGameplayModOp::Additive;
	Mod.ModifierMagnitude = FScalableFloat(0.7f);
	Modifiers.Add(Mod);
	FGameplayModifierInfo Mod2;
	Mod2.Attribute = UGymSpecificStats_OM::GetEnergyAttribute();
	Mod2.ModifierOp = EGameplayModOp::Additive;
	Mod2.ModifierMagnitude = FScalableFloat(0.6f);
	Modifiers.Add(Mod2);

	FGameplayTagContainer Tags = GetGrantedTags();
	Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Status.EnergyDrink")));*/
	
}
