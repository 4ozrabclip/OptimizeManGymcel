// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Consumables/Concrete/EnergyDrink_OM.h"


AEnergyDrink_OM::AEnergyDrink_OM()
{
	ConsumableType.Name = EConsumableName::EnergyDrink;
	ConsumableType.NameString = FString("EnergyDrink");
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Bladder, 5);
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Energy, 5);
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Focus, 3);
	ConsumableType.LifeTime = 60*3;
	ConsumableType.Price = 1;
	
}

void AEnergyDrink_OM::BeginPlay()
{
	Super::BeginPlay();
	
}
