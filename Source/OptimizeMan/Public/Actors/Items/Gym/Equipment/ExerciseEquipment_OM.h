// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptimizeMan/Public/Actors/InteractableActor_OM.h"
#include "Utils/Structs/ExerciseData.h"
#include "ExerciseEquipment_OM.generated.h"
class UWidgetComponent;
class AGymCamera;
/*
 * Parent of all exercise equipment
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API AExerciseEquipment_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
	
public:	
	AExerciseEquipment_OM();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void TurnOffWidget();
	
	virtual void Interact_Implementation() override;
	void StartWorkoutMode();
	virtual void ChangeWeight(float InWeight);
	virtual void SetWeightClass();


	
	FRotator GetLookAtCameraRotation() const;
	FVector GetLookAtCameraPosition() const;
	FTransform GetOriginalPosition() const;
	AActor* GetGymCamera() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UWidgetComponent* SelectWorkoutWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	AGymCamera* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Position")
	FRotator LookAtCameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Position")
	FVector LookAtCameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weights")
	TArray<FEquipmentData> Equipment;



	EWeightClass CurrentWeightClass;
	float CurrentWeight;
	
	FTransform OriginalPosition;

	

	
	
};
