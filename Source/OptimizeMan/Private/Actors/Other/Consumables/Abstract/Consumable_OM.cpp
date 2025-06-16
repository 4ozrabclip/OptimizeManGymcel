// Copyright © 2025 4ozStudio. All rights reserved.



#include "Actors/Other/Consumables/Abstract/Consumable_OM.h"

#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Utils/Structs/AudioTypes.h"

AConsumable_OM::AConsumable_OM()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAudioType(EAudioTypes::SfxAudio);
	AudioComponent->bAutoActivate = true;
}

void AConsumable_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void AConsumable_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	GameInstance->AddConsumable(ConsumableType);
}


void AConsumable_OM::PlayConsumeSound()
{
	if (!AudioComponent) return;
	if (ConsumeSounds.Num() <= 0) return;

	const int RandIndex = FMath::RandRange(0, ConsumeSounds.Num() - 1);

	AudioComponent->SetSound(ConsumeSounds[RandIndex]);

	AudioComponent->Play();
	
}