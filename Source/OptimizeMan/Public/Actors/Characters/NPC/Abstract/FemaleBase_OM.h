// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "NpcBase_OM.h"
#include "FemaleBase_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AFemaleBase_OM : public ANpcBase_OM
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;
	
};
