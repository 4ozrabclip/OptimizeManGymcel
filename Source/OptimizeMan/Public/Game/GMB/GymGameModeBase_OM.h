// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyTick_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTick_OM.h"
#include "Utils/Structs/ConsumableData.h"
#include "GymGameModeBase_OM.generated.h"

class UMentalHealthStats_OM;
class UGymSpecificStats_OM;
class UAbilitySystemComponent_OM;
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
protected:
	/** Function Overrides **/
	virtual void BeginPlay() override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	void InitializeConstantEffects();

private:


protected:
	UPROPERTY()
	UGameInstance_OM* GameInstance;
	UPROPERTY()
	UConsumablesSubsystem* ConsumableManager;
	UPROPERTY()
	APlayerController_OM* PlayerController;
	UPROPERTY()
	APlayerCharacter_OM* Player;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent_OM> AbSysComp;
	UPROPERTY()
	const UGymSpecificStats_OM* GymStats;
	UPROPERTY()
	const UMentalHealthStats_OM* MentalHealth;

	


private:
	float TimePassedSinceIdle = 0.f;

	float EnergyDecreaseValue = -0.001f;
	float FocusDecreaseValue = -0.001f;

	float FocusDecreaseSlowMultiplier = 1.f;
	float EnergyDecreaseSlowMultiplier = 1.f;
	
	bool bFocusBoostActive = false;
	bool bEnergyBoostActive = false;

	
	
};