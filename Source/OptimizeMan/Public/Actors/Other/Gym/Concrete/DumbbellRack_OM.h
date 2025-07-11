// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentRack_OM.h"
#include "DumbbellRack_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ADumbbellRack_OM : public AEquipmentRack_OM
{
	GENERATED_BODY()
public:
	ADumbbellRack_OM();

	virtual void BeginPlay() override;


	virtual void Interact_Implementation() override;
};
