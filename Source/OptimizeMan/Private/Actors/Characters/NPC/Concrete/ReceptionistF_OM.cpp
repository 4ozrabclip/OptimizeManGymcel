// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Characters/NPC/Concrete/ReceptionistF_OM.h"

AReceptionistF_OM::AReceptionistF_OM()
{
	CurrentMood = ENpcMood::Neutral;
	CurrentState = ENpcState::Idle;
}
