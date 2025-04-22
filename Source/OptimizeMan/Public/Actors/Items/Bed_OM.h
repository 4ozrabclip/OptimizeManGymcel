// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptimizeMan/Public/Actors/InteractableActor_OM.h"
#include "Bed_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API ABed_OM : public AInteractableActor_OM
{
	GENERATED_BODY()

public:
	ABed_OM();
	
	virtual void Interact_Implementation() override;
	void SleepDelay(const float FadeDuration);

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void CheckAndSetDarkMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* ExtraCollider;

	void SetIsSleeping(const bool InIsSleeping);
	bool GetIsSleeping() const;

private:
	bool bIsSleeping;

	UPROPERTY()
	class ABedroomGameModeBase_OM* GameMode;

protected:
	FTimerHandle SleepTimerHandle;
};
