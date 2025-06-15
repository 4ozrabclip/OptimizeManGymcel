// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/EnergyDrink_OM.h"


AEnergyDrink_OM::AEnergyDrink_OM()
{
	ConsumableType.Name = FName("Energy Drink");
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Bladder, 5);
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Energy, 5);
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Focus, 3);
	ConsumableType.LifeTime = 60*3;
	
}

void AEnergyDrink_OM::BeginPlay()
{
	Super::BeginPlay();
	
}
