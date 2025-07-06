// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Other/Bedroom/Concrete/Shelf_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/PointLightComponent.h"
#include "Utils/UtilityHelpers_OMG.h"

AShelf_OM::AShelf_OM()
{
	SteroidsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Steroids"));
	SteroidsMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SteroidsMesh->SetVisibility(false);
	SteroidsMesh->SetupAttachment(RootComponent);

	PreWorkoutMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreWorkout"));
	PreWorkoutMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PreWorkoutMesh->SetVisibility(false);
	PreWorkoutMesh->SetupAttachment(RootComponent);

	
}



void AShelf_OM::BeginPlay()
{
	Super::BeginPlay();
	
	AuraLight->SetVisibility(false);

	UpdateShelfItems();
	
}

void AShelf_OM::UpdateShelfItems() const
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No game instance in shelf"));
		return;
	}
	const FInventoryData& Inventory = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetInventoryData();
	if (Inventory.bOwnsSteroids)
	{
		SteroidsMesh->SetVisibility(true);
	}
	else
	{
		SteroidsMesh->SetVisibility(false);
	}
	if (Inventory.bOwnsPreWorkout)
	{
		PreWorkoutMesh->SetVisibility(true);
	}
	else
	{
		PreWorkoutMesh->SetVisibility(false);
	}
}

void AShelf_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No player"));
		return;
	}
	
	GymcelUtils::GetPlayer_Gymcel(GetWorld())->TogglePlayMode(EPlayModes::ShelfMode, Player->GetInteractableOpen(), this);
	//Player->SetCurrentPlayMode(EPlayModes::ShelfMode, this);
}
