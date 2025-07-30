// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CameraComponent_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UCameraComponent_OM : public UCameraComponent
{
	GENERATED_BODY()
public:
	UCameraComponent_OM();
protected:
	virtual void BeginPlay() override;
	
	
	UFUNCTION(BlueprintCallable)
	void FOVShift(bool bIncreaseFOV = true);
	UFUNCTION(BlueprintCallable)
	void FOVLerpToDefault();

	
	void LerpFOV(const float InterpSpeed, float TargetFOV);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float FOVShiftSpeed = 6.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float FOVLerpToDefaultSpeed = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float MaxFOV; // ------- Check Range
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fov Params")
	float MinFOV;


private:
	bool bReturnToDefault = false;
	float DefaultFOV;



	FTimerHandle FovShiftHandle;

};
