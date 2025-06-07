// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/ExerciseSelectionParentWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/Components/Exercise_OM.h"
#include "Actors/Items/Gym/Equipment/ExerciseEquipment_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UExerciseSelectionParentWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	
	if (BackFromWeightSelect_Button)
	{
		BackFromWeightSelect_Button->OnClicked.Clear();
		BackFromWeightSelect_Button->OnClicked.AddDynamic(this, &UExerciseSelectionParentWidget_OM::OnBackFromWeightSelectClicked);
	}
	if (ExerciseEquipment && Exit_Button)
	{
		Exit_Button->OnClicked.Clear();
		Exit_Button->OnClicked.AddDynamic(ExerciseEquipment, &AExerciseEquipment_OM::TurnOffWidget);
	}
	if (ConfirmWeight_Button)
	{
		ConfirmWeight_Button->OnClicked.Clear();
		ConfirmWeight_Button->OnClicked.AddDynamic(this, &UExerciseSelectionParentWidget_OM::OnWeightConfirmed);
	}

	if (ExerciseEquipment && WeightSelect_Slider)
	{
		WeightSelect_Slider->MouseUsesStep = true;
		WeightSelect_Slider->SetStepSize(0.25f);

		WeightSelect_Slider->OnValueChanged.Clear();
		WeightSelect_Slider->OnValueChanged.AddDynamic(this, &UExerciseSelectionParentWidget_OM::UpdateWeightSelect);

		EquipmentMaxWeight = ExerciseEquipment->GetMaxWeight();
		EquipmentMinWeight = ExerciseEquipment->GetMinWeight();

		WeightSelect_Slider->SetMaxValue(EquipmentMaxWeight);
		WeightSelect_Slider->SetMinValue(EquipmentMinWeight);
	}


	if (APlayerCharacter_OM* Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		ExerciseComponent = Player->GetComponentByClass<UExercise_OM>();
		if (!ExerciseComponent)
			return;
	}

	CheckAndSetDarkMode();
	
	InitialOpen();
}

void UExerciseSelectionParentWidget_OM::CheckAndSetDarkMode()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (GameInstance->GetDarkMode())
	{
		WeightSelect_Text->SetColorAndOpacity(White);
	}
	else
	{
		WeightSelect_Text->SetColorAndOpacity(Black);
	}
}

void UExerciseSelectionParentWidget_OM::UpdateWeightSelect(float InValue)
{
	WeightSelectText_String = FString::Printf(TEXT("%.2f"), InValue);
	WeightSelect_Text->SetText(FText::FromString(WeightSelectText_String));
	
	const float NormalizedInput = FMath::Clamp((InValue - EquipmentMinWeight) / (EquipmentMaxWeight - EquipmentMinWeight), 0.0f, 1.0f);
	const float MuscleExertionRatio = FMath::Clamp((NormalizedInput - MuscleGroupCurrentStrength) * 5.f, 0.f, 1.f);

	

	const FLinearColor SafeColour = FLinearColor::Green;
	const FLinearColor DangerColour = FLinearColor::Red;
	const FLinearColor ResultColour = FLinearColor::LerpUsingHSV(SafeColour, DangerColour, MuscleExertionRatio);

	WeightSelect_Slider->SetSliderBarColor(ResultColour);
}

void UExerciseSelectionParentWidget_OM::OnWeightConfirmed()
{
	SelectedWeight = WeightSelect_Slider->GetValue();	

	if (ExerciseEquipment)
	{
		ExerciseEquipment->ChangeWeight(SelectedWeight);
		ExerciseEquipment->TurnOffWidget();
		ExerciseEquipment->StartWorkoutMode();
	}
}
void UExerciseSelectionParentWidget_OM::OpenLayer(UGridPanel* InGrid) const
{
	if (InGrid == nullptr) return;
	Main_Grid->SetVisibility(ESlateVisibility::Hidden);
	WeightSelect_Grid->SetVisibility(ESlateVisibility::Hidden);

	InGrid->SetVisibility(ESlateVisibility::Visible);
}

void UExerciseSelectionParentWidget_OM::InitialOpen()
{
	OpenLayer(Main_Grid);
}

void UExerciseSelectionParentWidget_OM::OnSelectWeightButtonClicked()
{
	OpenLayer(WeightSelect_Grid);
}

void UExerciseSelectionParentWidget_OM::OnBackFromWeightSelectClicked()
{
	OpenLayer(Main_Grid);
}

void UExerciseSelectionParentWidget_OM::SetMuscleGroupCurrentStrength(const float InStrength)
{
	//if (InStrength == 0.f)
	//	MuscleGroupCurrentStrength = InStrength + 0.05f;
	//else
	MuscleGroupCurrentStrength = InStrength;
}