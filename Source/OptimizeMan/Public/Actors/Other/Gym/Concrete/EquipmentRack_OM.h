// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Abstract/InteractableActor_OM.h"
#include "GameFramework/Actor.h"
#include "EquipmentRack_OM.generated.h"

class AExerciseEquipment_OM;

UCLASS()
class OPTIMIZEMAN_API AEquipmentRack_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
	
public:	
	AEquipmentRack_OM();

protected:
	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExerciseEquipment")
	AExerciseEquipment_OM* Equipment;
	
};
