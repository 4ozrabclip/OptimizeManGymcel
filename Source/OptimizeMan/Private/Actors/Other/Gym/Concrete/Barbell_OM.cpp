// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Other/Gym/Concrete/Barbell_OM.h"

#include "Components/BoxComponent.h"

ABarbell_OM::ABarbell_OM()
{
	ExtraCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtraCollider"));
	ExtraCollider->SetCollisionProfileName(TEXT("Default"));
	ExtraCollider->SetupAttachment(RootComponent);
}

void ABarbell_OM::BeginPlay()
{
	Super::BeginPlay();
	SetInteractableWidgetText("Lift Weight");
}


void ABarbell_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
}
