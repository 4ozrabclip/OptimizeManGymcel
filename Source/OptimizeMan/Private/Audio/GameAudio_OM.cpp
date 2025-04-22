// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/GameAudio_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "AnimNodes/AnimNode_RandomPlayer.h"
#include "Utils/GameInstance_OM.h"
#include "Utils/Structs/AudioTypes.h"

UGameAudio_OM::UGameAudio_OM()
{
	Player = nullptr;
	AudioType = EAudioTypes::None;
	CurrentVolumeMultiplier = 1.f;
}
void UGameAudio_OM::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerCharacter_OM>(GetOwner());

	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		GameInstance->OnAudioSettingsChanged.AddDynamic(this, &UGameAudio_OM::UpdateAudioSettings);
	}
}

void UGameAudio_OM::UpdateAudioSettings(const float InMasterVolume, const float InVoiceVolume,
	const float InMusicVolume, const float InNotificationVolume, const float InSfxVolume)
{
	UE_LOG(LogTemp, Display, TEXT("Update Audio Settings Changed"));

	switch (AudioType)
	{
	case EAudioTypes::None:
		{
			UE_LOG(LogTemp, Warning, TEXT("Audio Type Not Set.  Please set in constructor"));
			return;
		}
	case EAudioTypes::VoiceAudio:
		{
			CurrentVolumeMultiplier = InVoiceVolume * InMasterVolume;
			break;
		}
	case EAudioTypes::MusicAudio:
		{
			CurrentVolumeMultiplier = InMusicVolume * InMasterVolume;
			break;
		}
	case EAudioTypes::SfxAudio:
		{
			CurrentVolumeMultiplier = InSfxVolume * InMasterVolume;
			break;
		}
	case EAudioTypes::NotificationAudio:
		{
			CurrentVolumeMultiplier = InNotificationVolume * InMasterVolume;
			break;
		}
	default:
		{
			break;
		}
	}
	SetVolumeMultiplier(CurrentVolumeMultiplier);
}

