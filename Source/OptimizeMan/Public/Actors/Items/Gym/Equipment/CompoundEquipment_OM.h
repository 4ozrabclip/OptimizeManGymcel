// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExerciseEquipment_OM.h"
#include "CompoundEquipment_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API ACompoundEquipment_OM : public AExerciseEquipment_OM
{
	GENERATED_BODY()
public:
	ACompoundEquipment_OM();
protected:
	virtual void BeginPlay() override;
public:
	virtual void ChangeWeight(float InWeight) override;
};
