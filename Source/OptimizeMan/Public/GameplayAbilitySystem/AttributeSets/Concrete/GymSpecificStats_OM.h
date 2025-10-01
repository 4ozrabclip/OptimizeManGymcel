// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/Abstract/PlayerAttributeSet_OM.h"
#include "GymSpecificStats_OM.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatBelowThreshold, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatEmpty);

UCLASS()
class OPTIMIZEMAN_API UGymSpecificStats_OM : public UPlayerAttributeSet_OM
{
	GENERATED_BODY()
public:
	UGymSpecificStats_OM();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatBelowThreshold OnEnergyBelowThreshold;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatEmpty OnEnergyEmpty;



	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Focus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Bladder;


private:
	float EnergyThreshold = 0.7f;
	float FocusThreshold = 0.5f;
	bool bCanTriggerFocusLow = true;
	bool bCanTriggerEnergyLow = true;

public:
	ATTRIBUTE_ACCESSORS_BASIC(UGymSpecificStats_OM, Focus);
	ATTRIBUTE_ACCESSORS_BASIC(UGymSpecificStats_OM, Energy);
	ATTRIBUTE_ACCESSORS_BASIC(UGymSpecificStats_OM, Bladder);

};