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
	// Sets default values for this actor's properties
	ALegPress_OM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
  