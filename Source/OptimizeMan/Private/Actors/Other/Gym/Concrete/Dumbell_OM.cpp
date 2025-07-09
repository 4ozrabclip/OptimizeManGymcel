// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/Dumbell_OM.h"

#include "Components/BoxComponent.h"

ADumbell_OM::ADumbell_OM()
{
	ExtraCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtraCollider"));
	ExtraCollider->SetCollisionProfileName(TEXT("Default"));
	ExtraCollider->SetupAttachment(RootComponent);
}

void ADumbell_OM::BeginPlay()
{
	Super::BeginPlay();
	SetInteractableWidgetText("Lift Weight");
}

void ADumbell_OM::Interact_Implementation()
{
	Super::Interact_Implementation(); 
}
