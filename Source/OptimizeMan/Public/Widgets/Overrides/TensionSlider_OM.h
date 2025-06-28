// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once


#include "SlateBasics.h"
#include "SlateCore.h"
#include "Widgets/Input/SSlider.h"

/**
 * 
 */
class OPTIMIZEMAN_API STensionSlider_OM : public SSlider
{
public:
	SLATE_BEGIN_ARGS(STensionSlider_OM)
		: _TensionExponent(2.0f)
	{}
	SLATE_ARGUMENT(float, TensionExponent)
	SLATE_EVENT(FOnFloatValueChanged, OnValueChanged)
SLATE_END_ARGS()

void Construct(const FArguments& InArgs)
	{
		TensionExponent = InArgs._TensionExponent;

		// Pass OnValueChanged event to SSlider
		SSlider::FArguments Args = SSlider::FArguments()
			.OnValueChanged(InArgs._OnValueChanged);

		SSlider::Construct(Args);
	}

	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override
	{
		if (HasMouseCapture())
		{
			const FVector2D LocalMouseCoord = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
			const float SliderLength = (Orientation == Orient_Horizontal) ? MyGeometry.GetLocalSize().X : MyGeometry.GetLocalSize().Y;
			const float NewValueRaw = (Orientation == Orient_Horizontal) ? LocalMouseCoord.X / SliderLength : 1.f - (LocalMouseCoord.Y / SliderLength);

			// Clamp and apply tension
			float NewValueNorm = FMath::Clamp(NewValueRaw, 0.f, 1.f);
			float TensionMultiplier = FMath::Pow(1.0f - NewValueNorm, TensionExponent);
			float AdjustedValue = FMath::Clamp(NewValueNorm - (1.f - TensionMultiplier) * 0.1f, 0.f, 1.f); 

			CommitValue(AdjustedValue);

			return FReply::Handled();
		}
		return SSlider::OnMouseMove(MyGeometry, MouseEvent);
	}

protected:
	float TensionExponent = 2.f;
};
