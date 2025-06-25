// Copyright © 2025 4ozStudio. All rights reserved.


#include "OptimizeMan/Public/GameplayAbilitySystem/GameplayEffects/Gym/Concrete/UseEnergyDrink_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"

UUseEnergyDrink_OM::UUseEnergyDrink_OM()
{
	FGameplayTagContainer Tags = GetGrantedTags();
	Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Status.EnergyDrink")));
	
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo Mod;
	Mod.Attribute = UGymSpecificStats_OM::GetFocusAttribute();
	Mod.ModifierOp = EGameplayModOp::Additive;
	Mod.ModifierMagnitude = FScalableFloat(0.7f);
	Modifiers.Add(Mod);
	FGameplayModifierInfo Mod2;
	Mod2.Attribute = UGymSpecificStats_OM::GetEnergyAttribute();
	Mod2.ModifierOp = EGameplayModOp::Additive;
	Mod2.ModifierMagnitude = FScalableFloat(0.6f);
	Modifiers.Add(Mod2);

}
