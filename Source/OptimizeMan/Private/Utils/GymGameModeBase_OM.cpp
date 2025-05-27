// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GymGameModeBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
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


	
	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (APlayerController_OM* PlayerController = Cast<APlayerController_OM>(Player->GetController()))
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

	
	if (APlayerController_OM* PlayerController = Cast<APlayerController_OM>(Player->GetController()))
	{
		PlayerController->UpdateGymHud();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Null in gym gm tick"));
	}

	

}
void AGymGameModeBase_OM::CheckGymStats(float DeltaTime)
{
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
