// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "ExerciseSelectionParentWidget_OM.generated.h"

class UTensionSliderObj_OM;
class AExerciseEquipment_OM;
class UTextBlock;
class USlider;
class UGridPanel;
class UButton;
/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API UExerciseSelectionParentWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void CheckAndSetDarkMode();

	UFUNCTION()
	virtual void InitialOpen();
	UFUNCTION()
	void OnSelectWeightButtonClicked();
	UFUNCTION()
	void OnBackFromWeightSelectClicked();
	UFUNCTION()
	void OnWeightConfirmed();
	UFUNCTION()
	void UpdateWeightSelect(float InValue);
	UFUNCTION()
	void InitEquipment(AExerciseEquipment_OM* InEquipment) { ExerciseEquipment = InEquipment;}
	
	virtual void OpenLayer(UGridPanel* InGrid) const;
	void SetMuscleGroupCurrentStrength(float InStrength);

protected:
//Widget properties
	UPROPERTY(meta = (BindWidget))
	UButton* SelectWeight_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromWeightSelect_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Exit_Button;

	// Weight Select
	UPROPERTY(meta = (BindWidget))
	USlider* WeightSelect_Slider;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightSelect_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmWeight_Button;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* Main_Grid;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* WeightSelect_Grid;

//Other properties
	UPROPERTY()
	AExerciseEquipment_OM* ExerciseEquipment;
	UPROPERTY()
	UExercise_OM* ExerciseComponent;


	float EquipmentMaxWeight;
	float EquipmentMinWeight;

	
	float SelectedWeight = 0.f;

	float MuscleGroupCurrentStrength = 0.f;

	

private:

	UPROPERTY()
	FString WeightSelectText_String;


};
