// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Characters/NPC/Concrete/GymGuy1_OM.h"

#include "Actors/Characters/NPC/Abstract/NpcBase_OMG.h"

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
