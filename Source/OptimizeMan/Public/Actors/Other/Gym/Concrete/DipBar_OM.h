// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Gym/Abstract/CompoundEquipment_OM.h"
#include "DipBar_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API ADipBar_OM : public ACompoundEquipment_OM
{
	GENERATED_BODY()
public:
	ADipBar_OM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
