// Copyright © 2025 4ozStudio. All rights reserved.

#include "Actors/Characters/NPC/Concrete/GymGuy1_OM.h"

AGymGuy1_OM::AGymGuy1_OM()
{
	CurrentMood = ENpcMood::Neutral;

	CurrentState = ENpcState::Idle;

	ExitDialogueState = ENpcState::Walking;
}

void AGymGuy1_OM::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(ENpcState::Walking);
}
