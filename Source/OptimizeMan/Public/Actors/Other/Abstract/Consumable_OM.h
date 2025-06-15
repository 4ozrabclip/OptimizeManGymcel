// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor_OM.h"
#include "Utils/Structs/ConsumableData.h"
#include "Consumable_OM.generated.h"


UCLASS(Abstract)
class OPTIMIZEMAN_API AConsumable_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
public:
	AConsumable_OM();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Interact_Implementation() override;

	FConsumableType& GetConsumableType() { return ConsumableType; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable Type")
	FConsumableType ConsumableType;
	
};
