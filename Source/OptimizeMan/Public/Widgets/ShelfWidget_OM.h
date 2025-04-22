// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/Laptop_OM.h"
#include "Widgets/MinigameBaseWidget_OM.h"
#include "ShelfWidget_OM.generated.h"

enum class EShopAndBook : uint8;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UShelfWidget_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	void InitButtons();
	void CheckItemForButtonVisibility(bool InHasItem, UButton* InButton);

	
	


	UPROPERTY(meta = (BindWidget))
	UButton* UseBabyCrackButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* UseSteroidsButton;



	void OnItemUsed(EShopAndBook InItem);
	
	UFUNCTION()
	void OnUseBabyCrackClicked() {OnItemUsed(EShopAndBook::PreWorkout); }

	UFUNCTION()
	void OnUseSteroidsClicked() {OnItemUsed(EShopAndBook::Steroids);}

};
