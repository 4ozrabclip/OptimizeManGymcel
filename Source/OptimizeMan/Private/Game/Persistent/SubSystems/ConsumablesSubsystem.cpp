// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/Persistent/SubSystems/ConsumablesSubsystem.h"

#include "Game/GMB/GymGameModeBase_OM.h"
#include "Game/Persistent/GameInstance_OM.h"

void UConsumablesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UConsumablesSubsystem::AddConsumable(const FConsumableType& InConsumable)
{
	CurrentConsumables.Add(InConsumable);

	OnConsumableAdded.Broadcast(InConsumable);

	
	if (GetWorld()->GetAuthGameMode()->IsA<AGymGameModeBase_OM>)
	{
		UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
		FGymResStats& GymResStats = GameInstance->GetGymResStats();
	
		for (TPair<EConsumableEffectTypes, float> InstantEffect : InConsumable.ConsumableEffects)
		{
			const float BoostValue = InstantEffect.Value / 10.f;
			switch (InstantEffect.Key)
			{
			case EConsumableEffectTypes::Focus:
				GameInstance->AddGymResStats(GymResStats.Focus, BoostValue);
				break;
			case EConsumableEffectTypes::Energy:
				GameInstance->AddGymResStats(GymResStats.Energy, BoostValue);
				break;
			default:
				break;
			}
		}
	}

}

void UConsumablesSubsystem::RemoveConsumable(const FConsumableType& InConsumable)
{
	if (CurrentConsumables.Contains(InConsumable))
	{
		CurrentConsumables.Remove(InConsumable);
	}
}
