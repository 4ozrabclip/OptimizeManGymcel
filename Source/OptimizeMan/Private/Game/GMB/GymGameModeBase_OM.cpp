// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GMB/GymGameModeBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Character/Concrete/AbilitySystemComponent_OM.h"
#include "Game/Persistent/SubSystems/ConsumablesSubsystem.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTick_OM.h"
#include "Kismet/GameplayStatics.h"
#include "OptimizeMan/Public/Game/Persistent/GameInstance_OM.h"

AGymGameModeBase_OM::AGymGameModeBase_OM()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PlayerController = nullptr;
	Player = nullptr;
	GameInstance = nullptr;
	ConsumableManager = nullptr;
}
void AGymGameModeBase_OM::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

void AGymGameModeBase_OM::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	
	GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	if (GameInstance && !GameInstance->GetHasBeenToGymToday())
		GameInstance->SetHasBeenToGymToday(true);
	
	PlayerController = Cast<APlayerController_OM>(NewPlayer);
	if (!PlayerController) return;
	Player = Cast<APlayerCharacter_OM>(PlayerController->GetPawn());
	if (!Player) return;

	AbSysComp = Cast<UAbilitySystemComponent_OM>(Player->GetAbilitySystemComponent());
	if (!AbSysComp) return;
	MentalHealth = AbSysComp->GetSet<UMentalHealthStats_OM>();
	if (!MentalHealth) return;
	GymStats = AbSysComp->GetSet<UGymSpecificStats_OM>();
	if (!GymStats) return;

	PlayerController->SetGymHud();
	
}
void AGymGameModeBase_OM::InitializeConstantEffects()
{

}

/*
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
	
	float CurrentFocusDecrease = FocusDecreaseValue * (bFocusBoostActive ? FocusDecreaseSlowMultiplier : 1.0f);
	float CurrentEnergyDecrease = EnergyDecreaseValue * (bEnergyBoostActive ? EnergyDecreaseSlowMultiplier : 1.0f);
	
	if (GymResStats.Focus < 0.5f)
		AbSysComp->SetVal

	AbSysComp->SetFocus(CurrentFocusDecrease);
	
}

/*void AGymGameModeBase_OM::CheckGymStats(float DeltaTime)
{
	FGymResStats& GymResStats = GameInstance->GetGymResStats();

	bFocusBoostActive = false;
	bEnergyBoostActive = false;
	FocusDecreaseSlowMultiplier = 1.f;
	EnergyDecreaseSlowMultiplier = 1.f;

	if (ConsumableManager)
	{
		for (int Index = ConsumableManager->GetCurrentConsumables().Num() - 1; Index >= 0; --Index)
		{
			FConsumableType& Consumable = ConsumableManager->GetCurrentConsumables()[Index];
			Consumable.LifeTime -= DeltaTime;
			
			for (TPair<EConsumableEffectTypes, int> Effect : Consumable.ConsumableEffects)
			{
				float BaseLineBladderIncrease = 0.00005f;
				switch (Effect.Key)
				{
				case EConsumableEffectTypes::Bladder:
					{
						if (GymResStats.Bladder > 0.35f && GymResStats.Bladder < 0.7f)
							BaseLineBladderIncrease *= 2;
						
						AbSysComp->SetBladder(BaseLineBladderIncrease * Effect.Value);
						//GameInstance->AddGymResStats(GymResStats.Bladder, BaseLineBladderIncrease * Effect.Value);
						break;
					}
				case EConsumableEffectTypes::Focus:
					{
						bFocusBoostActive = true;
						FocusDecreaseSlowMultiplier = 0.2f; 
						break;
					}
				case EConsumableEffectTypes::Energy:
					{
						bEnergyBoostActive = true;
						EnergyDecreaseSlowMultiplier = 0.2f; 
						break;
					}
				default:
					{
						break;
					}
				}
			}
			if (Consumable.LifeTime <= 0.f)
			{
				ConsumableManager->RemoveConsumable(Consumable);
				continue;
			}
		}
	}
	
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
	if (!PlayerController)
		PlayerController = Cast<APlayerController_OM>(Player->GetController());
	if (PlayerController)
		PlayerController->UpdateGymHud();
}*/
