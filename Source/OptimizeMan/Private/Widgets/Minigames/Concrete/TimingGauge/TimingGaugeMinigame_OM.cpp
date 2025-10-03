// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Minigames/Concrete/TimingGauge/TimingGaugeMinigame_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Utils/Structs/ExerciseData.h"


UTimingGaugeMinigame_OM::UTimingGaugeMinigame_OM()
{
	MiniGameType = EMiniGameType::TimingGauge;
}

void UTimingGaugeMinigame_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (MiniGameClickButton)
	{
		MiniGameClickButton->OnClicked.RemoveAll(this);
		MiniGameClickButton->OnClicked.AddDynamic(this, &UTimingGaugeMinigame_OM::OnMiniGameClick);
	}
	
	if (BloodSplatter->GetVisibility() != ESlateVisibility::Hidden)
	{
		BloodSplatter->SetVisibility(ESlateVisibility::Hidden);
	}

	if (!ExerciseComponent)
	{
		ExerciseComponent = Player->GetComponentByClass<UExercise_OM>();
	}
	if (!ExerciseComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Exercise Component Null"));
		return;
	}

	SetMiniGameOn(true);
	
	if (SetCountTextBlock && RepCountTextBlock)
	{
		SetCountTextBlock->SetText(FText::FromString(TEXT("")));
		RepCountTextBlock->SetText(FText::FromString(TEXT("")));
	}
	
}

void UTimingGaugeMinigame_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	switch (CurrentWorkoutState)
	{
	case EWorkoutStates::InExercisePosition:
		{
			if (!MiniGameClickButton->GetIsEnabled())
				MiniGameClickButton->SetIsEnabled(true);
			if (GetMiniGameOn())
				MiniGame(InDeltaTime);

			if (!GetHasPlayedThisMiniGame())
			{
				WorkoutTutorial(InDeltaTime);
			}
			break;
		}
	case EWorkoutStates::SetComplete:
		{
			NotificationTextPopUp(TEXT("Set Complete"));
			if (ExerciseComponent)
				ExerciseComponent->SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
			break;
		}
	default:
		if (MiniGameClickButton->GetIsEnabled())
			MiniGameClickButton->SetIsEnabled(false);
		return;
	}
}

void UTimingGaugeMinigame_OM::CheckAndSetStyles()
{
	Super::CheckAndSetStyles();

	if (const bool bDarkMode = GameInstance->GetDarkMode())
	{
		FSlateBrush WhiteThumb;
		WhiteThumb.SetResourceObject(DownArrowWhite);
		FSliderStyle SliderDarkStyle;
		SliderDarkStyle.SetNormalThumbImage(WhiteThumb);
		SliderDarkStyle.SetBarThickness(0.f);

	
		MiniGameSlider->SetWidgetStyle(SliderDarkStyle);
		NotificationText->SetColorAndOpacity(White);
		SetCountTextBlock->SetColorAndOpacity(White);
		RepCountTextBlock->SetColorAndOpacity(White);
	}
	else
	{
		FSlateBrush BlackThumb;
		BlackThumb.SetResourceObject(DownArrowBlack);
		FSliderStyle SliderLightStyle;
		SliderLightStyle.SetNormalThumbImage(BlackThumb);
		SliderLightStyle.SetBarThickness(0.f);
		
		MiniGameSlider->SetWidgetStyle(SliderLightStyle);
		NotificationText->SetColorAndOpacity(Black);
		SetCountTextBlock->SetColorAndOpacity(Black);
		RepCountTextBlock->SetColorAndOpacity(Black);
	}
}

void UTimingGaugeMinigame_OM::WorkoutTutorial(float DeltaTime)
{
	if (!ClickImage) return;
	TimeSinceWorkoutTutorial += DeltaTime;

	if (ClickImage->GetVisibility() == ESlateVisibility::Hidden)
		ClickImage->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (FMath::IsNearlyEqual(TimeSinceWorkoutTutorial, 1.5f, 0.1f)
		|| FMath::IsNearlyEqual(TimeSinceWorkoutTutorial, 4.3f, 0.1f))
	{ 
		if (ClickHand_Clicking)
			ClickImage->SetBrushResourceObject(ClickHand_Clicking);
	}
	else if (FMath::IsNearlyEqual(TimeSinceWorkoutTutorial, 3.f, 0.1f))
	{
		if (ClickHand)
			ClickImage->SetBrushResourceObject(ClickHand);
	}
	else if (FMath::IsNearlyEqual(TimeSinceWorkoutTutorial, 5.f, 0.1f))
	{
		if (ClickHand)
			ClickImage->SetBrushResourceObject(ClickHand);
		TimeSinceWorkoutTutorial = 0.f;
	}

}
void UTimingGaugeMinigame_OM::SetWorkoutState(EWorkoutStates NewWorkoutState)
{
	Super::SetWorkoutState(NewWorkoutState);
	switch (CurrentWorkoutState)
	{
	case EWorkoutStates::InExercisePosition:
		{
			if (!MiniGameClickButton->GetIsEnabled())
				MiniGameClickButton->SetIsEnabled(true);
			break;
		}
	default:
		if (MiniGameClickButton->GetIsEnabled())
			MiniGameClickButton->SetIsEnabled(false);
		return;
	}
	
}
void UTimingGaugeMinigame_OM::NativeDestruct()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Super::NativeDestruct();
}

