// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EnergyNegateHitExecCalc_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UEnergyNegateHitExecCalc_OM : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UEnergyNegateHitExecCalc_OM();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
