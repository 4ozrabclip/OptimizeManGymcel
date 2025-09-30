// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Bedroom/Concrete/Laptop_OM.h"
#include "Widgets/Both/Abstract/PlayModeBaseWidget_OM.h"
#include "ShelfWidget_OM.generated.h"

enum class EShopAndBook : uint8;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UShelfWidget_OM : public UPlayModeBaseWidget_OM
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
