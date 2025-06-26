// Copyright © 2025 4ozStudio. All rights reserved.



#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyTick_OM.h"
#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyTickExecCalc_OM.h"

UEnergyTick_OM::UEnergyTick_OM()
{
	FGameplayEffectExecutionDefinition ExecDef;
	ExecDef.CalculationClass = UEnergyTickExecCalc_OM::StaticClass();
	Executions.Add(ExecDef);
	
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 0.25f;
	

	TagReqComp = CreateDefaultSubobject<UTargetTagRequirementsGameplayEffectComponent>(TEXT("TargetTagRequirements"));

}

void UEnergyTick_OM::PostInitProperties()
{
	Super::PostInitProperties();
	FGameplayTagRequirements RequiredTags;
	RequiredTags.RequireTags.AddTag(FGameplayTag::RequestGameplayTag("State.Idle"));
	RequiredTags.RequireTags.AddTag(FGameplayTag::RequestGameplayTag("Level.Gym"));
	RequiredTags.IgnoreTags.AddTag(FGameplayTag::RequestGameplayTag("Stats.Gym.Focus.High"));

	if (TagReqComp)
		TagReqComp->OngoingTagRequirements = RequiredTags;
	

	
}
