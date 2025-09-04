// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/GMB/GymGameModeBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Character/Concrete/AbilitySystemComponent_OM.h"
#include "Game/Persistent/SubSystems/ConsumablesSubsystem.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTick_OM.h"
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

	Player->SwitchLevelTag(FGameplayTag::RequestGameplayTag("Level.Gym"));

	AbSysComp = Cast<UAbilitySystemComponent_OM>(Player->GetAbilitySystemComponent());

	InitializeConstantEffects();

	
	
}
void AGymGameModeBase_OM::InitializeConstantEffects()
{

}

