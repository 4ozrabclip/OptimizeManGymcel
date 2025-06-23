// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Utils/Structs/ConsumableData.h"
#include "GymGameModeBase_OM.generated.h"

class APlayerController_OM;
class APlayerCharacter_OM;
class UGameInstance_OM;
class UConsumablesSubsystem;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AGymGameModeBase_OM : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGymGameModeBase_OM();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void CheckIdleStats(float DeltaTime);
	void CheckGymStats(float DeltaTime);

protected:
	UPROPERTY()
	UGameInstance_OM* GameInstance;
	UPROPERTY()
	UConsumablesSubsystem* ConsumableManager;

	UPROPERTY()
	APlayerController_OM* PlayerController;
	UPROPERTY()
	APlayerCharacter_OM* Player;

private:
	float TimePassedSinceIdle = 0.f;

	float EnergyDecreaseValue = -0.001f;
	float FocusDecreaseValue = -0.001f;

	float FocusDecreaseSlowMultiplier = 1.f;
	float EnergyDecreaseSlowMultiplier = 1.f;
	
	bool bFocusBoostActive = false;
	bool bEnergyBoostActive = false;

	
	
};