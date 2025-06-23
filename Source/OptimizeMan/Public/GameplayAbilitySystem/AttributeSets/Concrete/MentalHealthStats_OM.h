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
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Ego;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Social;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData SexAppeal;

public:
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UMentalHealthStats_OM, Ego);
	float GetEgo() const;
	void SetEgo(const float InEgo);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Ego);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UMentalHealthStats_OM, Social);
	float GetSocial() const;
	void SetSocial(const float InSocial);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Social);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UMentalHealthStats_OM, SexAppeal);
	float GetSexAppeal() const;
	void SetSexAppeal(const float InSexAppeal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(SexAppeal);
	
};
