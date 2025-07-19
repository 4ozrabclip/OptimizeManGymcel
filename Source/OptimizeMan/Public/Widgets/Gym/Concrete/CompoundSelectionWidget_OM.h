// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/ExerciseData.h"
#include "Widgets/Gym/Abstract/ExerciseSelectionParentWidget_OM.h"
#include "CompoundSelectionWidget_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UCompoundSelectionWidget_OM : public UExerciseSelectionParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void CheckAndSetEquipmentType() override;
	virtual void InitialOpen() override;
	virtual void OpenLayer(UGridPanel* InGrid) const override;

	void AssignWorkoutButtons();
	UFUNCTION()
	void OnSelectWorkoutButtonClicked() { OpenLayer(SelectWorkout_Grid); }

	UFUNCTION()
	void SetExerciseSquat() { SetExerciseType(EExerciseType::Squat); };
	UFUNCTION()
	void SetExerciseCurl() { SetExerciseType(EExerciseType::BicepCurl); };
	UFUNCTION()
	void SetExerciseOverheadPress() { SetExerciseType(EExerciseType::OverheadPress); };
	UFUNCTION()
	void SetExerciseLeftCurl() { SetExerciseType(EExerciseType::LeftCurl); };
	UFUNCTION()
	void SetExerciseRightCurl() { SetExerciseType(EExerciseType::RightCurl); };
	UFUNCTION()
	void SetExerciseChestDip() { SetExerciseType(EExerciseType::ChestDip); }
	
	virtual void SetExerciseType(EExerciseType InExerciseType) override;


protected:
	UPROPERTY(meta = (BindWidget))
	UGridPanel* SelectWorkout_Grid;

	UPROPERTY(meta = (BindWidget))
	UButton* WorkoutType1_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* WorkoutType2_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* WorkoutType3_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WorkoutType1_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WorkoutType2_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WorkoutType3_Text;

private:




};


