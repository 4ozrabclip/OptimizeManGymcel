// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GMB/GymGameModeBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Game/Persistent/SubSystems/ConsumablesSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "OptimizeMan/Public/Game/Persistent/GameInstance_OM.h"

AGymGameModeBase_OM::AGymGameModeBase_OM()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerController = nullptr;
	Player = nullptr;
	GameInstance = nullptr;
	ConsumableManager = nullptr;
}

void AGymGameModeBase_OM::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	if (!GetWorld()->IsGameWorld()) return;

	GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	if (GameInstance)
	{
		if (!GameInstance->GetHasBeenToGymToday())
		{
			GameInstance->SetHasBeenToGymToday(true);
		}
		
		FGymResStats& GymRes = GameInstance->GetGymResStats();

		GameInstance->AddGymResStats(GymRes.Bladder, 0.f);
		GameInstance->AddGymResStats(GymRes.Focus, 1.f);
		GameInstance->AddGymResStats(GymRes.Energy, 1.f);
	}


	PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GameInstance, 0));
	Player = Cast<APlayerCharacter_OM>(PlayerController->GetPawn());
	if (PlayerController && Player)
	{
		PlayerController->SetGymHud();
		SetActorTickEnabled(true);
	}
}



void AGymGameModeBase_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckGymStats(DeltaTime);
}

void AGymGameModeBase_OM::CheckIdleStats(float DeltaTime)
{
	//Decrease focus because your idle
	const float MaxTimeIdle = 5.f / GameInstance->GetDifficultyMultiplier();

	TimePassedSinceIdle += (DeltaTime / 2);
	
	if (TimePassedSinceIdle < MaxTimeIdle) return;
	
	FGymResStats& GymResStats = GameInstance->GetGymResStats();
	constexpr float DecreaseValue = -0.001f;

	
	if (GymResStats.Focus < 0.5f)
		GameInstance->AddGymResStats(GymResStats.Energy, DecreaseValue);


	GameInstance->AddGymResStats(GymResStats.Focus, DecreaseValue);
	

}

void AGymGameModeBase_OM::CheckGymStats(float DeltaTime)
{
	if (!ConsumableManager)
		ConsumableManager = Cast<UConsumablesSubsystem>(GameInstance->GetSubsystem<UConsumablesSubsystem>());

	FGymResStats& GymResStats = GameInstance->GetGymResStats();

	if (ConsumableManager)
	{
		for (int Index = ConsumableManager->GetCurrentConsumables().Num() - 1; Index >= 0; --Index)
		{
			FConsumableType& Consumable = ConsumableManager->GetCurrentConsumables()[Index];
			if (Consumable.LifeTime <= 0.f)
			{
				ConsumableManager->RemoveConsumable(Consumable);
				continue;
			}
			
			Consumable.LifeTime -= DeltaTime;
			for (TPair<EConsumableEffectTypes, int> Effect : Consumable.ConsumableEffects)
			{
				float BaseLineBladderIncrease = 0.00005f;
				switch (Effect.Key())
				{
				case EConsumableEffectTypes::Bladder:
					{
						if (GymResStats.Bladder > 0.35f && GymResStats.Bladder < 0.7f)
							BaseLineBladderIncrease *= 2;
						GameInstance->AddGymResStats(GymResStats.Bladder, BaseLineBladderIncrease * Effect.Value());
						break;
					}
				case EConsumableEffectTypes::Focus:
					{
						
						break;
					}
				case EConsumableEffectTypes::Energy:
					{
						break;
					}
				default:
					{
						break;
					}
				}
			}
		}
	}

	/*
	*	ConsumableType.NameString = FString("EnergyDrink");
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Bladder, 5);
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Energy, 5);
	ConsumableType.ConsumableEffects.Add(EConsumableEffectTypes::Focus, 3);
	ConsumableType.LifeTime = 60*3;
	ConsumableType.Price = 5;
	 * 
	 */
	
	switch (Player->GetCurrentPlayMode())
	{
	case EPlayModes::RegularMode: 
		{
			CheckIdleStats(DeltaTime);
			break;
		}
	default:
		{
			TimePassedSinceIdle = 0.f;
			break;
		}
	}
	if (PlayerController = Cast<APlayerController_OM>(Player->GetController()))
		PlayerController->UpdateGymHud();
	
}
