// Fill out your copyright notice in the Description page of Project Settings.


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
    
	const int SoundToUseRandIndex = FMath::RandRange(0, SoundsToUse->Num() - 1);
	if (!SoundsToUse->IsValidIndex(SoundToUseRandIndex)) return;
    
	SetSound((*SoundsToUse)[SoundToUseRandIndex]);
	Play();
}
void UPlayerVoiceAudio_OM::GrumpySoundEffects()
{
	if (IsPlaying()) return;

	if (GrumpySounds.Num() <= 0 || GrumpySounds_Intense.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NOT ENOUGH GRUMPY SOUNDS"));
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
    
	SetSound((*SoundsToUse)[SoundToUseRandIndex]);
	Play();
	UE_LOG(LogTemp, Error, TEXT("Grumpy Sound played"));
}
