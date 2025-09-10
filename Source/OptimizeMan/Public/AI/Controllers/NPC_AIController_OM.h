// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Utils/structs/NpcStates.h"
#include "NPC_AIController_OM.generated.h"

class ANpcBase_OM;
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	void ActivityChangeDiceRoll();


private:
	UPROPERTY()
	ANpcBase_OM* Npc;

	float TimeSinceLastActivityChange = 0.f;
	float RandDurationBetweenRolls = 10.f;
};
