// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/Door.h"
#include "BedroomDoor_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ABedroomDoor_OM : public ADoor
{
	GENERATED_BODY()

public:
	ABedroomDoor_OM();

	virtual void Interact_Implementation() override;
};
