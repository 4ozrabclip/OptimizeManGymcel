// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Audio/Concrete/PlayerVoiceAudio_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Utils/Structs/AudioTypes.h"
#include "Utils/Structs/PlayerData.h"


UPlayerVoiceAudio_OM::UPlayerVoiceAudio_OM()
{
	AudioType = EAudioTypes::VoiceAudio;
	Player = nullptr;
}

void UPlayerVoiceAudio_OM::BeginPlay()
{
	Super::BeginPlay();

	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());
	
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());


	PlayBreathingInterval();

	MinPitchOffset = 0.02f;
	MaxPitchOffset = 0.02f;

	OnAudioFinished.AddDynamic(this, &UPlayerVoiceAudio_OM::PlayBreathingInterval);
	
}

void UPlayerVoiceAudio_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	GetWorld()->GetTimerManager().ClearTimer(BreathingTimerHandle);
}

void UPlayerVoiceAudio_OM::Play(float StartTime)
{

	Super::Play(StartTime);
}

void UPlayerVoiceAudio_OM::PlayBreathingSound()
{
	if (IsPlaying()) return;
	TArray<USoundBase*>* BreathingArray = nullptr;
	const int RandIndex = FMath::RandRange(0, BreathingSounds_Soft.Num() - 1);

	BreathingArray = CurrentBreathingIntensity == EBreathingIntensity::Soft ? &BreathingSounds_Soft :
					 CurrentBreathingIntensity == EBreathingIntensity::Normal ? &BreathingSounds_Normal : &BreathingSounds_Intense;
	
	if (BreathingArray && BreathingArray->IsValidIndex(RandIndex) && (*BreathingArray)[RandIndex]->IsValidLowLevel())
	{
		SetSound((*BreathingArray)[RandIndex]);
		SetVolumeMultiplier(FMath::RandRange(VolumeMultiplier - MinVolumeOffset, VolumeMultiplier + MaxVolumeOffset));
		SetPitchMultiplier(FMath::RandRange(PitchMultiplier - MinPitchOffset, PitchMultiplier + MaxPitchOffset));
		Play();
		OnBreathTaken.Broadcast(CurrentBreathingIntensity);
	}
}

void UPlayerVoiceAudio_OM::PlayBreathingInterval()
{
	GetWorld()->GetTimerManager().ClearTimer(BreathingTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(BreathingTimerHandle, [this]()
	{
		PlayBreathingSound();
	}, BreathingTimerInterval, true);
}

void UPlayerVoiceAudio_OM::InjurySoundEffects(const EExerciseType CurrentExerciseType)
{
	if (MajorInjurySounds.Num() <= 0 || MajorInjurySounds_Intense.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NOT ENOUGH MAJOR INJURY SOUNDs"));
		return;
	}

	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());
	
	EPlayerEmotionalStates CurrentEmotionalState = EPlayerEmotionalStates::Cope;
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
	}
	TArray<USoundBase*>* SoundsToUse;

	switch (CurrentEmotionalState)
	{
	case EPlayerEmotionalStates::Cope:
	case EPlayerEmotionalStates::Gigachad:
	case EPlayerEmotionalStates::Grindset:
		SoundsToUse = &MajorInjurySounds;
		break;
	case EPlayerEmotionalStates::Doomer:
	case EPlayerEmotionalStates::GoblinMode:
		SoundsToUse = &MajorInjurySounds_Intense;
		break;
	default:
		SoundsToUse = &MajorInjurySounds;
		break;
	}
	SetVolumeMultiplier(FMath::RandRange(VolumeMultiplier - MinVolumeOffset, VolumeMultiplier + MaxVolumeOffset));
	SetPitchMultiplier(FMath::RandRange(PitchMultiplier - MinPitchOffset, PitchMultiplier + MaxPitchOffset));
	const int SoundToUseRandIndex = FMath::RandRange(0, SoundsToUse->Num() - 1);
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		break;
	default:
		if (!SoundsToUse->IsValidIndex(SoundToUseRandIndex)) return;
		SetSound((*SoundsToUse)[SoundToUseRandIndex]);
		Play();
		break;
	}
}

void UPlayerVoiceAudio_OM::MinorInjurySoundEffects(const EExerciseType CurrentExerciseType)
{
	if (MinorInjurySounds.Num() <= 0 || MinorInjurySounds_Intense.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NOT ENOUGH MINOR INJURY SOUNDS"));
		return;
	}

	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());

	EPlayerEmotionalStates CurrentEmotionalState = EPlayerEmotionalStates::Cope;
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
	}
	TArray<USoundBase*>* SoundsToUse;

	switch (CurrentEmotionalState)
	{
	case EPlayerEmotionalStates::Cope:
	case EPlayerEmotionalStates::Gigachad:
	case EPlayerEmotionalStates::Grindset:
		SoundsToUse = &MinorInjurySounds;
		break;
	case EPlayerEmotionalStates::Doomer:
	case EPlayerEmotionalStates::GoblinMode:
		SoundsToUse = &MinorInjurySounds_Intense;
		break;
	default:
		SoundsToUse = &MinorInjurySounds;
		break;
	}
	SetVolumeMultiplier(FMath::RandRange(VolumeMultiplier - MinVolumeOffset, VolumeMultiplier + MaxVolumeOffset));
	SetPitchMultiplier(FMath::RandRange(PitchMultiplier - MinPitchOffset, PitchMultiplier + MaxPitchOffset));
	const int SoundToUseRandIndex = FMath::RandRange(0, SoundsToUse->Num() - 1);
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		break;
	default:
		if (!SoundsToUse->IsValidIndex(SoundToUseRandIndex)) return;
		SetSound((*SoundsToUse)[SoundToUseRandIndex]);
		Play();
		break;
	}
}

