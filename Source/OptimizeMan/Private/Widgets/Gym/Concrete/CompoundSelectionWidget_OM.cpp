// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/CompoundSelectionWidget_OM.h"

#include "Actors/Other/Gym/Abstract/ExerciseEquipment_OM.h"
#include "Actors/Other/Gym/Concrete/Barbell_OM.h"
#include "Actors/Other/Gym/Concrete/DipBar_OM.h"
#include "Actors/Other/Gym/Concrete/Dumbell_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Character/Concrete/Exercise_OM.h"

void UCompoundSelectionWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (SelectWeight_Button)
	{
		SelectWeight_Button->OnClicked.Clear();
		SelectWeight_Button->OnClicked.AddDynamic(this, &UCompoundSelectionWidget_OM::OnSelectWorkoutButtonClicked);
	}


	AssignWorkoutButtons();
}
void UCompoundSelectionWidget_OM::CheckAndSetEquipmentType()
{
	Super::CheckAndSetEquipmentType();
	 
	if (ExerciseEquipment->IsA<ABarbell_OM>())
	{
		CurrentEquipmentType = EEquipmentTypes::Barbell;
	}
	else if (ExerciseEquipment->IsA<ADumbell_OM>())
	{
		CurrentEquipmentType = EEquipmentTypes::Dumbell;
	}
	else if (ExerciseEquipment->IsA<ADipBar_OM>())
	{
		CurrentEquipmentType = EEquipmentTypes::Dipbar;
	}
}
void UCompoundSelectionWidget_OM::AssignWorkoutButtons()
{
	if (!ExerciseComponent)
	{
		ExerciseEquipment->TurnOffWidget();
		return;
	}
	switch (CurrentEquipmentType)
	{
		case EEquipmentTypes::Barbell:
			{
				const FText SquatText = FText::FromString("Squat");
				WorkoutType1_Text->SetText(SquatText);
				WorkoutType1_Button->OnClicked.Clear();
				WorkoutType1_Button->OnClicked.AddDynamic(this, &UCompoundSelectionWidget_OM::SetExerciseSquat);
				const FText CurlText = FText::FromString("Curl");
				WorkoutType2_Text->SetText(CurlText);
				WorkoutType2_Button->OnClicked.Clear();
				WorkoutType2_Button->OnClicked.AddDynamic(this, &UCompoundSelectionWidget_OM::SetExerciseCurl);

				WorkoutType3_Button->SetVisibility(ESlateVisibility::Hidden);
				break;
			}
		case EEquipmentTypes::Dumbell:
			{
				const FText LeftCurlText = FText::FromString("LeftCurl");
				WorkoutType1_Text->SetText(LeftCurlText);
				WorkoutType1_Button->OnClicked.Clear();
				WorkoutType1_Button->OnClicked.AddDynamic(this, &UCompoundSelectionWidget_OM::SetExerciseLeftCurl);
				const FText RightCurlText = FText::FromString("RightCurl");
				WorkoutType2_Text->SetText(RightCurlText);
				WorkoutType2_Button->OnClicked.Clear();
				WorkoutType2_Button->OnClicked.AddDynamic(this, &UCompoundSelectionWidget_OM::SetExerciseRightCurl);

				WorkoutType3_Button->SetVisibility(ESlateVisibility::Hidden);
				break;
			}
		case EEquipmentTypes::Dipbar:
			{
				const FText ChestDipsText = FText::FromString("ChestDips");
				WorkoutType1_Text->SetText(ChestDipsText);
				WorkoutType1_Button->OnClicked.Clear();
				WorkoutType1_Button->OnClicked.AddDynamic(this, &UCompoundSelectionWidget_OM::SetExerciseChestDip);

				WorkoutType2_Button->SetVisibility(ESlateVisibility::Hidden);
				WorkoutType3_Button->SetVisibility(ESlateVisibility::Hidden);
				break;
			}
		default:
			{
				ExerciseEquipment->TurnOffWidget();
				return;
			}
	}
}

void UCompoundSelectionWidget_OM::InitialOpen()
{
	Super::InitialOpen();

	SelectWeight_Button->SetVisibility(ESlateVisibility::Visible);
}

void UCompoundSelectionWidget_OM::OpenLayer(UGridPanel* InGrid) const
{
	SelectWorkout_Grid->SetVisibility(ESlateVisibility::Hidden);
	Super::OpenLayer(InGrid);
}

void UCompoundSelectionWidget_OM::SetExerciseType(EExerciseType InExerciseType)
{
	Super::SetExerciseType(InExerciseType);

	const FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	switch (InExerciseType)
	{
	case EExerciseType::Squat:
		SetMuscleGroupCurrentStrength(GameInstance->GetBodyPartLeftRightCombinedStrengthValue(EBodyPart::Thigh));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Thigh, EBodyPartSide::Left));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Thigh, EBodyPartSide::Right));
		break;
	case EExerciseType::BicepCurl:
		SetMuscleGroupCurrentStrength(GameInstance->GetBodyPartLeftRightCombinedStrengthValue(EBodyPart::Arm));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Arm, EBodyPartSide::Left));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Arm, EBodyPartSide::Right));
		break;
	case EExerciseType::LeftCurl:
		SetMuscleGroupCurrentStrength(GameInstance->GetBodyPartStrengthValue(EBodyPart::Arm, EBodyPartSide::Left));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Arm, EBodyPartSide::Left));
		break;
	case EExerciseType::RightCurl:
		SetMuscleGroupCurrentStrength(GameInstance->GetBodyPartStrengthValue(EBodyPart::Arm, EBodyPartSide::Right));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Arm, EBodyPartSide::Left));
		break;
	case EExerciseType::ChestDip:
		SetMuscleGroupCurrentStrength(GameInstance->GetBodyPartStrengthValue(EBodyPart::Chest, EBodyPartSide::Center));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Chest, EBodyPartSide::Center));
		break;
	default:
		SetMuscleGroupCurrentStrength(GameInstance->GetBodyPartStrengthValue(EBodyPart::Abdominal, EBodyPartSide::Center));
		break;
	}

	OpenLayer(WeightSelect_Grid);
}