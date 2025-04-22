// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Player/Components/FootstepAudio_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Utils/Structs/AudioTypes.h"

UFootstepAudio_OM::UFootstepAudio_OM()
{
	bInitialFootstep = false;
	FootstepIndex = 0;
	FootstepInterval = 0.65f;
	TimeSinceLastFootstep = 0.f;
	AudioType = EAudioTypes::SfxAudio;
}

void UFootstepAudio_OM::Footsteps(float DeltaTime)
{
	if (Player->GetIsWalking())
	{
		TimeSinceLastFootstep += DeltaTime;
		if (TimeSinceLastFootstep >= FootstepInterval)
		{
			PlayFootstepSound();
			TimeSinceLastFootstep = 0.f;
		}
	}
	else
	{
		TimeSinceLastFootstep = FootstepInterval;
	}
}

void UFootstepAudio_OM::PlayFootstepSound()
{
	if (FootstepSounds.Num() <= 0)
	{
		UE_LOG(LogTemp, Display, TEXT("No FootstepSounds Found"));
		return;
	}
	constexpr int MaxFootstepIndex = 3;
	if (bInitialFootstep)
	{
		if (FootstepIndex < MaxFootstepIndex)
		{
			FootstepIndex++;
		}
		else
		{
			FootstepIndex = 0;
		}
	}
	else
	{
		FootstepIndex = 0;
		bInitialFootstep = true;	
	}

	if (FootstepSounds.IsValidIndex(FootstepIndex) && FootstepSounds[FootstepIndex])
	{
		SetSound(FootstepSounds[FootstepIndex]);
		if (!IsPlaying())
		{
			Play();
		}
	}
}
