// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Player/Components/NotificationAudio_OM.h"

#include "Utils/Structs/AudioTypes.h"

UNotificationAudio_OM::UNotificationAudio_OM()
{
	TodoWritingSound = nullptr;
	TodoCompletedSound = nullptr;
	SplatSound = nullptr;
	AudioType = EAudioTypes::NotificationAudio;
}

void UNotificationAudio_OM::PlayWritingSound()
{
	if (!TodoWritingSound)
	{
		UE_LOG(LogTemp, Error, TEXT("No writing sound"));
		return;
	}
	
	SetSound(TodoWritingSound);
	if (!IsPlaying())
	{
		Play();
	}
}
void UNotificationAudio_OM::PlaySplatSound()
{
	if (!SplatSound)
	{
		UE_LOG(LogTemp, Error, TEXT("No Splat Sound"));
		return;
	}

	SetSound(SplatSound);
	if (!IsPlaying())
	{
		Play();
	}
	else
	{
		Stop();
		Play();
	}
}

void UNotificationAudio_OM::PlayTodoCompletedSound()
{
	if (!TodoCompletedSound)
	{
		UE_LOG(LogTemp, Error, TEXT("No TodoCompleted sound"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Todo Complete sound ready"));
	SetSound(TodoCompletedSound);
	UE_LOG(LogTemp, Display, TEXT("Todo Complete sound set"));
	if (!IsPlaying())
	{
		Play();
		UE_LOG(LogTemp, Display, TEXT("Todo Complete sound played"));
	}
}