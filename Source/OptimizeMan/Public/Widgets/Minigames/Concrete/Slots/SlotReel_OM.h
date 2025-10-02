// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utils/Structs/SlotData.h"
#include "SlotReel_OM.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScrollFinished);
class UScrollBox;
class UUniformGridPanel;
class USlotItem_OM;
class UImage;
/**
 * 
 */

UCLASS()
class OPTIMIZEMAN_API USlotReel_OM : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	/** Delegates / Events **/
	FOnScrollFinished OnScrollFinished;
private:
	/* Init */
	void SetInitialItems();
	UFUNCTION()
	void TickScroll();
	UFUNCTION()
	void EndScroll();
	
public:
	UFUNCTION(BlueprintCallable)
	void StartScroll(int EnergyBid, int ReelIndex);

	void SelectItemCenter(ESlotItemType InType);


	/* Setters */
	void SetIsSpinning(const bool bInIsSpinning) { bIsSpinning = bInIsSpinning; };

	/* Getters */
	FSlotItemData GetRandomType();

protected:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ReelScrollBox;
	
	UPROPERTY(meta = (BindWidget))
	USlotItem_OM* TopItem;
	UPROPERTY(meta = (BindWidget))
	USlotItem_OM* UnderTopItem;
	UPROPERTY(meta = (BindWidget))
	USlotItem_OM* AboveBottomItem;
	UPROPERTY(meta = (BindWidget))
	USlotItem_OM* BottomItem;
	UPROPERTY(meta = (BindWidget))
	USlotItem_OM* CenterItem;


	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ScrollAnim;
	
private:
	UPROPERTY(EditAnywhere)
	float ScrollSpeed = 5.f;
	UPROPERTY(EditAnywhere)
	float TickSpeed = 0.065f;
	
	float CurrentScrollOffset;
	
	float StartScrollOffset = 0;
	float EndScrollOffset;

	bool bIsSpinning;
	
	TArray<TSoftObjectPtr<USlotItem_OM>> AllItems;

	UPROPERTY(EditAnywhere)
	TArray<FSlotItemData> ItemTypes;


	FTimerHandle ScrollTimerHandle;
	FTimerHandle EndScrollTimerHandle;
	
};