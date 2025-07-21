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
	UFUNCTION()
	void ExitVendor();

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
	
	// Widget UOBJECTS
	UPROPERTY(meta = (BindWidget))
	UButton* Option1_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Option2_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Option3_Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Exit_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option1Desc_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option2Desc_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option3Desc_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option1Price_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option2Price_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option3Price_Text;


	UPROPERTY(meta = (BindWidget))
	UImage* Option1_Image;
	UPROPERTY(meta = (BindWidget))
	UImage* Option2_Image;
	UPROPERTY(meta = (BindWidget))
	UImage* Option3_Image;
	UPROPERTY(meta = (BindWidget))
	UImage* Option4_Image;

	
};

