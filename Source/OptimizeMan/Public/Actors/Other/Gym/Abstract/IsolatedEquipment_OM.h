// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExerciseEquipment_OM.h"
#include "IsolatedEquipment_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API AIsolatedEquipment_OM : public AExerciseEquipment_OM
{
	GENERATED_BODY()
public:
	AIsolatedEquipment_OM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
