// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTick_OM.h"
#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTickExecCalc_OM.h"
#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"

UFocusTick_OM::UFocusTick_OM()
{
	FGameplayEffectExecutionDefinition ExecDef;
	ExecDef.CalculationClass = UFocusTickExecCalc_OM::StaticClass();
	Executions.Add(ExecDef);
	
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 0.25f;



	//TagReqComp = CreateDefaultSubobject<UTargetTagRequirementsGameplayEffectComponent>(TEXT("TargetTagRequirements"));

}
