// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/NPC/Abstract/MaleBase_OM.h"
#include "GymGuy1_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AGymGuy1_OM : public AMaleBase_OM
{
	GENERATED_BODY()
public:
	AGymGuy1_OM();

	virtual void BeginPlay() override;
	
};
