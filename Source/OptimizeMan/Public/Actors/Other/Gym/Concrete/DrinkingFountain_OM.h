// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Both/Abstract/InteractableActor_OM.h"
#include "DrinkingFountain_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API ADrinkingFountain_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
public:
	ADrinkingFountain_OM();

protected:
	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;
	
};
