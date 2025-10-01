// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Structs/PlayerData.h"
#include "Utils/Structs/PlayModes.h"
#include "PostProcessController_OM.generated.h"

class UGymSpecificStats_OM;
class APlayerCharacter_OM;
class UGameInstance_OM;

UENUM()
enum class EEffectTickMode : uint8
{
	None		UMETA(DisplayName = "None"),
	WaveEffect	UMETA(DisplayName = "WaveEffect"),
	FadeIn		UMETA(DisplayName = "FadeIn"),
};
USTRUCT()
struct FPostProcessEffect
{
	GENERATED_USTRUCT_BODY()
	FPostProcessEffect() :
	Name("Invalid")
	{}
	FName Name;
	float Max;
	float Min;
	bool bGoingUp = false;
	bool bCurrentlyOn = false;
	float TickCounter = 0.f;
	TFunction<void(bool)> OverrideSetter;
	TFunction<float()> ValueGetter;
	TFunction<void(float)> ValueSetter;
	FTimerHandle TimerHandle;

	void WaveEffectTick(int EndTime, const float TickRate)
	{
		if (bGoingUp)
		{
			if (ValueGetter() >= Max) bGoingUp = false;
			ValueSetter(FMath::FInterpConstantTo(
			ValueGetter(), Max, 0.065, 0.5));
		}
		else
		{
			if (ValueGetter() <= Min) bGoingUp = true;
			ValueSetter(FMath::FInterpConstantTo(
			ValueGetter(), Min, 0.065, 0.5));
		}

		TickCounter += TickRate;
		if (TickCounter >= EndTime)
		{
			bCurrentlyOn = false;
		}
	}
	void FadeIn()
	{
		if (ValueGetter() < Max)
		{
			ValueSetter(FMath::FInterpConstantTo(
			ValueGetter(), Max, 0.065, 0.5));
		}
		else
		{
			// This will be on, so maybe a better naming convention.
			bCurrentlyOn = false;
		}
	}
};

UCLASS(Blueprintable)
class OPTIMIZEMAN_API APostProcessController_OM : public AActor
{
	GENERATED_BODY()
public:
	APostProcessController_OM();
protected:
	/** Overrides **/
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void InitializeEffects();

	UFUNCTION()
	void CheckDarkMode();
	UFUNCTION()
	void SetDarkMode(bool bDark);
	UFUNCTION()
	void ManageEffectsOnPlayMode(EPlayModes CurrentPlayMode);
	UFUNCTION()
	void OnEnergyBelowThreshold(float InEnergyVal);
	UFUNCTION()
	void CameraFadeTick();
	UFUNCTION()
	void ManageEffectsOnTempEmotion(ETemporaryEmotionalStates InState);

	
	void StartEffect(FName InEffectName, int MinTime, int MaxTime,
	                 EEffectTickMode InEffectTickMode);


	/** Effects Array **/
	TArray<FPostProcessEffect> Effects;

public:
	/** Effects Callers **/
	UFUNCTION(BlueprintCallable)
	void StartFilmGrainEffects();
	UFUNCTION(BlueprintCallable)
	void StartChromaticEffects();
	UFUNCTION(BlueprintCallable)
	void StartVignetteEffect(EEffectTickMode EffectType = EEffectTickMode::FadeIn, int MinTime = 2, int MaxTime = 5);

	/** Getters/Setters **/
	FPostProcessEffect& GetEffect(FName InName);

protected:
	/** Effects Ticks **/

	
	/** Serialized Effect Params **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MaxChromaticIntensity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MinChromaticOffset = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MaxChromaticOffset = 1.f;

	bool bChromaticGoingUp = true;

	

private:
	UPROPERTY(EditAnywhere)
	float FadeDuration = 10.f;
	float LeftoverFadeDuration = 10.f;
	float CameraFadeTickRate = 0.065;
	float CurrentFadeAmount = 0.f;

	UPROPERTY(EditAnywhere)
	float LowestEnergyThreshold = 0.1f;
	
	bool bFilmGrainOn = false;
	bool bChromaticOn = false;
	bool bVignetteOn = false;
	
	float ChromaticTickCounter = 0.f;
	float FilmGrainTickCounter = 0.f;
	const float TickRate = 0.1f;

	FTimerHandle VignetteTickHandle;
	FTimerHandle ChromaticTickHandle;
	FTimerHandle FilmGrainIntensityHandle;
	FTimerHandle FilmGrainTexelSizeHandle;


	/** Class Cache **/
	UPROPERTY()
	UGameInstance_OM* GameInstance;
	UPROPERTY()
	APlayerCharacter_OM* Player;
	UPROPERTY()
	APlayerCameraManager* CameraManager;

	UPROPERTY()
	const UGymSpecificStats_OM* GymStats;


	FTimerHandle CameraFadeHandle;


protected:
	UPROPERTY(EditInstanceOnly, Category="PostProcess")
	APostProcessVolume* GlobalPostProcessVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PostProcessing)
	UMaterialInterface* DarkModeMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PostProcessing)
	UMaterialInterface* LightModeMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* DarkModeMID;
	UPROPERTY()
	UMaterialInstanceDynamic* LightModeMID;

	

private:
	float TargetFilmSlope;
	float FilmSlopeFadeSpeed;
	
	float TargetVignette;
	float VignetteFadeSpeed;

	float TargetBloom;
	float BloomFadeSpeed;

	float TargetLensDistortion;
	float LensDistortionFadeSpeed;

};

