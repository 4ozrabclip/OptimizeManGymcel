// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/IsolatedSelectionWidget_OM.h"

#include "Actors/Other/Gym/Concrete/LegPress_OM.h"
#include "Components/Button.h"

void UIsolatedSelectionWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	if (SelectWeight_Button)
	{
		SelectWeight_Button->OnClicked.Clear();
		SelectWeight_Button->OnClicked.AddDynamic(this, &UIsolatedSelectionWidget_OM::OpenWeightSelect);
	}
}

void UIsolatedSelectionWidget_OM::CheckAndSetEquipmentType()
{
	Super::CheckAndSetEquipmentType();
	if (ExerciseEquipment->IsA<ALegPress_OM>())
	{
		CurrentEquipmentType = EEquipmentTypes::Legpress;
		SetExerciseType(EExerciseType::LegPress);
	}
}

void UIsolatedSelectionWidget_OM::SetExerciseType(EExerciseType InExerciseType)
{
	Super::SetExerciseType(InExerciseType);

	const FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	switch (InExerciseType)
	{
	case EExerciseType::LegPress:
		SetMuscleGroupCurrentStrength(GameInstance->GetBodyPartLeftRightCombinedStrengthValue(EBodyPart::Thigh));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Thigh, EBodyPartSide::Left));
		ExerciseComponent->SetBodyPartInUse(*GameInstance->FindBodyPart(EBodyPart::Thigh, EBodyPartSide::Right));
		break;
	default:
		break;
	}
}
