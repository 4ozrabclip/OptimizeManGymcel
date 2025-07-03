// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Other/Abstract/Door.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/PointLightComponent.h"
#include "Controllers/PlayerController_OM.h"
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
	
	if (APlayerCharacter_OM* Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		Player->SyncStatsToGameInstance();
	
}

void ADoor::ClearTimers()
{
	if (APlayerCharacter_OM* Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		Player->ClearTimers();
}

void ADoor::OpenDoor()
{
	SetHasOpenedDoor(true);
	if (const APlayerController_OM* PC = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (APlayerCharacter_OM* Player = Cast<APlayerCharacter_OM>(PC->GetPawn()))
		{
			Player->SetMaxMovementSpeed(0.f);
			
			if (APlayerCameraManager* CameraManager = PC->PlayerCameraManager)
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
					if (APlayerCharacter_OM* Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
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
