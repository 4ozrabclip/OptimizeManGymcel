// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/Abstract/PlayerAttributeSet_OM.h"
#include "MentalHealthStats_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UMentalHealthStats_OM : public UPlayerAttributeSet_OM
{
	GENERATED_BODY()
public:
	UMentalHealthStats_OM();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Ego;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Social;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData SexAppeal;

public:
	ATTRIBUTE_ACCESSORS_BASIC(UMentalHealthStats_OM, Ego);
	ATTRIBUTE_ACCESSORS_BASIC(UMentalHealthStats_OM, Social);
	ATTRIBUTE_ACCESSORS_BASIC(UMentalHealthStats_OM, SexAppeal);
};
