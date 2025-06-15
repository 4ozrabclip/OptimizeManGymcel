// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Other/Bedroom/Concrete/Speaker_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Utils/Structs/AudioTypes.h"
#include "Widgets/Home/Concrete/SpeakerWidget_OM.h"

ASpeaker_OM::ASpeaker_OM()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = true;
	AudioComponent->SetAudioType(EAudioTypes::MusicAudio);
	ExtraCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtraCollider"));
	ExtraCollider->SetCollisionProfileName(TEXT("Default"));
	ExtraCollider->SetupAttachment(RootComponent);

	SpeakerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	SpeakerWidget->SetupAttachment(RootComponent);
	SpeakerWidget->SetVisibility(false);
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

	
	if (USpeakerWidget_OM* Widg = Cast<USpeakerWidget_OM>(SpeakerWidget->GetWidget()))
		Widg->InitSpeaker(this);
	
	SetActorTickEnabled(false);
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
	PlayerController->HideUnhideInteractableWidget(true);
	SpeakerWidget->SetVisibility(true);
	//InteractableInterfaceProperties.bIsInteractable = false;
	Player->SetToUIMode(true, true);
	
	if (Songs.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Songs is empty"));
		return;
	}
	
	SetActorTickEnabled(true);
	//PlayNextSong();
}

void ASpeaker_OM::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		FVector2D Delta = FVector2D(this->GetActorLocation()) - FVector2D(Player->GetActorLocation());
		
		if (Delta.Size() > 200)
		{
			TurnOffWidget();
		}
	}
}

void ASpeaker_OM::TurnOffWidget()
{
	SpeakerWidget->SetVisibility(false);
	//InteractableInterfaceProperties.bIsInteractable = true;
	Player->SetToUIMode(false);
	PlayerController->HideUnhideInteractableWidget(false);
	SetActorTickEnabled(false);
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
		}, 1.f, false);
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

void ASpeaker_OM::StopSong()
{
	if (!bIsPlaying) return;

	AudioComponent->Stop();

	bIsPlaying = false;
}
