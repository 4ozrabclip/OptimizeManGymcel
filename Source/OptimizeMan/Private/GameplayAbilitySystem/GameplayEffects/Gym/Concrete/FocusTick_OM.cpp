// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTick_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTickExecCalc_OM.h"

UFocusTick_OM::UFocusTick_OM()
{
	FGameplayTagContainer Tags = GetGrantedTags();
	Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Effect.FocusDrain")));
	FGameplayEffectExecutionDefinition ExecDef;
	ExecDef.CalculationClass = UFocusTickExecCalc_OM::StaticClass();
	Executions.Add(ExecDef);
	
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 1.f;
}
