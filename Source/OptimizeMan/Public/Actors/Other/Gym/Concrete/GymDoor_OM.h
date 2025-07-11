// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Abstract/Door.h"
#include "GymDoor_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AGymDoor_OM : public ADoor
{
	GENERATED_BODY()

public:
	AGymDoor_OM();

	virtual void Interact_Implementation() override;

	virtual void ClearTimers() override;
	
};
