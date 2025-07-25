// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/EquipmentRack_OM.h"

#include "Actors/Other/Gym/Abstract/ExerciseEquipment_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Game/Persistent/GameInstance_OM.h"

// Sets default values
AEquipmentRack_OM::AEquipmentRack_OM()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("Default"));
	
	Equipment = nullptr;
	

}

void AEquipmentRack_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEquipmentRack_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (!Player || !Player->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Player is invalid"));
		return;
	}
	if (!Equipment)
	{
		UE_LOG(LogTemp, Error, TEXT("Equipment is invalid"));
		return;
	}
	if (GameInstance && GameInstance->GetGymResStats().Energy > 0)
	{
		Player->SetCurrentPlayMode(EPlayModes::WorkoutMode, Equipment);
	}
}