// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptimizeMan/Public/Actors/InteractableActor_OM.h"
#include "ExerciseEquipment_OM.generated.h"
/*
 * Parent of all exercise equipment
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API AExerciseEquipment_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
	
public:	
	AExerciseEquipment_OM();
	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;

	FRotator GetLookAtCameraRotation() const;
	FVector GetLookAtCameraPosition() const;
	FTransform GetOriginalPosition() const;
	AActor* GetGymCamera() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class AGymCamera* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Position")
	FRotator LookAtCameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Position")
	FVector LookAtCameraPosition;

	FTransform OriginalPosition;

	
	
};
