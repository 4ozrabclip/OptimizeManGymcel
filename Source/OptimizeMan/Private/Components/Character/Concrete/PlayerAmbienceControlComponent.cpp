// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/PlayerAmbienceControlComponent.h"


UPlayerAmbienceControlComponent::UPlayerAmbienceControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UPlayerAmbienceControlComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPlayerAmbienceControlComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

