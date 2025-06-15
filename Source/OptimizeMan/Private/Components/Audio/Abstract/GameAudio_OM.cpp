// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Audio/Abstract/GameAudio_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Utils/Structs/AudioTypes.h"

UGameAudio_OM::UGameAudio_OM()
{
	AudioType = EAudioTypes::None;
	CurrentVolumeMultiplier = 1.f;

}
void UGameAudio_OM::BeginPlay()
{
	Super::BeginPlay();
	SetIsVirtualized(true);
	GetAndSetVolume();
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		GameInstance->OnAudioSettingsChanged.AddDynamic(this, &UGameAudio_OM::UpdateAudioSettings);
	}
}

void UGameAudio_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void UGameAudio_OM::GetAndSetVolume()
{
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		FGameSettings Settings = GameInstance->GetGameSettings();

		switch (AudioType)
		{
		case EAudioTypes::None:
			{
				UE_LOG(LogTemp, Warning, TEXT("Audio Type Not Set.  Please set in constructor"));
				return;
			}
		case EAudioTypes::VoiceAudio:
			{
				CurrentVolumeMultiplier = Settings.VoiceVolume * Settings.MasterVolume;
				break;
			}
		case EAudioTypes::MusicAudio:
			{
				CurrentVolumeMultiplier = Settings.MusicVolume * Settings.MasterVolume;
				break;
			}
		case EAudioTypes::SfxAudio:
			{
				CurrentVolumeMultiplier = Settings.SfxVolume * Settings.MasterVolume;
				break;
			}
		case EAudioTypes::NotificationAudio:
			{
				CurrentVolumeMultiplier = Settings.NotificationVolume * Settings.MasterVolume;
				break;
			}
		default:
			{
				break;
			}
		}
		SetVolumeMultiplier(CurrentVolumeMultiplier);
	}
	
}

void UGameAudio_OM::UpdateAudioSettings(const float InMasterVolume, const float InVoiceVolume,
	const float InMusicVolume, const float InNotificationVolume, const float InSfxVolume)
{
	UE_LOG(LogTemp, Display, TEXT("Update Audio Settings Changed"));

	OnAudioFinished.RemoveAll(this);

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

