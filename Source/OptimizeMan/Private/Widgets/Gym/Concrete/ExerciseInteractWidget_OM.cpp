// Copyright © 2025 4ozStudio. All rights reserved.

#include "Widgets/Gym/Concrete/ExerciseInteractWidget_OM.h"

#include "Actors/Other/Gym/Concrete/Barbell_OM.h"
#include "Actors/Other/Gym/Concrete/Dumbell_OM.h"
#include "Actors/Other/Gym/Abstract/ExerciseEquipment_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Components/GridPanel.h"
#include "Game/Persistent/GameInstance_OM.h"

void UExerciseInteractWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	if (MiniGameClickButton)
	{
		MiniGameClickButton->OnClicked.RemoveAll(this);
		MiniGameClickButton->OnClicked.AddDynamic(this, &UExerciseInteractWidget_OM::OnMiniGameClick);
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
	if (ExerciseComponent)
	{
		ExerciseComponent->OnWorkoutStateChanged.RemoveAll(this);
		ExerciseComponent->OnWorkoutStateChanged.AddDynamic(this, &UExerciseInteractWidget_OM::SetWorkoutState);
	}

	


	UpdateStats();
	SetMiniGameOn(true);
	
	if (SetCountTextBlock && RepCountTextBlock)
	{
		SetCountTextBlock->SetText(FText::FromString(TEXT("")));
		RepCountTextBlock->SetText(FText::FromString(TEXT("")));
	}


	ExerciseComponent->PrepareExercise();

	CheckAndSetStyles();

	
	GetWorld()->GetTimerManager().SetTimer(TutorialDelayHandle, [this]()
	{
		bHasWorkedOutInitial = GameInstance->GetHasDoneWorkoutInitial();
	},2.f, false);

	
}



void UExerciseInteractWidget_OM::CheckAndSetStyles()
{

	auto SetupButtonStyle = [this](FButtonStyle& Style, UMaterial* Image, UMaterial* HoverImage)
	{
		if (!Image || !HoverImage)
		{
			UE_LOG(LogTemp, Error, TEXT("Image or HoverImage is null"));
			return;
		}
		Style.Normal.SetResourceObject(Image);
		Style.Hovered.SetResourceObject(HoverImage);
		Style.Pressed.SetResourceObject(Image);
	
		Style.Normal.Margin = FMargin(0);
		Style.Hovered.Margin = FMargin(0);
		Style.Pressed.Margin = FMargin(0);
    
		Style.NormalPadding = FMargin(15);
		Style.PressedPadding = FMargin(15);
	};
	
	const bool bDarkMode = GameInstance->GetDarkMode();
	

	if (bDarkMode)
	{
		FSlateBrush WhiteThumb;
		WhiteThumb.SetResourceObject(DownArrowWhite);
		FSliderStyle SliderDarkStyle;
		SliderDarkStyle.SetNormalThumbImage(WhiteThumb);
		SliderDarkStyle.SetBarThickness(0.f);

		FSlateBrush BarFillDarkMode;
		BarFillDarkMode.SetResourceObject(EnergyLevelDarkFill);

		FSlateBrush BarFill;
		BarFill.SetResourceObject(EnergyLevelDarkFill);
		FSlateBrush BackgroundFill;
		BackgroundFill.SetResourceObject(EnergyLevelBorderDark);
		FProgressBarStyle EnergyBarStyle;
		EnergyBarStyle.SetFillImage(BarFill);
		EnergyBarStyle.SetBackgroundImage(BackgroundFill);
		
		MiniGameSlider->SetWidgetStyle(SliderDarkStyle);
		NotificationText->SetColorAndOpacity(White);
		SetCountTextBlock->SetColorAndOpacity(White);
		RepCountTextBlock->SetColorAndOpacity(White);
		DarkExitStyle.Normal.SetResourceObject(WhiteExitButton);
		DarkExitStyle.Hovered.SetResourceObject(WhiteHoveredExitButton);
		DarkExitStyle.Pressed.SetResourceObject(WhiteExitButton);
	}
	else
	{
		FSlateBrush BlackThumb;
		BlackThumb.SetResourceObject(DownArrowBlack);
		FSliderStyle SliderLightStyle;
		SliderLightStyle.SetNormalThumbImage(BlackThumb);
		SliderLightStyle.SetBarThickness(0.f);

		FSlateBrush BarFill;
		BarFill.SetResourceObject(EnergyLevelLightFill);
		FSlateBrush BackgroundFill;
		BackgroundFill.SetResourceObject(EnergyLevelBorderLight);
		FProgressBarStyle EnergyBarStyle;
		EnergyBarStyle.SetFillImage(BarFill);
		EnergyBarStyle.SetBackgroundImage(BackgroundFill);
		
		MiniGameSlider->SetWidgetStyle(SliderLightStyle);
		NotificationText->SetColorAndOpacity(Black);
		SetCountTextBlock->SetColorAndOpacity(Black);
		RepCountTextBlock->SetColorAndOpacity(Black);
		DarkExitStyle.Normal.SetResourceObject(BlackExitButton);
		DarkExitStyle.Hovered.SetResourceObject(BlackHoveredExitButton);
		DarkExitStyle.Pressed.SetResourceObject(BlackExitButton);
	}
}
void UExerciseInteractWidget_OM::WorkoutTutorial(float DeltaTime)
{
	if (!ClickImage) return;
	TimeSinceWorkoutTutorial += DeltaTime;

	if (ClickImage->GetVisibility() == ESlateVisibility::Hidden)
		ClickImage->SetVisibility(ESlateVisibility::Visible);

	if (FMath::IsNearlyEqual(TimeSinceWorkoutTutorial, 3.f, 0.7f)
		|| FMath::IsNearlyEqual(TimeSinceWorkoutTutorial, 5.2f, 0.5f))
	{ 
		if (ClickHand_Clicking)
			ClickImage->SetBrushResourceObject(ClickHand_Clicking);
	}
	else if (FMath::IsNearlyEqual(TimeSinceWorkoutTutorial, 4.6f, 0.5f))
	{
		if (ClickHand)
			ClickImage->SetBrushResourceObject(ClickHand);
	}
	else if (FMath::IsNearlyEqual(TimeSinceWorkoutTutorial, 7.f, 0.5f))
	{
		if (ClickHand)
			ClickImage->SetBrushResourceObject(ClickHand);
		TimeSinceWorkoutTutorial = 0.f;
	}

}
void UExerciseInteractWidget_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

			if (!bHasWorkedOutInitial)
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

