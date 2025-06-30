// Fill out your copyright notice in the Description page of Project Settings.



#include "Characters/NpcBase_OM.h"

#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"



#include "Components/Audio/Abstract/GameAudio_OM.h"

#include "GameFramework/CharacterMovementComponent.h"


ANpcBase_OM::ANpcBase_OM()
{
	PrimaryActorTick.bCanEverTick = true;

	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));


}
