// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/ExerciseData.h"
#include "Widgets/Gym/Concrete/ExerciseMinigameWidget_OM.h"
#include "TimingGaugeMinigame_OM.generated.h"

class UExercise_OM;
class USlider;
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UTimingGaugeMinigame_OM : public UExerciseMinigameWidget_OM
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;

	virtual void SetWorkoutState(EWorkoutStates NewWorkoutState) override;
	virtual void CheckAndSetStyles() override;

	virtual void OnMiniGameClick() override;

	virtual void MiniGameTutorial() override;

	
	void WorkoutTutorial(float DeltaTime);
public:
	void MiniGame(float InDeltaTime);

	void SetNotificationText();
	void SetInjuryRisk();
	void SetSetAndRepCountTextBlocks();


	UFUNCTION(BlueprintCallable)
	void UpdateStats();


	UFUNCTION(BlueprintCallable)
	void NotificationTextPopUp(const FString& InString = "");
	UFUNCTION(BlueprintCallable)
	bool GetMiniGameOn() const { return bMiniGameOn; }
	UFUNCTION(BlueprintCallable)
	void SetMiniGameOn(const bool InMiniGameOn);
	UFUNCTION(BlueprintCallable)
	void SetSpecialSliderOn(const bool InSpecialSliderOn);
	UFUNCTION(BlueprintCallable)
	bool GetSpecialSliderOn() const { return bSpecialSliderOn; };


protected:
	UPROPERTY(EditAnywhere, Category = "MiniGameSpeed")
	float Speed = 1.f;

	UPROPERTY(EditAnywhere, Category = "MiniGameSpeed")
	float Divider = 10.f;


	FTimerHandle MiniGameTickHandle;
	FTimerHandle TextPopUpDelayHandle;
	FTimerHandle ChangeWorkoutButtonHandle;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelLightFill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelDarkFill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelBorderLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light mode")
	UMaterial* EnergyLevelBorderDark;


	
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* MiniGameSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* WinBoundsLeftSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* WinBoundsRightSlider;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USlider* SpecialSlider;


	
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


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ClickImage;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Images")
	UTexture2D* ClickHand;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Images")
	UTexture2D* ClickHand_Clicking;




// --- images for dark/light mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* DownArrowBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* DownArrowWhite;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SigmaWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/LightMode images")
	UMaterial* SigmaBlack;



	/** Class Cache **/
	UPROPERTY()
	UExercise_OM* ExerciseComponent;


	
private: //Priv variables

	EMinigameResult NewResult = EMinigameResult::None;
	float NewEnergyFactor = 1.f;


	
	bool bSpecialSliderOn = false;
	bool bMiniGameOn = false;


	

	
	float InjuryBoundsLeftValue = 0.f;
	float InjuryBoundsRightValue = 1.f;
	float MinorInjuryBoundsLeftValue = 0.f;
	float MinorInjuryBoundsRightValue = 1.f;
	
	float SliderValue = 0.f;

	float TimeSinceWorkoutTutorial = 0.f;
	
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