void UTimingGaugeMinigame_OM::MiniGame(float InDeltaTime)
{
	if (BloodSplatter->GetVisibility() != ESlateVisibility::Hidden)
	{
		BloodSplatter->SetVisibility(ESlateVisibility::Hidden);
	}

	float ScaledSpeed = Speed * InDeltaTime;
	
	if (bMovingRight)
	{
		SliderValue += ScaledSpeed;
		if (SliderValue >= MaxValue)
		{
			SliderValue = MaxValue;
			bMovingRight = false;
		}
	}
	else
	{
		SliderValue -= ScaledSpeed;
		if (SliderValue <= MinValue)
		{
			SliderValue = MinValue;
			bMovingRight = true;
		}
	}
    //injury bounds
	if (bLeftMovingUp)
	{
		InjuryBoundsLeftValue += ScaledSpeed;
		if (InjuryBoundsLeftValue >= LeftMax)
		{
			InjuryBoundsLeftValue = LeftMax;
			bLeftMovingUp = false;
		}
	}
	else
	{
		InjuryBoundsLeftValue -= ScaledSpeed;
		if (InjuryBoundsLeftValue <= LeftMin)
		{
			InjuryBoundsLeftValue = LeftMin;
			bLeftMovingUp = true;
		}
	}
	if (bRightMovingUp)
	{
		InjuryBoundsRightValue += ScaledSpeed;
		if (InjuryBoundsRightValue >= RightMax)
		{
			InjuryBoundsRightValue = RightMax;
			bRightMovingUp = false;
		}
	}
	else
	{
		InjuryBoundsRightValue -= ScaledSpeed;
		if (InjuryBoundsRightValue <= RightMin)
		{
			InjuryBoundsRightValue = RightMin;
			bRightMovingUp = true;
		}
	}
	
	InjuryBoundsLeft->SetPercent((InjuryBoundsLeftValue * 2.f) - 0.2f);
	InjuryBoundsRight->SetPercent(((1.f  - InjuryBoundsRightValue) * 2.f) - 0.2f);

	MinorInjuryLeft->SetPercent((InjuryBoundsLeftValue * 2.f) + 0.35f);
	MinorInjuryRight->SetPercent(((1.f  - InjuryBoundsRightValue) * 2.f) + 0.35f);

	constexpr float MainSliderPhaseSpeed = 0.5;

	MainSliderTime += InDeltaTime * MainSliderPhaseSpeed;

	MainSliderPhase = FMath::Sin(MainSliderTime);
	const float MainSliderValueWithPhase = (MainSliderPhase + 1.f) / 2.f;

	float SliderValueFinal = (SliderValue + MainSliderValueWithPhase * 0.1f);
	SliderValueFinal = FMath::Clamp(SliderValueFinal, MinValue, MaxValue);
	
	MiniGameSlider->SetValue(SliderValueFinal);

	//sigma
	if (bSpecialSliderOn)
	{
		constexpr float BaseSpeed = 2.f;
		constexpr float PhaseSpeed = 0.5f;

		SpecialSliderTime += InDeltaTime * BaseSpeed;

		if (bSpecialSliderPhaseIncreasing)
		{
			SpecialSliderPhase += InDeltaTime * PhaseSpeed;
			if (SpecialSliderPhase >= PI)
			{
				SpecialSliderPhase = PI;
				bSpecialSliderPhaseIncreasing = false;
			}
		}
		else
		{
			SpecialSliderPhase -= InDeltaTime * PhaseSpeed;
			if (SpecialSliderPhase <= -PI)
			{
				SpecialSliderPhase = -PI;
				bSpecialSliderPhaseIncreasing = true;
			}
		}

		const float PrimaryWave = FMath::Sin(SpecialSliderTime + SpecialSliderPhase);
		const float SecondaryWave = FMath::Sin(SpecialSliderTime * 0.5f) * 0.3f;
		const float CombinedWave = PrimaryWave + SecondaryWave;

		SpecialSliderValue = (CombinedWave + 1.3f) / 2.6f;
		SpecialSliderValue = FMath::Clamp(SpecialSliderValue, 0.0f, 1.0f);

		SpecialSlider->SetValue(SpecialSliderValue);
	}
}

