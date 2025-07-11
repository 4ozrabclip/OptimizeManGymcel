// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PostProcessController_OM.generated.h"

class UGameInstance_OM;
class IPersistentStateProvider_OM;

UCLASS(Blueprintable)
class OPTIMIZEMAN_API APostProcessController_OM : public AActor
{
	GENERATED_BODY()
public:
	APostProcessController_OM();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckDarkMode();
	UFUNCTION()
	void SetDarkMode(bool bDark);


public:
	/** Effects Callers **/
	UFUNCTION(BlueprintCallable)
	void StartFilmGrainEffect();

	UFUNCTION(BlueprintCallable)
	void StartVignetteEffect();
	UFUNCTION(BlueprintCallable)
	void RemoveVignetteEffect();
	UFUNCTION(BlueprintCallable)
	void StartChromaticEffects();
	UFUNCTION(BlueprintCallable)
	void RemoveChromaticEffects();
protected:
	/** Effects Ticks **/
	void VignetteEffectTick(FPostProcessSettings& Settings);
	void RemoveVignetteEffectTick(FPostProcessSettings& Settings);
	void RemoveChromaticEffectsTick(FPostProcessSettings& Settings);
	void ChromaticEffectsTick(const int EndTime, FPostProcessSettings& Settings);
	void FilmGrainEffectTick(int EndTime);
	
	/** Serialized Effect Params **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MaxChromaticIntensity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MinChromaticOffset = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MaxChromaticOffset = 1.f;

	bool bGoingUp = true;
	
	

private:
	bool bFilmGrainOn = false;
	bool bChromaticOn = false;
	bool bVignetteOn = false;
	
	float ChromaticTickCounter = 0.f;
	float FilmGrainTickCounter = 0.f;
	const float TickRate = 0.1f;

	FTimerHandle VignetteTickHandle;
	FTimerHandle ChromaticTickHandle;
	FTimerHandle FilmGrainEffectHandle;
	UPROPERTY()
	UGameInstance_OM* GameInstance;


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

