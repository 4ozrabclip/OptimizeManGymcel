// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/Persistent/SubSystems/ConsumablesSubsystem.h"

void UConsumablesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UConsumablesSubsystem::AddConsumable(const FConsumableType& InConsumable)
{
	CurrentConsumables.Add(InConsumable);

	OnConsumableAdded.Broadcast(InConsumable);
}

void UConsumablesSubsystem::RemoveConsumable(const FConsumableType& InConsumable)
{
	if (CurrentConsumables.Contains(InConsumable))
	{
		CurrentConsumables.Remove(InConsumable);
	}
}
