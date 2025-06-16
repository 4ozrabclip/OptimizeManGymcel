// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Abstract/Consumable_OM.h"
#include "Actors/Other/Abstract/InteractableActor_OM.h"
#include "VendingMachine_OM.generated.h"

class UWidgetComponent;

UCLASS()
class OPTIMIZEMAN_API AVendingMachine_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
public:
	AVendingMachine_OM();
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

public:
	UFUNCTION()
	void ExitVendor();

public:
	TArray<TSubclassOf<AConsumable_OM>> GetVendorInventory() { return VendingInventory;};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UWidgetComponent* VendorWidgetComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<TSubclassOf<AConsumable_OM>> VendingInventory;

private:

	
};
