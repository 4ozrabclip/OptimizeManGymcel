// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Abstract/InteractableActor_OM.h"
#include "GymGate_OM.generated.h"

class UGameAudio_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AGymGate_OM : public AInteractableActor_OM
{
	GENERATED_BODY()

	AGymGate_OM();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;
	void CheckIfInwardOrOutward();

public:
	void ClearGateTimer();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GateOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GateTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameAudio_OM* AudioComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor GateRedColour = {0, 255, 255};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor GateGreenColour = {255, 0, 255};


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* GateBeepSound;

private:
	FRotator DoorOneClosedRotation;
	FRotator DoorTwoClosedRotation;
	FVector DoorOneClosedLocation;
	FVector DoorTwoClosedLocation;
	FRotator DoorOpenRotation;

	bool bGateIsOpen;

	float CurrentRotationAlpha;
	float TimeSinceTriggered;
	float GateOpenSpeed;

	const float GateCloseDelay = 4.f;

	UPROPERTY()
	FTimerHandle GateCloseTimerHandle;


	void OpenGate(float DeltaTime);
	void PrepareDelayForGateClose();
	void CloseGate(float DeltaTime);
};
