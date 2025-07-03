// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Consumables/Abstract/Consumable_OM.h"
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
	void PlaySound(USoundBase* InSound) const;



public:
	UFUNCTION()
	void ExitVendor();

	void SpawnItem(const FConsumableType& ItemToSpawn);

	void PlayBuySound() const { PlaySound(BuySound); }
	void PlayNoMoneySound() const { PlaySound(NoMoneySound); }

public:
	TArray<TSubclassOf<AConsumable_OM>> GetVendorInventory() { return VendingInventory;};

protected:
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* VendorWidgetComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UGameAudio_OM* VendorAudio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Spawn Params")
	USceneComponent* SpawnLocation;

	//Other
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<TSubclassOf<AConsumable_OM>> VendingInventory;



	//Sounds
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* BuySound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* NoMoneySound;
	
private:

	
};
