// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/GymEnergyDrain_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"

UGymEnergyDrain_OM::UGymEnergyDrain_OM()
{
	FGameplayTagContainer Tags = GetGrantedTags();
	Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Effect.EnergyDrain")));

	FGameplayModifierInfo Mod;
	Mod.Attribute = UGymSpecificStats_OM::GetEnergyAttribute();
	Mod.ModifierOp = EGameplayModOp::Additive;
	Mod.ModifierMagnitude = FScalableFloat(-0.0005f);
	Mod.SourceTags.RequireTags.AddTag(FGameplayTag::RequestGameplayTag("State.Idle"));
	Mod.SourceTags.RequireTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Level.Gym")));
	Modifiers.Add(Mod);

	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 1.f;
}
