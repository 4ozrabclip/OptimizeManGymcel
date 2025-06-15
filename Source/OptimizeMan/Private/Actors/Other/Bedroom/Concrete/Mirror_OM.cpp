// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Other/Bedroom/Concrete/Mirror_OM.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Other/Bedroom/Concrete/Shelf_OM.h"
#include "Components/AudioComponent.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Widgets/Home/Concrete/MirrorWidget_OM.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Utils/Structs/AudioTypes.h"
#include "Widgets/Home/Concrete/MirrorWidget_OM.h"

AMirror_OM::AMirror_OM()
{
	ExtraCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtraCollider"));
	ExtraCollider->SetCollisionProfileName(TEXT("Default"));
	ExtraCollider->SetupAttachment(RootComponent);
	
	MirrorAudio = CreateDefaultSubobject<UGameAudio_OM>(TEXT("MirrorAudio"));
	MirrorAudio->bAutoActivate = true;
	MirrorAudio->SetAudioType(EAudioTypes::None);
	MirrorAudio->SetVolumeMultiplier(1.f);

	AuraLight->SetIntensity(1.f);
	AuraLight->SetAttenuationRadius(30.f);
	
}

void AMirror_OM::BeginPlay()
{
	Super::BeginPlay();
	SetInteractableWidgetText("Look Mirror");

	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
		UE_LOG(LogTemp, Error, TEXT("RECAST GAME INSTANCE IN mirror"));
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to recast in mirror"));
		return;
	}
}

void AMirror_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	}
	//Stick character in mirror position
	MirrorWidget = Cast<UMirrorWidget_OM>(PlayerController->GetMirrorWidget());
	Player->TogglePlayMode(EPlayModes::MirrorMode, Player->bInteractableOpen, this);
	
	//Player->SetCurrentPlayMode(EPlayModes::MirrorMode, this);
	
}

void AMirror_OM::UpdateStats() 
{
	if (!MirrorWidget)
	{
		return;
	}
	MirrorWidget->UpdateStats();
}

