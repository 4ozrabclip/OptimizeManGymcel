// Copyright © 2025 4ozStudio. All rights reserved.


#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"


UGymSpecificStats_OM::UGymSpecificStats_OM()
{
	InitBladder(0.f);
	InitEnergy(1.f);
	InitFocus(1.f);
}

void UGymSpecificStats_OM::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);


	if (bCanTriggerEnergyLow)
	{
		if (float EnergyVal = GetEnergy())
		{
			if (EnergyVal <= 0.f)
			{
				OnEnergyEmpty.Broadcast();
				bCanTriggerEnergyLow = false;
			}
			else if (EnergyVal < EnergyThreshold)
			{
				OnEnergyBelowThreshold.Broadcast(EnergyVal);
				EnergyThreshold -= 0.1f;
			}
		}
	}
}
