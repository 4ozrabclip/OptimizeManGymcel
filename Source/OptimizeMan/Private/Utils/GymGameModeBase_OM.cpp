// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GymGameModeBase_OM.h"
#include "OptimizeMan/Public/Utils/GameInstance_OM.h"

AGymGameModeBase_OM::AGymGameModeBase_OM()
{
	GameInstance = nullptr;
}

void AGymGameModeBase_OM::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UGameInstance_OM>(GetGameInstance());

	if (GameInstance && !GameInstance->GetHasBeenToGymToday())
	{
		GameInstance->SetHasBeenToGymToday(true);
	}


}
