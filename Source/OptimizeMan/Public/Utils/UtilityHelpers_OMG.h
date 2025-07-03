#pragma once

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OMG.h"
#include "Game/Persistent/GameInstance_OMG.h"
#include "Game/Persistent/SubSystems/TodoManagement_OMG.h"
#include "Kismet/GameplayStatics.h"


class GymcelUtils
{
public:
	static APlayerCharacter_OM* GetPlayer_Gymcel(const UObject* WorldContext)
	{
		return Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(WorldContext, 0));
	}
	static APlayerController_OMG* GetPC_Gymcel(const UObject* WorldContext)
	{
		return Cast<APlayerController_OMG>(UGameplayStatics::GetPlayerController(WorldContext, 0));
	}
	static UGameInstance_OMG* GetGameInstance_Gymcel(const UObject* WorldContext)
	{
		return Cast<UGameInstance_OMG>(UGameplayStatics::GetGameInstance(WorldContext));
	}
	static UTodoManagement_OMG* GetTodoManager_Gymcel(const UObject* WorldContext)
	{
		return Cast<UTodoManagement_OMG>(GetGameInstance_Gymcel(WorldContext)->GetSubsystem<UTodoManagement_OMG>());
	}
	
};