void UTimingGaugeMinigame_OM::SetSpecialSliderOn(const bool InSpecialSliderOn)
{
	bSpecialSliderOn = InSpecialSliderOn;
	if (bSpecialSliderOn)
	{
		SpecialSlider->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		SpecialSlider->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UTimingGaugeMinigame_OM::CheckStatsForFrontEnd()
{
	if (!ExerciseComponent) return;
	SetLocalEnergyLevel(ExerciseComponent->GetEnergy());
	if (GetEnergyLevel() <= 0.f)
	{
		NotificationTextPopUp(TEXT("No Energy"));
		SetMiniGameOn(false);
	}

	SetSetAndRepCountTextBlocks();
}


void UTimingGaugeMinigame_OM::OnMiniGameClick()
{
	Super::OnMiniGameClick();
	
	if (GetHasPlayedThisMiniGame())
	{
		ClickImage->SetVisibility(ESlateVisibility::Hidden);
	}
	
	MiniGameClickButton->SetIsEnabled(false);
	
	constexpr float SigmaOffset = 0.15f;
	if (bSpecialSliderOn && MiniGameSlider->GetValue() >= SpecialSlider->GetValue() - SigmaOffset && MiniGameSlider->GetValue() <= SpecialSlider->GetValue() + SigmaOffset)
	{
		SetSpecialSliderOn(false);
	}

	const float MajorInjuryBoundsValueLeft = (InjuryBoundsLeft->GetPercent()) / 2.f;
	const float MajorInjuryBoundsValueRight = 1.f - (InjuryBoundsRight->GetPercent()) / 2.f;

	const float MinorInjuryBoundsValueLeft = (MinorInjuryLeft->GetPercent()) / 2.f;
	const float MinorInjuryBoundsValueRight = 1.f - ((MinorInjuryRight->GetPercent()) / 2.f);

	

	if (MiniGameSlider->GetValue() >= MinorInjuryBoundsValueLeft &&
		MiniGameSlider->GetValue() <= MinorInjuryBoundsValueRight)
	{
		NewResult = EMinigameResult::Success;
		NewEnergyFactor += 0.1f;
		
	}
	else if (MiniGameSlider->GetValue() >= MajorInjuryBoundsValueLeft &&
			 MiniGameSlider->GetValue() <= MajorInjuryBoundsValueRight)
	{
		NewResult = EMinigameResult::Success;
		NewEnergyFactor += 0.4f;

		const FName InjuredPartName = ExerciseComponent->GetCurrentInjuredPart()->Name;
		
		const FString InjuryString = FString::Printf(TEXT("You have injured your: %s"), *InjuredPartName.ToString());
		NotificationTextPopUp(InjuryString);
	}
	else
	{
		NewResult = EMinigameResult::Failed;

		BloodSplatter->SetVisibility(ESlateVisibility::HitTestInvisible);
		ExerciseComponent->Injury(EInjuryLevel::Major);
		
		SetMiniGameOn(false);
	}

	
	CurrentMinigameResult.Result = NewResult;
	CurrentMinigameResult.EnergyFactor = NewEnergyFactor;

	Speed += 0.1 * NewEnergyFactor;
	LeftMax += 0.005f * NewEnergyFactor;
	RightMin -= 0.005f * NewEnergyFactor;
	InjuryBoundsLeftValue = 0.f;
	InjuryBoundsRightValue = 1.f;
	
	ExerciseComponent->MiniGame(CurrentMinigameResult);
	
	CheckStatsForFrontEnd();


	/*
	 * Special Slider Logic is full of Magic Numbers.  Make a separate function for this
	 *
	 * 
	 *if (!bSpecialSliderOn && ( GetEnergyLevel() > 0.8f || GetEnergyLevel() < 0.3f && GetEnergyLevel() > 0.1))
	{
		SetSpecialSliderOn(true);
	}
	else
	{
		SetSpecialSliderOn(false);
	}*/
	
}



void UTimingGaugeMinigame_OM::SetMiniGameOn(const bool InMiniGameOn)
{
	bMiniGameOn = InMiniGameOn;
	
	if (bMiniGameOn)
	{
		MiniGameSlider->SetVisibility(ESlateVisibility::HitTestInvisible);
		WinBoundsLeftSlider->SetVisibility(ESlateVisibility::Hidden);
		WinBoundsRightSlider->SetVisibility(ESlateVisibility::Hidden);
		InjuryBoundsLeft->SetVisibility(ESlateVisibility::HitTestInvisible);
		InjuryBoundsRight->SetVisibility(ESlateVisibility::HitTestInvisible);
		MinorInjuryLeft->SetVisibility(ESlateVisibility::HitTestInvisible);
		MinorInjuryRight->SetVisibility(ESlateVisibility::HitTestInvisible);
		
		MiniGameClickButton->SetVisibility(ESlateVisibility::Visible);

		SetSetAndRepCountTextBlocks();
	}
	else
	{
		MiniGameSlider->SetVisibility(ESlateVisibility::Hidden);
		WinBoundsLeftSlider->SetVisibility(ESlateVisibility::Hidden);
		WinBoundsRightSlider->SetVisibility(ESlateVisibility::Hidden);
		InjuryBoundsLeft->SetVisibility(ESlateVisibility::Hidden);
		InjuryBoundsRight->SetVisibility(ESlateVisibility::Hidden);
		MinorInjuryLeft->SetVisibility(ESlateVisibility::Hidden);
		MinorInjuryRight->SetVisibility(ESlateVisibility::Hidden);
		SpecialSlider->SetVisibility(ESlateVisibility::Hidden);
		
		
		MiniGameClickButton->SetVisibility(ESlateVisibility::Hidden);

		
	}
}


