// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Gym/Abstract/ExerciseEquipment_OM.h"
#include "FlatBench_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AFlatBench_OM : public AExerciseEquipment_OM
{
	GENERATED_BODY()
public:
	AFlatBench_OM();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	UStaticMeshComponent* Barbell;
	
};
