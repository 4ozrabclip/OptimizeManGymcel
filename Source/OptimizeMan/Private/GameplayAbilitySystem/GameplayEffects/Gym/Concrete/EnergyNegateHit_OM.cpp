// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyNegateHit_OM.h"

#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyNegateHitExecCalc_OM.h"

UEnergyNegateHit_OM::UEnergyNegateHit_OM()
{
	FGameplayEffectExecutionDefinition ExecDef;
    ExecDef.CalculationClass = UEnergyNegateHitExecCalc_OM::StaticClass();
    Executions.Add(ExecDef);
    
    DurationPolicy = EGameplayEffectDurationType::Instant;
    Period = 0.f;
}
