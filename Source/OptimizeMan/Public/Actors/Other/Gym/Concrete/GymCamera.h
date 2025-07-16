// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Utils/Structs/PlayerData.h"
#include "GymCamera.generated.h"

UCLASS()
class OPTIMIZEMAN_API AGymCamera : public ACameraActor
{
	GENERATED_BODY()
public:	
	AGymCamera();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION()
	void OnEmotionalStateChanged(EPlayerEmotionalStates NewState);

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform DoomerTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform GrindsetTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform CopeTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform GoblinTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform GigachadTransform;

	UPROPERTY()
	class UGameInstance_OM* GameInstance;

private:
	FTransform DefaultTransform;
	


	

};
