// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/Player/PlayerControllerBase_OM.h"

#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Utils/Structs/AudioTypes.h"

APlayerControllerBase_OM::APlayerControllerBase_OM()
{
	UserInterfaceAudio = CreateDefaultSubobject<UGameAudio_OM>(TEXT("UI Audio"));
	UserInterfaceAudio->SetupAttachment(RootComponent);
	UserInterfaceAudio->SetAudioType(EAudioTypes::NotificationAudio);
	UserInterfaceAudio->bIsUISound = true;
}

void APlayerControllerBase_OM::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerControllerBase_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APlayerControllerBase_OM::PlayUISound(USoundBase* InSound) const
{
	if (!InSound) return;

	if (UserInterfaceAudio)
	{
		UserInterfaceAudio->SetSound(InSound);
		UserInterfaceAudio->Play();
	}
}
