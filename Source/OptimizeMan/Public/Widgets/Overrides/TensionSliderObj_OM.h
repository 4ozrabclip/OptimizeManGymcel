// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "TensionSliderObj_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UTensionSliderObj_OM : public USlider
{
	GENERATED_BODY()
public:
	// How much tension to apply (higher = harder to drag near top)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tension")
	float TensionExponent = 2.0f;

protected:
	// Build the Slate widget and hook it up
	virtual TSharedRef<SWidget> RebuildWidget() override;

	// Sync any property changes
	virtual void SynchronizeProperties() override;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

private:
	// Pointer to our custom Slate slider
	TSharedPtr<class STensionSlider_OM> MyTensionSlider;
};
