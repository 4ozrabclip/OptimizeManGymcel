// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Abstract/Consumable_OM.h"

#include "Game/Persistent/GameInstance_OM.h"

AConsumable_OM::AConsumable_OM()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AConsumable_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void AConsumable_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	GameInstance->AddConsumable(ConsumableType);
}

