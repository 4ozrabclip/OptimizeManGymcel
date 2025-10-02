// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/Toilet_OM.h"

#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Structs/AudioTypes.h"


AToilet_OM::AToilet_OM()
{
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAudioType(EAudioTypes::SfxAudio);
	
}

void AToilet_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void AToilet_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (!PlayerController)
		PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	PlayerController->GetWidgetManagementComponent()->ToggleInteractWidgetFromViewport(true);
	InteractableInterfaceProperties.bIsInteractable = false;
	
	const int PissLength = PlayPissingSound();
	
	PlayerController->SetCinematicMode(true, true, true);

	GetWorld()->GetTimerManager().ClearTimer(ToiletTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(ToiletTimerHandle, [this]()
	{
		PlayerController->SetCinematicMode(false, true, true);
		PlayerController->GetWidgetManagementComponent()->ToggleInteractWidgetFromViewport(false);
		InteractableInterfaceProperties.bIsInteractable = true;
		ResetBladder();
		
	}, PissLength, false);


	
}

void AToilet_OM::ResetBladder()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	float& Bladder = GameInstance->GetGymResStats().Bladder;
	
	GameInstance->SetGymResStats(Bladder, 0.f);
	
}


void AToilet_OM::PlaySound(USoundBase* InSound)
{
	if (!AudioComponent) return;

	if (!InSound) return;

	AudioComponent->SetSound(InSound);

	AudioComponent->Play();
}

int AToilet_OM::PlayPissingSound()
{
	if (PissingSounds.Num() <= 0) return 10;

	int RandIndex = FMath::RandRange(0, PissingSounds.Num() - 1);

	size_t IndexCount = 0;
	for (const TPair<int, USoundBase*>& PissSound : PissingSounds)
	{
		if (IndexCount == RandIndex)
		{
			if (PissSound.Value)
				PlaySound(PissSound.Value);
			return PissSound.Key;
		}
		IndexCount++;
	}

	return 10;
}
