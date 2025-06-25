// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyTick_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyTickExecCalc_OM.h"

UEnergyTick_OM::UEnergyTick_OM()
{
	FGameplayEffectExecutionDefinition ExecDef;
	ExecDef.CalculationClass = UEnergyTickExecCalc_OM::StaticClass();
	Executions.Add(ExecDef);
	
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 1.f;



}
