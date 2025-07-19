// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Gym/Abstract/IsolatedEquipment_OM.h"
#include "LegPress_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API ALegPress_OM : public AIsolatedEquipment_OM
{
	GENERATED_BODY()

public:
	ALegPress_OM();

protected:
	virtual void BeginPlay() override;

public:
};
  