// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/Abstract/PlayerAttributeSet_OM.h"
#include "GymSpecificStats_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UGymSpecificStats_OM : public UPlayerAttributeSet_OM
{
	GENERATED_BODY()
public:
	UGymSpecificStats_OM();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Focus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Bladder;

public:
	ATTRIBUTE_ACCESSORS_BASIC(UGymSpecificStats_OM, Focus);
	ATTRIBUTE_ACCESSORS_BASIC(UGymSpecificStats_OM, Energy);
	ATTRIBUTE_ACCESSORS_BASIC(UGymSpecificStats_OM, Bladder);

};