void UExerciseInteractWidget_OM::NativeDestruct()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Super::NativeDestruct();
}

void UExerciseInteractWidget_OM::OnExitButtonClicked()
{
	if (!ExerciseComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ExerciseComponent is NULL"))
		return;
	}
	ExerciseComponent->LeaveExercise();

	


	Super::OnExitButtonClicked();

	if (UPlayerCharacterAnimInstance_OM* AnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(Player->GetMesh()->GetAnimInstance()))
	{
		AnimInstance->SetHasInjury(false);
	}
}

void UExerciseInteractWidget_OM::SetInjuryRisk()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

}

void UExerciseInteractWidget_OM::MiniGame(float InDeltaTime)
{
	if (BloodSplatter->GetVisibility() != ESlateVisibility::Hidden)
	{
		BloodSplatter->SetVisibility(ESlateVisibility::Hidden);
	}

	float ScaledSpeed = Speed * InDeltaTime;
//	FString MinAndMaxVals = FString::Printf(TEXT("RightMin: %.2f RightMax: %.2f\n LeftMin: %.2f LeftMax: %.2f\n"
//											  "LeftVal: %.2f RightVal: %.2f"), RightMin, RightMax, LeftMin, LeftMax, InjuryBoundsLeftValue, InjuryBoundsRightValue);
	
//	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, MinAndMaxVals);

	
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

void UExerciseInteractWidget_OM::SetSetAndRepCountTextBlocks()
{
	if (!ExerciseComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ExerciseComponent null in SetSetAndRepCountTextBlock"));
		return;
	}
	if (!SetCountTextBlock || !RepCountTextBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("SetCountTextBlock and/or RepCountTextBlock is null"));
		return;
	}

	const int SetCount = ExerciseComponent->GetSetCount();
	const int RepCount = ExerciseComponent->GetRepCount();
	
	const FText SetCountText = FText::Format(FText::FromString(TEXT("Set: {0}")), FText::AsNumber(SetCount));
	const FText RepCountText = FText::Format(FText::FromString(TEXT("Reps: {0}")), FText::AsNumber(RepCount));

	SetCountTextBlock->SetText(SetCountText);
	RepCountTextBlock->SetText(RepCountText);
	
}

void UExerciseInteractWidget_OM::SetSpecialSliderOn(const bool InSpecialSliderOn)
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

void UExerciseInteractWidget_OM::OnPlayModeChanged(EPlayModes InPlayMode)
{
	if (InPlayMode == EPlayModes::PauseMode)
		OnExitButtonClicked();
}

void UExerciseInteractWidget_OM::UpdateStats()
{
	const float EnergyLevel = ExerciseComponent->GetEnergy();
	if (EnergyLevel <= 0.f)
	{
		NotificationTextPopUp(TEXT("No Energy"));
		SetMiniGameOn(false);
	}
}



