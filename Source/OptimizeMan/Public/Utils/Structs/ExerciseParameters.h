#pragma once
#include "CoreMinimal.h"
#include "ExerciseParameters.generated.h"

USTRUCT(BlueprintType)
struct FExerciseParameters
{
	GENERATED_USTRUCT_BODY()

	FExerciseParameters()
	: SquatsEnergyUse(-0.1f),
	BicepCurlEnergyUse(-0.1f),
	OverheadPressEnergyUse(-0.1f),
	LowerBodyIncrease(0.055f),
	ArmIncrease(0.055f),
	ShoulderIncrease(0.055f)
	{}
	
	UPROPERTY(VisibleAnywhere)
	float SquatsEnergyUse;
	UPROPERTY(VisibleAnywhere)
	float BicepCurlEnergyUse;
	UPROPERTY(VisibleAnywhere)
	float OverheadPressEnergyUse;
	
	UPROPERTY(VisibleAnywhere)
	float LowerBodyIncrease;
	UPROPERTY(VisibleAnywhere)
	float ArmIncrease;
	UPROPERTY(VisibleAnywhere)
	float ShoulderIncrease;


	void UpdateParameters(class UGameInstance_OMG* GameInstance);

	
};
