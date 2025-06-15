// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/NPC/Abstract/MaleBase_OM.h"

#include "Components/Audio/Abstract/GameAudio_OM.h"

/*void AMaleBase_OM::PlayRandomTalkingSound(TArray<USoundBase*>& InSounds)
{
	if (InSounds.Num() <= 0) return;

	const int RandomIndex = FMath::RandRange(0, InSounds.Num() - 1);

	if (TalkingAudioComponent->IsPlaying())
	{
		TalkingAudioComponent->Stop();
	}

	if (InSounds.IsValidIndex(RandomIndex))
	{
		TalkingAudioComponent->SetSound(InSounds[RandomIndex]);
	}
	TalkingAudioComponent->Play();
}
*/