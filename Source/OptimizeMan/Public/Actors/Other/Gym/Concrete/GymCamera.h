// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraActor.h"
#include "Utils/Structs/PlayerData.h"
#include "GymCamera.generated.h"
UENUM(BlueprintType)
enum class ECameraAutoState : uint8
{
	Idle,
	ZoomingIn,
	Hold,
	ZoomingOut
};
UCLASS()
class OPTIMIZEMAN_API AGymCamera : public ACineCameraActor
{
	GENERATED_BODY()
public:
	explicit AGymCamera(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION()
	void OnEmotionalStateChanged(EPlayerEmotionalStates NewState);


	UPROPERTY(EditAnywhere, Category = "Automation")
	ECameraAutoState AutoState = ECameraAutoState::Idle;

	UPROPERTY(EditAnywhere, Category = "Automation")
	float ZoomedFOV = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Automation")
	float NormalFOV = 60.0f;

	UPROPERTY(EditAnywhere, Category = "Automation")
	float FocusNear = 250.0f;

	UPROPERTY(EditAnywhere, Category = "Automation")
	float FocusFar = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Automation")
	float FOVInterpSpeed = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Automation")
	float FocusInterpSpeed = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Automation")
	float HoldDuration = 2.0f;

	float HoldTimer = 0.0f;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequences")
	class ULevelSequence* MinorInjurySequence;


	
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
