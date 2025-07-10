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

	UFUNCTION(BlueprintCallable)
	void StartChromaticEffects();


	void ChromaticEffectsTick(const int EndTime, FPostProcessSettings& Settings);

	
	/** Serialized Effect Params **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MaxChromaticIntensity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MinChromaticOffset = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float MaxChromaticOffset = 1.f;

	bool bGoingUp = true;
	

private:
	float TimeSinceAnxietyTickStarted = 0.f;
	int AnxietyTickEndTime = 0;
	const float TickRate = 0.1f;

	float ChromaticTickCounter = 0.f;

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
	FTimerHandle AnxietyTickHandle;
	FTimerHandle ChromaticTickHandle;


	float TargetFilmSlope;
	float FilmSlopeFadeSpeed;
	
	float TargetVignette;
	float VignetteFadeSpeed;

	float TargetBloom;
	float BloomFadeSpeed;

	float TargetLensDistortion;
	float LensDistortionFadeSpeed;

};
