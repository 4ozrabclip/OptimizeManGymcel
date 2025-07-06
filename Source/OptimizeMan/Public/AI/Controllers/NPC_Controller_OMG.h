// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/NPC/Abstract/NpcBase_OMG.h"
#include "Controllers/NPC_AIController_OM.h"
#include "NPC_Controller_OMG.generated.h"

class ANpcBase_OMG;

UCLASS()
class OPTIMIZEMAN_API ANPC_Controller_OMG : public ANPC_AIController_OM
{
	GENERATED_BODY()
public:
	explicit ANPC_Controller_OMG(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

	/** AI MIND **/
	void ActivityChangeDiceRoll();

private:
	/** Cache **/
	FORCEINLINE ANpcBase_OMG* GetNpcBase_Gymcel() const
	{
		return Cast<ANpcBase_OMG>(Npc);
	}


	/** AI Mind Stored Variables **/
	float TimeSinceLastActivityChange = 0.f;
	float RandDurationBetweenRolls = 10.f;


public:
	// Called every frame

};