void UExerciseInteractWidget_OM::OnMiniGameClick()
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Pointer is NULL"));
		return;
	}
	if (!ExerciseComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ExerciseComponent Pointer is NULL"));
		return;
	}

	if (!bHasWorkedOutInitial)
	{
		GameInstance->SetHasDoneWorkoutInitial(true);
		bHasWorkedOutInitial = true;
		ClickImage->SetVisibility(ESlateVisibility::Hidden);
	}
		

	MiniGameClickButton->SetIsEnabled(false);

	
	float EnergyLevel = ExerciseComponent->GetEnergy();

	bDoingRep = true;
	if (Player)
		Player->SetIsDoingRep(bDoingRep);
	
	constexpr float SigmaOffset = 0.15f;
	if (bSpecialSliderOn && MiniGameSlider->GetValue() >= SpecialSlider->GetValue() - SigmaOffset && MiniGameSlider->GetValue() <= SpecialSlider->GetValue() + SigmaOffset)
	{
		SetSpecialSliderOn(false);
	}

	const float MajorInjuryBoundsValueLeft = (InjuryBoundsLeft->GetPercent()) / 2.f;
	const float MajorInjuryBoundsValueRight = 1.f - (InjuryBoundsRight->GetPercent()) / 2.f;

	const float MinorInjuryBoundsValueLeft = (MinorInjuryLeft->GetPercent()) / 2.f;
	const float MinorInjuryBoundsValueRight = 1.f - ((MinorInjuryRight->GetPercent()) / 2.f);

	//		S U C C E S F U L  
	if (MiniGameSlider->GetValue() >= MinorInjuryBoundsValueLeft && MiniGameSlider->GetValue() <= MinorInjuryBoundsValueRight)
	{
		//bMiniGameOn = false;
		ExerciseComponent->MiniGame();

		if (EnergyLevel <= 0.4f)
		{
			Speed += 0.01f;
		}
		LeftMax += 0.005f;
		RightMin -= 0.005f;
		InjuryBoundsLeftValue = 0.f;
		InjuryBoundsRightValue = 1.f;
		UpdateStats();
	}
	//				M I N O R  I N J U R Y
	else if (MiniGameSlider->GetValue() >= MajorInjuryBoundsValueLeft && MiniGameSlider->GetValue() <= MajorInjuryBoundsValueRight)
	{
		
		ExerciseComponent->Injury(EInjuryLevel::Minor);
		
		ExerciseComponent->MiniGame();

		UpdateStats();

		FName InjuredPartName = ExerciseComponent->GetCurrentInjuredPart()->Name;
		
		FString InjuryString = FString::Printf(TEXT("You have injured your: %s"), *InjuredPartName.ToString());
		NotificationTextPopUp(InjuryString);
		
	}
	else   //			M A J O R  I N J U R Y 
	{
		BloodSplatter->SetVisibility(ESlateVisibility::HitTestInvisible);
		ExerciseComponent->Injury(EInjuryLevel::Major);
		
		SetMiniGameOn(false);
	}
	if (!bSpecialSliderOn && ( EnergyLevel > 0.8f || EnergyLevel < 0.3f && EnergyLevel > 0.1))
	{
		SetSpecialSliderOn(true);
	}
	else
	{
		SetSpecialSliderOn(false);
	}

	SetInjuryRisk();

	SetSetAndRepCountTextBlocks();


}

void UExerciseInteractWidget_OM::SetNotificationText()
{
	if (!ExerciseComponent) return;
	const float EnergyLevel = ExerciseComponent->GetEnergy();
	if (EnergyLevel <= 0.f && CurrentWorkoutState == EWorkoutStates::SetComplete)
	{
		const FText SetCompleteNoEnergyText = FText::FromString("Last Set No Energy");
		NotificationText->SetText(SetCompleteNoEnergyText);
	}
	else if (EnergyLevel <= 0.f)
	{
		const FText NoEnergyText = FText::FromString("No Energy");
		NotificationText->SetText(NoEnergyText);
		
	}
	else if (CurrentWorkoutState == EWorkoutStates::SetComplete)
	{
		const FText SetCompleteText = FText::FromString("Set Complete");
		NotificationText->SetText(SetCompleteText);
	}
}

void UExerciseInteractWidget_OM::NotificationTextPopUp(const FString& InString) 
{
	//if (EnergyLevel > 0.f) return;
	SetNotificationText();
	constexpr float PopUpTimeShown = 2.f;

	NotificationText->SetText(FText::FromString(InString));
	NotificationText->SetVisibility(ESlateVisibility::Visible);
	
	GetWorld()->GetTimerManager().ClearTimer(TextPopUpDelayHandle);
	GetWorld()->GetTimerManager().SetTimer(
			TextPopUpDelayHandle,
			[this]()
			{
				NotificationText->SetVisibility(ESlateVisibility::Hidden);
			},
			PopUpTimeShown, 
			false 
		);
}

void UExerciseInteractWidget_OM::SetMiniGameOn(const bool InMiniGameOn)
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

