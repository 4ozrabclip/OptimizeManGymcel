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

protected:
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	
};