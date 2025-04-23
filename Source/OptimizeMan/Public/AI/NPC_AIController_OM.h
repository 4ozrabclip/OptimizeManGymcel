// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Utils/structs/NpcStates.h"
#include "NPC_AIController_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ANPC_AIController_OM : public AAIController
{
	GENERATED_BODY()
public:
	explicit ANPC_AIController_OM(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
