// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "Slider_OM.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API USlider_OM : public USlider
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	bool bHasColourLerp = true;


	UPROPERTY(EditAnywhere)
	FLinearColor MinColour;
	UPROPERTY(EditAnywhere)
	FLinearColor MaxColour;
};
