// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/BladderTick_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/BladderTickExecCalc_OM.h"

UBladderTick_OM::UBladderTick_OM()
{
	FGameplayEffectExecutionDefinition ExecDef;
	ExecDef.CalculationClass = UBladderTickExecCalc_OM::StaticClass();
	Executions.Add(ExecDef);

	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 1.f;
}

