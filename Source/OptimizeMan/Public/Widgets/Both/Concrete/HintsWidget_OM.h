// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "HintsWidget_OM.generated.h"

/**
 * 
 */

UCLASS()
class OPTIMIZEMAN_API UHintsWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void ShowHint(const FText& HintTextString, float DisplayTime = 0.f, bool bFlash = false);
	void HideHint();


protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HintText;

	FTimerHandle HintTimerHandle;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FlashingAnim;




private:
	bool bHintOnScreen = false;
	bool bFlashing = false;

	float TimeTilFlashingStarts;
	float TimeSinceHintOnScreen = 0.f;
	
};

