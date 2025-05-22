// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GymGameModeBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Kismet/GameplayStatics.h"
#include "OptimizeMan/Public/Utils/GameInstance_OM.h"

AGymGameModeBase_OM::AGymGameModeBase_OM()
{
	GameInstance = nullptr;
	Player = nullptr;
	PrimaryActorTick.bCanEverTick = true;
}

void AGymGameModeBase_OM::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	GameInstance = Cast<UGameInstance_OM>(GetGameInstance());

	if (GameInstance && !GameInstance->GetHasBeenToGymToday())
	{
		GameInstance->SetHasBeenToGymToday(true);
	}

	FPlayerData& PlayerData = GameInstance->GetPlayerData();

	PlayerData.SetStat(PlayerData.Bladder, 0.f);
	PlayerData.SetStat(PlayerData.Focus, 1.f);
	PlayerData.SetStat(PlayerData.Energy, 1.f);
	
	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->SetGymHud();
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
	constexpr float MaxTimeIdle = 5.f;

	TimePassedSinceIdle += (DeltaTime / 2);
	
	if (TimePassedSinceIdle < MaxTimeIdle) return;
	
	FPlayerData& PlayerData = GameInstance->GetPlayerData();
	constexpr float DecreaseValue = -0.001f;

	
	if (PlayerData.Focus < 0.5f)
		PlayerData.AddStat(PlayerData.Energy, DecreaseValue);

	
	PlayerData.AddStat(PlayerData.Focus, DecreaseValue);

	
	if (Player)
	{
		Player->UpdateGymHud();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Null in gym gm tick"));
	}

	

}
void AGymGameModeBase_OM::CheckGymStats(float DeltaTime)
{
	FPlayerData& PlayerData = GameInstance->GetPlayerData();

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
}
