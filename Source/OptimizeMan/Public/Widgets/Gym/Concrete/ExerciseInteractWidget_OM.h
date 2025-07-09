// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Utils/Structs/ExerciseData.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "ExerciseInteractWidget_OM.generated.h"

class UProgressBar;
class UTextBlock;
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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void OnExitButtonClicked() override;

	void MiniGame(float InDeltaTime);

	void SetNotificationText();
	void SetInjuryRisk();
	void SetSetAndRepCountTextBlocks();

	UFUNCTION()
	void SetWorkoutState(EWorkoutStates NewWorkoutState) { CurrentWorkoutState = NewWorkoutState; };
	UFUNCTION()
	void CheckAndSetStyles();
	UFUNCTION(BlueprintCallable)
	void UpdateStats();
	UFUNCTION(BlueprintCallable)
	void OnMiniGameClick();
	UFUNCTION(BlueprintCallable)
	void NotificationTextPopUp();
	UFUNCTION(BlueprintCallable)
	bool GetMiniGameOn() const { return bMiniGameOn; }
	UFUNCTION(BlueprintCallable)
	void SetMiniGameOn(const bool InMiniGameOn);
	UFUNCTION(BlueprintCallable)
	void SetSpecialSliderOn(const bool InSpecialSliderOn);
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
	UProgressBar* EnergyLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelLightFill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelDarkFill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelBorderLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelBorderDark;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnergyText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NotificationText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MiniGameClickButton;
	
	
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
	UExercise_OM* ExerciseComponent;

// --- images for dark/light mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* DownArrowBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* DownArrowWhite;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SigmaWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SigmaBlack;
	


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

