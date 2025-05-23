// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Items/Gym/GymDoor_OM.h"

#include "Actors/Items/Gym/GymGate_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/GameInstance_OM.h"
#include "Utils/GymGameModeBase_OM.h"
#include "Utils/TodoManagementSubsystem.h"

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
