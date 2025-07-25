// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/GymDoor_OM.h"

#include "Actors/Other/Gym/Concrete/GymGate_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Game/GMB/GymGameModeBase_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

AGymDoor_OM::AGymDoor_OM()
{
	LevelToLoad = "/Game/Levels/Home";
}

void AGymDoor_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (!Cast<AGymGameModeBase_OM>(GetWorld()->GetAuthGameMode()))
		return;
	
	if (TodoManager && TodoManager->CurrentTodoListContainsLayer(FString("Gym")) && !bWantsToContinue)
	{
		FString IncompleteGymWarning = FString("Are you sure you want to exit the Gym?  You have an incomplete todo which can only be achieved here");


			PlayerController->ShowOrHideHint(IncompleteGymWarning, 2.f);
		

		bWantsToContinue = true;
		return;
	}

	ClearTimers();
	
	OpenDoor();
}

void AGymDoor_OM::ClearTimers()
{
	Super::ClearTimers();
	if (AGymGate_OM* GymGate = Cast<AGymGate_OM>(UGameplayStatics::GetActorOfClass(GetWorld(), AGymGate_OM::StaticClass())))
	{
		// Add this function to your GymGate class to expose timer clearing
		GymGate->ClearGateTimer();
	}
}
