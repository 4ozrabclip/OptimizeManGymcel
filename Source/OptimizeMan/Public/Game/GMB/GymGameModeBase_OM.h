// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GymGameModeBase_OM.generated.h"

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
	class UGameInstance_OM* GameInstance;
	UPROPERTY()
	class APlayerCharacter_OM* Player;

private:
	float TimePassedSinceIdle = 0.f;
	
};