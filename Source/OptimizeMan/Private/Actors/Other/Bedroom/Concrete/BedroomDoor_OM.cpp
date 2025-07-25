// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Bedroom/Concrete/BedroomDoor_OM.h"

#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GMB/BedroomGameModeBase_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

ABedroomDoor_OM::ABedroomDoor_OM()
{
	LevelToLoad = "/Game/Levels/Gym";
}

void ABedroomDoor_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	ABedroomGameModeBase_OM* BedroomGameMode = Cast<ABedroomGameModeBase_OM>(UGameplayStatics::GetGameMode(this));
	if (!BedroomGameMode)
		return;
	if (BedroomGameMode->GetWidgetIsVisible()) return;
	
	if (TodoManager && TodoManager->CurrentTodoListContainsLayer(FString("Bedroom")) && !bWantsToContinue)
	{
		FString IncompleteBedroomWarning = FString("Are you sure you want to exit the bedroom?  You have an incomplete todo which can only be achieved in room");


		PlayerController->ShowOrHideHint(IncompleteBedroomWarning, 2.f);
		


		bWantsToContinue = true;
		return;
	}

	ClearTimers();

	OpenDoor();
}
