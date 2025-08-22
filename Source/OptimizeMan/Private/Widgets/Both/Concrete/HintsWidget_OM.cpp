// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/HintsWidget_OM.h"

#include "Components/TextBlock.h"

void UHintsWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	TimeTilFlashingStarts = FMath::RandRange(4.f, 10.f);
	
}

void UHintsWidget_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bHintOnScreen && !bFlashing)
	{
		TimeSinceHintOnScreen += InDeltaTime;

		if (TimeSinceHintOnScreen >= TimeTilFlashingStarts)
		{
			TimeTilFlashingStarts = FMath::RandRange(4.f, 10.f);
			bFlashing = true;
			PlayAnimation(FlashingAnim, 0, 0);
		}
	}
	
}

void UHintsWidget_OM::ShowHint(const FText& HintTextString, float DisplayTime, bool bFlash)
{
	if (!HintText)
	{
		UE_LOG(LogTemp, Error, TEXT("HintText TextBlock is NULL"));
		return;
	}
	/*if (GameInstance->GetDarkMode())
	{
		HintText->SetColorAndOpacity(White);
	}
	else
	{
		HintText->SetColorAndOpacity(Black);
	}*/



	HintText->SetText(HintTextString);
	SetVisibility(ESlateVisibility::HitTestInvisible);
	bHintOnScreen = true;

	if (bFlash)
	{
		TimeTilFlashingStarts = FMath::RandRange(4.f, 10.f);
		PlayAnimation(FlashingAnim,0, 0);
		bFlashing = true;
	}
	else if (constexpr int HoldUntilHidden = 0; DisplayTime > HoldUntilHidden)
	{
		GetWorld()->GetTimerManager().ClearTimer(HintTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(
		HintTimerHandle,
		this,
		&UHintsWidget_OM::HideHint,
		DisplayTime, 
		false 
		);
	}
}

void UHintsWidget_OM::HideHint()
{
	if (FlashingAnim && bFlashing && GetAnimationState(FlashingAnim)->IsPlayingForward())
	{
		bFlashing = false;
		GetAnimationState(FlashingAnim)->Stop();
	}
	TimeSinceHintOnScreen = 0;
	SetVisibility(ESlateVisibility::Hidden);
	bHintOnScreen = false;
}
