// Copyright © 2025 4ozStudio. All rights reserved.

#include "Actors/Other/Both/Abstract/Door.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/PointLightComponent.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"
#include "Kismet/GameplayStatics.h"


ADoor::ADoor()
{
	SetHasOpenedDoor(false);
	AuraLight->SetVisibility(false);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}


void ADoor::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (bHasOpenedDoor) return;
	if (LevelToLoad.IsEmpty()) return;
	if (!TodoManager)
	{
		TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	}
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	Player->SyncStatsToGameInstance();
	
}

void ADoor::ClearTimers()
{
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->ClearTimers();
}

void ADoor::OpenDoor()
{
	SetHasOpenedDoor(true);

	Player->SetMaxMovementSpeed(0.f);
	
	if (APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager)
	{
		constexpr float FadeDuration = 2.f;
		CameraManager->StartCameraFade(0.f, 1.f, FadeDuration, FLinearColor::Black, true, true);

		const FName LevelToChangeTo = FName(LevelToLoad);

		if (TimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		
		DoorOpenDelay(LevelToChangeTo, FadeDuration, [this]()
		{
			SetHasOpenedDoor(false);
		});
		
	}
}

void ADoor::DoorOpenDelay(FName LevelToChangeTo, const float FadeDuration, TFunction<void()> Cleanup)
{
	GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			[this, LevelToChangeTo, Cleanup]()
			{
				if (LevelToChangeTo.IsValid())
				{
					Player->SetMaxMovementSpeed(Player->GetOriginalMovementSpeed());
					UGameplayStatics::OpenLevel(this, LevelToChangeTo);
				}
				SetHasOpenedDoor(false);
			},
			FadeDuration, 
			false 
		);
}


bool ADoor::GetHasOpenedDoor() const
{
	return bHasOpenedDoor;
}

void ADoor::SetHasOpenedDoor(const bool InHasOpenedDoor)
{
	bHasOpenedDoor = InHasOpenedDoor;
}
