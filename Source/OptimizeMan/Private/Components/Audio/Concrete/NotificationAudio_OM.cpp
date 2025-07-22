// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Audio/Concrete/NotificationAudio_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"
#include "Utils/Structs/AudioTypes.h"

UNotificationAudio_OM::UNotificationAudio_OM()
{
	TodoWritingSound = nullptr;
	TodoCompletedSound = nullptr;
	SplatSound = nullptr;
	AudioType = EAudioTypes::NotificationAudio;
	Player = nullptr;
}

void UNotificationAudio_OM::BeginPlay()
{
	Super::BeginPlay();
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(GetOwner());
	
	if (UGameInstance_OM* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		if (UTodoManagementSubsystem* TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>()))
		{
			TodoManager->OnTodoComplete.AddDynamic(this, &UNotificationAudio_OM::PlayTodoCompletedSound);
		}
	}
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

void UNotificationAudio_OM::PlayCrossingOutSound()
{
	if (!TodoCrossingOutSound)
	{
		UE_LOG(LogTemp, Error, TEXT("No writing sound"));
		return;
	}
	
	SetSound(TodoCrossingOutSound);
	if (IsPlaying()) Stop();

	Play();
	
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