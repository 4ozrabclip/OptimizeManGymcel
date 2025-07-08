// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/DrinkingFountain_OM.h"


ADrinkingFountain_OM::ADrinkingFountain_OM()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADrinkingFountain_OM::BeginPlay()
{
	Super::BeginPlay();

	SetInteractableWidgetText("Under Construction");
	
}

void ADrinkingFountain_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	
}
