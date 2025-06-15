// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Gym/Abstract/CompoundEquipment_OM.h"
#include "Dumbell_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ADumbell_OM : public ACompoundEquipment_OM
{
	GENERATED_BODY()

public:
	ADumbell_OM();

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* ExtraCollider;

	
};
