// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/InteractableMirrorBase_OM.h"
#include "Actors/InteractableActor_OM.h"
#include "MuscleView_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AMuscleView_OM : public AInteractableMirrorBase_OM
{
	GENERATED_BODY()
public:
	AMuscleView_OM();

	virtual void BeginPlay() override;


	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, Category = "Player facing mirror location")
	float StepBackReach;

	
};
