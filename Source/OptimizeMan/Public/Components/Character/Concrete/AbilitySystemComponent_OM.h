// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemComponent_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UAbilitySystemComponent_OM : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void UpdateFocusTags();

protected:
	virtual void BeginPlay() override;
	
	void BindFocusChangeDelegate();
	
	void OnFocusChanged(const FOnAttributeChangeData& Data);
	
};
