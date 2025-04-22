// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Gym/Equipment/Dumbell_OM.h"
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
