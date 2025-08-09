// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Both/Abstract/InteractableActor_OM.h"
#include "Laptop_OM.generated.h"

class UGameAudio_OM;
/**
 * 
 */
UENUM(BlueprintType)
enum class EShopAndBook : uint8 //mw
{
	None,
	JawSurgery,
	PreWorkout,
	Steroids,
	LegLengtheningSurgery,
	ChadPoster,
	WaifuPoster
};
UCLASS()
class OPTIMIZEMAN_API ALaptop_OM : public AInteractableActor_OM
{
	GENERATED_BODY()

public:
	ALaptop_OM();
	
	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;
	void SetShopAndBook(EShopAndBook InShopAndBook);
	void BuyItem();
	void PlaySound(USoundBase* InSound);
	
	virtual void DarkModeToggle(const bool bIsDarkMode) override;


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MirrorAudio")
	UGameAudio_OM* LaptopAudio;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* ExtraCollider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShopAudio")
	USoundBase* BuySound;
	
	EShopAndBook CurrentShopAndBook; //mw


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShelfAndItems")
	class AShelf_OM* Shelf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShelfAndItems")
	class APoster_OM* PostersClass;
	


	bool BuyPoster(TArray<bool>& InPosterArray, const FString& PosterType);
	
	
	
};
