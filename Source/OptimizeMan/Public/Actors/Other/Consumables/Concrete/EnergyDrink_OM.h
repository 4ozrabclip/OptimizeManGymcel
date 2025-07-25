// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Consumables/Abstract/Consumable_OM.h"
#include "EnergyDrink_OM.generated.h"

class UUseEnergyDrink_OM;

UCLASS()
class OPTIMIZEMAN_API AEnergyDrink_OM : public AConsumable_OM
{
	GENERATED_BODY()
public:
	AEnergyDrink_OM();
protected:
	virtual void BeginPlay() override;


public:
};
