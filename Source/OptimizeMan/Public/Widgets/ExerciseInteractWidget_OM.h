// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinigameBaseWidget_OM.h"
#include "Actors/Characters/Player/Components/Exercise_OM.h"
#include "Blueprint/UserWidget.h"
#include "Utils/Structs/ExerciseData.h"
#include "ExerciseInteractWidget_OM.generated.h"

/**
 * 
 */
class USlider;
UCLASS()
class OPTIMIZEMAN_API UExerciseInteractWidget_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	UFUNCTION()
	void SetWorkoutState(EWorkoutStates NewWorkoutState) { CurrentWorkoutState = NewWorkoutState; };
	void CheckAndSetEquipmentType();
	UFUNCTION()
	void CheckAndSetStyles();

	void SetNotificationText();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void OnExitButtonClicked() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateStats();

	UFUNCTION(BlueprintCallable)
	void OnMiniGameClick();

	UFUNCTION(BlueprintCallable)
	void NotificationTextPopUp();
	void SetChangeWorkoutOption(bool InChangeWorkoutOn);

	UFUNCTION(BlueprintCallable)
	bool GetMiniGameOn() const { return bMiniGameOn; }

	UFUNCTION(BlueprintCallable)
	void SetMiniGameOn(const bool InMiniGameOn);

	void MiniGame(float InDeltaTime);
	void SetSetAndRepCountTextBlocks();

	UFUNCTION(BlueprintCallable)
	void SetSpecialSliderOn(const bool InSpecialSliderOn);
	UFUNCTION()
	void OnChangeButtonClicked();

	UFUNCTION(BlueprintCallable)
	bool GetSpecialSliderOn() const { return bSpecialSliderOn; };

protected:

	EWorkoutStates CurrentWorkoutState;

	UPROPERTY(EditAnywhere, Category = "MiniGameSpeed")
	float Speed = 1.f;

	UPROPERTY(EditAnywhere, Category = "MiniGameSpeed")
	float Divider = 10.f;

	FTimerHandle RepTimeHandle;
	FTimerHandle TextPopUpDelayHandle;
	FTimerHandle ChangeWorkoutButtonHandle;

	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* EnergyLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelLightFill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelDarkFill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelBorderLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelBorderDark;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EnergyText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NotificationText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MiniGameClickButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* WorkoutOptionButton_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* WorkoutOptionButton_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* WorkoutOptionButton_3;
	UPROPERTY(meta = (BindWidget))
	UButton* ChangeWorkoutButton;
	
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* MiniGameSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* WinBoundsLeftSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* WinBoundsRightSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* SpecialSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* BloodSplatter;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* InjuryBoundsLeft;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* InjuryBoundsRight;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* MinorInjuryLeft;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* MinorInjuryRight;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* RepCountTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SetCountTextBlock;

	
	
	UPROPERTY()
	class UExercise_OM* ExerciseComponent;

// --- images for dark/light mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* DownArrowBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* DownArrowWhite;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SigmaWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SigmaBlack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SquatWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SquatBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SquatHoverWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SquatHoverBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* CurlWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* CurlBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* CurlHoverWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* CurlHoverBlack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* LeftCurlWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* LeftCurlHoverWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* LeftCurlBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* LeftCurlHoverBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* RightCurlWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* RightCurlHoverWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* RightCurlBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* RightCurlHoverBlack;

	
	FButtonStyle SquatDarkStyle;
	FButtonStyle CurlDarkStyle;
	FButtonStyle LeftCurlDarkStyle;
	FButtonStyle RightCurlDarkStyle;
	
	FButtonStyle SquatLightStyle;
	FButtonStyle CurlLightStyle;
	FButtonStyle LeftCurlLightStyle;
	FButtonStyle RightCurlLightStyle;



	UPROPERTY()
	class UGridPanel* ExerciseTypesGrid;

	


private:
	void OnExerciseButtonClicked(const EButtonOptions InButton);
	void DisableEnableUnusableButtonsHelper();

	UFUNCTION()
	void OnWorkoutOptionButton_1Clicked() { OnExerciseButtonClicked(EButtonOptions::ButtonOne); }
	UFUNCTION()
	void OnWorkoutOptionButton_2Clicked() { OnExerciseButtonClicked(EButtonOptions::ButtonTwo); }

protected:
	UPROPERTY()
	EEquipmentTypes CurrentEquipmentType;

private: //Priv variables
	bool bSpecialSliderOn = false;
	bool bMiniGameOn = false;

	bool bDoingRep = false;
	
	float InjuryBoundsLeftValue = 0.f;
	float InjuryBoundsRightValue = 1.f;
	float MinorInjuryBoundsLeftValue = 0.f;
	float MinorInjuryBoundsRightValue = 1.f;
	
	float SliderValue = 0.f;
	
	float MainSliderTime;
	float MainSliderPhase;
	
	float SpecialSliderValue = 0.f;
	float SpecialSliderTime;
	float SpecialSliderPhase;
	bool bSpecialSliderPhaseIncreasing;
	const float PhaseChangeInterval = 2.f;
	
	bool bLeftMovingUp = true;
	bool bRightMovingUp = false;
	bool bMovingRight = true;
	

	float MinValue = 0.0f;
	float MaxValue = 1.0f;
	float LeftMin = 0.0f;
	float LeftMax = 0.25f;
	float RightMin = 0.75f;
	float RightMax = 1.0f;



	
};

