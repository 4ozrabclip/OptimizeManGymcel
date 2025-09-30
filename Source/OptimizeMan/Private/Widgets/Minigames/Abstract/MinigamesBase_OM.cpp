// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Minigames/Abstract/MinigamesBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Character/Concrete/Exercise_OM.h"

void UMinigamesBase_OM::NativeConstruct()
{
	Super::NativeConstruct();
	if (!PlayerController)
	{	
		PlayerController = Cast<APlayerController_OM>(GetOwningPlayer());
	}
	if (!Player && PlayerController)
	{
		Player = Cast<APlayerCharacter_OM>(PlayerController->GetPawn());
	}

	if (Player)
	{
		if (auto* ExerciseComponent = Player->GetComponentByClass<UExercise_OM>())
		{
			OnMinigameResult.AddDynamic(ExerciseComponent, &UExercise_OM::MiniGame);
		}
	}
}
