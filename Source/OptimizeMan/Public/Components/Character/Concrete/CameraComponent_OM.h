// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraComponent_OM.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EFieldOfVisionState : uint8
{
	Default UMETA(DisplayName = "Default"),
	Phasing UMETA(DisplayName = "Phasing"),
	Tight	UMETA(DisplayName = "Tight"),
	Wide	UMETA(DisplayName = "Wide"),
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OPTIMIZEMAN_API UCameraComponent_OM : public UCineCameraComponent
{
	GENERATED_BODY()
public:
	UCameraComponent_OM();
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ManageFOVTick(float DeltaTime);



public:
	/** Setters **/
	UFUNCTION(BlueprintCallable, Category = "Fov State")
	void SetFOVState(EFieldOfVisionState InFOVState);


	EFieldOfVisionState GetFOVState() const { return FOVState; };

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float FastLerpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float SlowLerpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float DefaultLerpSpeed;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float WideFOV; // ------- Check Range
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float TightFOV;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float PhaseSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float PhaseAmplitude;


private:
	bool bReturnToDefault = false;
	float DefaultFOV;

	bool bFOVAtTarget = false;


	float TargetFOV;


	EFieldOfVisionState FOVState = EFieldOfVisionState::Default;


	float TimeAccumulator = 0.f;



	FTimerHandle FovShiftHandle;

};
