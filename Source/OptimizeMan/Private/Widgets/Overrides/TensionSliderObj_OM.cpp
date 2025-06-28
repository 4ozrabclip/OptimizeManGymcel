// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Overrides/TensionSliderObj_OM.h"
#include "Widgets/Overrides/TensionSlider_OM.h"

TSharedRef<SWidget> UTensionSliderObj_OM::RebuildWidget()
{
	MyTensionSlider = SNew(STensionSlider_OM)
		.TensionExponent(TensionExponent)
		.OnValueChanged(BIND_UOBJECT_DELEGATE(FOnFloatValueChanged, HandleOnValueChanged));


	// Set up initial appearance
	MyTensionSlider->SetOrientation(GetOrientation());
	MyTensionSlider->SetSliderBarColor(GetSliderBarColor());
	MyTensionSlider->SetSliderHandleColor(GetSliderHandleColor());


	return MyTensionSlider.ToSharedRef();
}

void UTensionSliderObj_OM::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (MyTensionSlider.IsValid())
	{
		MyTensionSlider->SetOrientation(GetOrientation());
		MyTensionSlider->SetSliderBarColor(GetSliderBarColor());
		MyTensionSlider->SetSliderHandleColor(GetSliderHandleColor());

		// If you ever add changing TensionExponent at runtime, can sync here
	}
}

void UTensionSliderObj_OM::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyTensionSlider.Reset();
}
