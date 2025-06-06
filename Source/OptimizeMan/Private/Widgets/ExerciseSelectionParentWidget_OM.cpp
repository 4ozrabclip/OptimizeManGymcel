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

	
	if (SelectWeight_Button)
	{
		SelectWeight_Button->OnClicked.Clear();
		SelectWeight_Button->OnClicked.AddDynamic(this, &UExerciseSelectionParentWidget_OM::OnSelectWeightButtonClicked);
	}
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

	if (WeightSelect_Slider)
	{
		WeightSelect_Slider->SetStepSize(0.25f);

		WeightSelect_Slider->OnValueChanged.Clear();
		WeightSelect_Slider->OnValueChanged.AddDynamic(this, &UExerciseSelectionParentWidget_OM::UpdateWeightSelectText);
	}

	if (APlayerCharacter_OM* Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		ExerciseComponent = Player->GetComponentByClass<UExercise_OM>();
		if (!ExerciseComponent)
			return;
	}

	InitialOpen();
}

void UExerciseSelectionParentWidget_OM::InitialOpen()
{
	OpenLayer(Main_Grid);
}

void UExerciseSelectionParentWidget_OM::UpdateWeightSelectText(float InValue)
{
	WeightSelectText_String = FString::Printf(TEXT("%.2f"), InValue);
	WeightSelect_Text->SetText(FText::FromString(WeightSelectText_String));
}

void UExerciseSelectionParentWidget_OM::OnSelectWeightButtonClicked()
{
	OpenLayer(WeightSelect_Grid);

}

void UExerciseSelectionParentWidget_OM::OnBackFromWeightSelectClicked()
{
	OpenLayer(Main_Grid);
}

void UExerciseSelectionParentWidget_OM::OnWeightConfirmed()
{
	SelectedWeight = WeightSelect_Slider->GetValue();	

	if (ExerciseEquipment)
	{
		ExerciseEquipment->ChangeWeight(SelectedWeight);
	}
}

void UExerciseSelectionParentWidget_OM::OpenLayer(UGridPanel* InGrid) const
{
	if (InGrid == nullptr) return;
	Main_Grid->SetVisibility(ESlateVisibility::Hidden);
	WeightSelect_Grid->SetVisibility(ESlateVisibility::Hidden);

	InGrid->SetVisibility(ESlateVisibility::Visible);
}
