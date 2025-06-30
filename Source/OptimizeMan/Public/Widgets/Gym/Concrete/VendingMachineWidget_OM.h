// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Gym/Concrete/VendingMachine_OM.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "VendingMachineWidget_OM.generated.h"

class UImage;
class UOverlay;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UVendingMachineWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
protected:
	void SetConsumables();
	void SetConsumablesText();

	void SetConsumablesTextHelper(UTextBlock* InTextBlock, const FText& InText);
	void BuyConsumable(const FConsumableType& InConsumable);
	
	UFUNCTION()
	void OnOption1Clicked();
	UFUNCTION()
	void OnOption2Clicked();
	UFUNCTION()
	void OnOption3Clicked();
	void ShowNoMoneyWindow();

private:
	UPROPERTY()
	AVendingMachine_OM* VendingMachine;

	FTimerHandle NoMoneyTimer;

public:
	void InitVendingMachine(const TSoftObjectPtr<AVendingMachine_OM>& InVendingMachine) { VendingMachine = InVendingMachine.Get(); };


protected:
	TArray<FConsumableType> Consumables;
	FConsumableType Consumable_1;
	FConsumableType Consumable_2;
	FConsumableType Consumable_3;

	UPROPERTY(meta = (BindWidget))
	UImage* Option_Image;
	UPROPERTY(meta = (BindWidget))
	UImage* Option_Image_1;
	UPROPERTY(meta = (BindWidget))
	UImage* Option_Image_2;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OptionTitle_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OptionTitle_Text_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OptionTitle_Text_2;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionBuy_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* OptionBuy_Button_1;
	UPROPERTY(meta = (BindWidget))
	UButton* OptionBuy_Button_2;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Exit_Button;

	UPROPERTY(meta = (BindWidget))
	UOverlay* NoMoney_Overlay;
	

};

