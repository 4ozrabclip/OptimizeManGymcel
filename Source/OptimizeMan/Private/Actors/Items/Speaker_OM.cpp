// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Speaker_OM.h"

#include "Audio/GameAudio_OM.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Utils/GameInstance_OM.h"
#include "Utils/Structs/AudioTypes.h"

ASpeaker_OM::ASpeaker_OM()
{
	AudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = true;
	AudioComponent->SetAudioType(EAudioTypes::MusicAudio);
	ExtraCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtraCollider"));
	ExtraCollider->SetCollisionProfileName(TEXT("Default"));
	ExtraCollider->SetupAttachment(RootComponent);
}

void ASpeaker_OM::BeginPlay()
{
	Super::BeginPlay();
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
		UE_LOG(LogTemp, Error, TEXT("RECAST GAME INSTANCE IN speaker"));
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to recast in speaker"));
		return;
	}
	
	SongIndex = Songs.Num();
}

void ASpeaker_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: AudioComponent is invalid"), *GetName());
		return;
	}
	if (Songs.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Songs is empty"));
		return;
	}
	PlayNextSong();
}

void ASpeaker_OM::PlayNextSong()
{
	SongIndex = (SongIndex + 1) % Songs.Num();
	
	/*
	if (SongIndex >= Songs.Num() - 1)
	{
		SongIndex = 0;
	}
	else
	{
		SongIndex++;
	}
	*/
	
	if (!Songs.IsValidIndex(SongIndex) || !Songs[SongIndex])
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid song at index %d"), SongIndex);
		return;
	}

	if (ClickingSound)
	{
		AudioComponent->SetSound(ClickingSound);
		AudioComponent->SetVolumeMultiplier(Volume);
		AudioComponent->Play();

		GetWorld()->GetTimerManager().ClearTimer(SongTransitionTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(SongTransitionTimerHandle, [this]()
		{
			PlaySong();
		}, 2.f, false);
	}
}

void ASpeaker_OM::PlaySong()
{
	if (!Songs.IsValidIndex(SongIndex) || !Songs[SongIndex])
	{
		return;
	}
    AudioComponent->SetSound(Songs[SongIndex]);
	AudioComponent->SetVolumeMultiplier(Volume);
	AudioComponent->Play();
	bIsPlaying = true;
}