void UPlayerVoiceAudio_OM::WorkoutGruntSoundEffects(const EExerciseType CurrentExerciseType)
{
	if (FunnyGruntSounds.Num() <= 0 || FunnyGruntSounds_Intense.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NOT ENOUGH GRUNT SOUUNDS"))
		return;
	}

	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());

	EPlayerEmotionalStates CurrentEmotionalState = EPlayerEmotionalStates::Cope;
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
	}
	TArray<USoundBase*>* SoundsToUse;

	switch (CurrentEmotionalState)
	{
	case EPlayerEmotionalStates::Cope:
	case EPlayerEmotionalStates::Gigachad:
	case EPlayerEmotionalStates::Grindset:
		SoundsToUse = &FunnyGruntSounds;
		break;
	case EPlayerEmotionalStates::Doomer:
	case EPlayerEmotionalStates::GoblinMode:
		SoundsToUse = &FunnyGruntSounds_Intense;
		break;
	default:
		SoundsToUse = &FunnyGruntSounds;
		break;
	}
    
	const int SoundToUseRandIndex = FMath::RandRange(0, SoundsToUse->Num() - 1);

	SetVolumeMultiplier(FMath::RandRange(VolumeMultiplier - MinVolumeOffset, VolumeMultiplier + MaxVolumeOffset));
	SetPitchMultiplier(FMath::RandRange(PitchMultiplier - MinPitchOffset, PitchMultiplier + MaxPitchOffset));
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		break;
	default:
		if (!SoundsToUse->IsValidIndex(SoundToUseRandIndex)) return;
		SetSound((*SoundsToUse)[SoundToUseRandIndex]);
		Play();
		break;
	}
}
void UPlayerVoiceAudio_OM::UpsetSoundEffects()
{
	if (UpsetSounds.Num() == 0 || UpsetSounds_Doomer.Num() == 0 || UpsetSounds_Goblin.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NOT ENOUGH UPSET SOUNDS"));
		return;
	}

	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());

	EPlayerEmotionalStates CurrentEmotionalState = EPlayerEmotionalStates::Cope;
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
	}
	TArray<USoundBase*>* SoundsToUse;

	switch (CurrentEmotionalState)
	{
	case EPlayerEmotionalStates::Doomer:
		SoundsToUse = &UpsetSounds_Doomer;
		break;
	case EPlayerEmotionalStates::GoblinMode:
		SoundsToUse = &UpsetSounds_Goblin;
		break;
	default:
		SoundsToUse = &UpsetSounds;
		break;
	}
	SetVolumeMultiplier(FMath::RandRange(VolumeMultiplier - MinVolumeOffset, VolumeMultiplier + MaxVolumeOffset));
	SetPitchMultiplier(FMath::RandRange(PitchMultiplier - MinPitchOffset, PitchMultiplier + MaxPitchOffset));
	const int SoundToUseRandIndex = FMath::RandRange(0, SoundsToUse->Num() - 1);
	if (!SoundsToUse->IsValidIndex(SoundToUseRandIndex)) return;
    
	SetSound((*SoundsToUse)[SoundToUseRandIndex]);
	Play();
}
void UPlayerVoiceAudio_OM::GrumpySoundEffects()
{
	if (GrumpySounds.Num() <= 0 || GrumpySounds_Intense.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NOT ENOUGH GRUMPY SOUNDS"));
		return;
	}


	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());


	if (IsPlaying())
	{
		Stop();
	}

	EPlayerEmotionalStates CurrentEmotionalState = EPlayerEmotionalStates::Cope;
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
	}
	TArray<USoundBase*>* SoundsToUse;

	switch (CurrentEmotionalState)
	{
	case EPlayerEmotionalStates::Cope:
	case EPlayerEmotionalStates::Gigachad:
	case EPlayerEmotionalStates::Grindset:
		SoundsToUse = &GrumpySounds;
		break;
	case EPlayerEmotionalStates::Doomer:
	case EPlayerEmotionalStates::GoblinMode:
		SoundsToUse = &GrumpySounds_Intense;
		break;
	default:
		SoundsToUse = &GrumpySounds;
		break;
	}
    
	const int SoundToUseRandIndex = FMath::RandRange(0, SoundsToUse->Num() - 1);
	if (!SoundsToUse->IsValidIndex(SoundToUseRandIndex)) return;
	SetVolumeMultiplier(FMath::RandRange(VolumeMultiplier - MinVolumeOffset, VolumeMultiplier + MaxVolumeOffset));
	SetPitchMultiplier(FMath::RandRange(PitchMultiplier - MinPitchOffset, PitchMultiplier + MaxPitchOffset));
	SetSound((*SoundsToUse)[SoundToUseRandIndex]);
	Play();
	UE_LOG(LogTemp, Error, TEXT("Grumpy Sound played"));
}
