// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/Abstract/CharacterComponentBase_OM.h"
#include "PlayerAmbienceControlComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OPTIMIZEMAN_API UPlayerAmbienceControlComponent : public UCharacterComponentBase_OM
{
	GENERATED_BODY()
public:
	UPlayerAmbienceControlComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


private:
	int BreathStrength = 1;
};
