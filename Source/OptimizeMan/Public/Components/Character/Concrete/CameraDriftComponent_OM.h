// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/Abstract/CharacterComponentBase_OM.h"
#include "CameraDriftComponent_OM.generated.h"


class UCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OPTIMIZEMAN_API UCameraDriftComponent_OM : public UCharacterComponentBase_OM
{
	GENERATED_BODY()
public:
	UCameraDriftComponent_OM();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	float GetIntensity() const { return Intensity; }
	void SetIntensity(const float InValue) { Intensity = InValue; }

	void SetCamera(UCameraComponent* InCamera) { Camera = InCamera; }

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;


private:
	FRotator BaseRotation;

	float Intensity = 1.f;
};
