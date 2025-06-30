#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PlayModes.generated.h"

USTRUCT(BlueprintType) // Will need to do some more setup on the gameplay tag state manager here
struct FPlayModeConfig
{
	GENERATED_USTRUCT_BODY()
	
	FPlayModeConfig()
	: bSetToUiMode(false)
	, bAllowGameMovement(true)
	, bHasWidget(true)
	, ForcedLocation(FVector::ZeroVector)
	, ForcedRotation(FRotator::ZeroRotator)
	, bHasAFadeIn(false)
	, bNeedsPreSteps(false)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSetToUiMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllowGameMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForcedLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator ForcedRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasAFadeIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bNeedsPreSteps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag StateTag;
	
};