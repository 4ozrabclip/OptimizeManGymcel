// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NonInteractableActor_OM.generated.h"

UCLASS(Abstract)
class OPTIMIZEMAN_API ANonInteractableActor_OM : public AActor
{
	GENERATED_BODY()
public:
	ANonInteractableActor_OM();

protected:
	virtual void BeginPlay() override;
};
