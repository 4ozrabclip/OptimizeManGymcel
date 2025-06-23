// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/AttributeSets/Abstract/PlayerAttributeSet_OM.h"
#include "GymSpecificStats_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UGymSpecificStats_OM : public UPlayerAttributeSet_OM
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Focus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gym Stats")
	FGameplayAttributeData Bladder;

public:
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UGymSpecificStats_OM, Focus)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Focus)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UGymSpecificStats_OM, Energy)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Energy)

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UGymSpecificStats_OM, Bladder)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Bladder)


	float GetFocus() const { return Focus.GetCurrentValue(); }
	void SetFocus(const float InFocus) { Focus.SetCurrentValue(InFocus); }
	
	float GetEnergy() const { return Energy.GetCurrentValue(); }
	void SetEnergy(const float InEnergy) { Energy.SetCurrentValue(InEnergy); }
	
	float GetBladder() const { return Bladder.GetCurrentValue(); }
	void SetBladder(float InBladder) { Bladder.SetCurrentValue(InBladder); }
};