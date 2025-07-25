// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/AbilitySystemComponent_OM.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"


void UAbilitySystemComponent_OM::BeginPlay()
{
	Super::BeginPlay();

	BindFocusChangeDelegate();
	
}

void UAbilitySystemComponent_OM::BindFocusChangeDelegate()
{
	if (const UGymSpecificStats_OM* GymStats = GetSet<UGymSpecificStats_OM>())
	{
		GetGameplayAttributeValueChangeDelegate(GymStats->GetFocusAttribute()).AddUObject(this, &UAbilitySystemComponent_OM::OnFocusChanged);
	}
}

void UAbilitySystemComponent_OM::OnFocusChanged(const FOnAttributeChangeData& Data)
{
	UpdateFocusTags();
}

void UAbilitySystemComponent_OM::UpdateFocusTags()
{
	float Focus = GetNumericAttribute(UGymSpecificStats_OM::GetFocusAttribute());

	static const FGameplayTag FocusLowTag = FGameplayTag::RequestGameplayTag(TEXT("Stats.Gym.Focus.Low"));
	static const FGameplayTag FocusMediumTag = FGameplayTag::RequestGameplayTag(TEXT("Stats.Gym.Focus.Medium"));
	static const FGameplayTag FocusHighTag = FGameplayTag::RequestGameplayTag(TEXT("Stats.Gym.Focus.High"));
	
	RemoveLooseGameplayTag(FocusLowTag);
	RemoveLooseGameplayTag(FocusMediumTag);
	RemoveLooseGameplayTag(FocusHighTag);
	
	if (Focus < 0.3f)
	{
		AddLooseGameplayTag(FocusLowTag);
	}
	else if (Focus < 0.7f)
	{
		AddLooseGameplayTag(FocusMediumTag);
	}
	else
	{
		AddLooseGameplayTag(FocusHighTag);
	}
}
