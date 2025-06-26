// Copyright © 2025 4ozStudio. All rights reserved.


#include "OptimizeMan/Public/GameplayAbilitySystem/GameplayEffects/Gym/Concrete/UseEnergyDrink_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/UseEnergyDrinkExecCalc_OM.h"

UUseEnergyDrink_OM::UUseEnergyDrink_OM()
{
	FGameplayEffectExecutionDefinition ExecDef;
	ExecDef.CalculationClass = UUseEnergyDrinkExecCalc_OM::StaticClass();
	Executions.Add(ExecDef);
	
	DurationPolicy = EGameplayEffectDurationType::Instant;
	Period = 1.f;
}
