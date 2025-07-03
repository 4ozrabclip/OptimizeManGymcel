// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController_OM.generated.h"

class ANpcBase_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMANCORE_API ANPC_AIController_OM : public AAIController
{
	GENERATED_BODY()
public:
	explicit ANPC_AIController_OM(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	
private:

protected:
	UPROPERTY()
	ANpcBase_OM* Npc;

};
