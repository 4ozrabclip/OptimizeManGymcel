// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Audio/Concrete/PlayerAmbience_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Utils/Structs/AudioTypes.h"

UPlayerAmbience_OM::UPlayerAmbience_OM()
{
	AudioType = EAudioTypes::SfxAudio;
	Player = nullptr;
}


void UPlayerAmbience_OM::PlayAmbience(const bool bKeepPlaying)
{

	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	EPlayerEmotionalStates CurrentEmotionalState = EPlayerEmotionalStates::Cope;
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
	}

	TArray<USoundBase*>* AmbienceToUse = nullptr;

	switch (CurrentEmotionalState)
	{
	case EPlayerEmotionalStates::Doomer:
		AmbienceToUse = &DoomerEmotionAmbiences;
		break;
	case EPlayerEmotionalStates::Gigachad:
		AmbienceToUse = &GigaChadEmotionAmbiences;
		break;
	case EPlayerEmotionalStates::Grindset:
		AmbienceToUse = &GrindsetEmotionAmbiences;
		break;
	case EPlayerEmotionalStates::GoblinMode:
		AmbienceToUse = &GoblinEmotionAmbiences;
		break;
	case EPlayerEmotionalStates::Cope:
	default:
		return;
	}

	
	
	if (!AmbienceToUse || AmbienceToUse->Num() <= 0) return;

	const int RandomSongIndex = FMath::RandRange(0, AmbienceToUse->Num());
	
	
	if (!(*AmbienceToUse)[RandomSongIndex] || !AmbienceToUse->IsValidIndex(RandomSongIndex)) return;
	
	SetSound((*AmbienceToUse)[RandomSongIndex]);

	Play();

	if (bKeepPlaying)
		OnAudioFinished.AddDynamic(this, &UPlayerAmbience_OM::OnAmbienceSongFinished);
}

void UPlayerAmbience_OM::BeginPlay()
{
	Super::BeginPlay();
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());
}


void UPlayerAmbience_OM::OnAmbienceSongFinished()
{
	PlayAmbience();
}
