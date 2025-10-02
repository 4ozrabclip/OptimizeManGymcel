// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utils/Structs/SlotData.h"
#include "SlotItem_OM.generated.h"


class UImage;
/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API USlotItem_OM : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	/** Setters **/
	void SetType(FSlotItemData InType);
	void SetImage(UTexture2D* InImage);
	void SetIsFinalCenter(const bool InIsFinalCenter) { bIsFinalCenter = InIsFinalCenter; }
	void SetIsPositionedCenter(const bool InIsPositionedCenter) { bIsPositionedCenter = InIsPositionedCenter; }

	/** Getters **/
	bool GetIsFinalCenter() const { return bIsFinalCenter; }
	bool GetIsPositionedCenter() const { return bIsPositionedCenter; }
	FSlotItemData GetType() const { return Type; }

protected:
	FSlotItemData Type;
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;


private:
	UPROPERTY(EditAnywhere, Category = "Params")
	bool bIsFinalCenter = false;
	bool bIsPositionedCenter = false;



	
};
