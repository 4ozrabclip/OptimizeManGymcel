// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Other/Bedroom/Concrete/Bed_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GMB/BedroomGameModeBase_OM.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Game/GameInstance_OM.h"
#include "Utils/UtilityHelpers_OMG.h"

ABed_OM::ABed_OM()
{
	ExtraCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtraCollider"));
	ExtraCollider->SetCollisionProfileName(TEXT("Default"));
	ExtraCollider->SetupAttachment(RootComponent);
}
void ABed_OM::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ABedroomGameModeBase_OM>(UGameplayStatics::GetGameMode(this));
	SetIsSleeping(false);
	SetInteractableWidgetText("Go Sleep");
	CheckAndSetDarkMode();

}
void ABed_OM::CheckAndSetDarkMode()
{
	if (!GameInstance) return;
	if (GameInstance->GetDarkMode())
	{
		AuraLight->SetIntensity(0.5f);
		AuraLight->SetAttenuationRadius(100.f);
	}
	else
	{
		AuraLight->SetIntensity(6.f);
		AuraLight->SetAttenuationRadius(195.f);
	}
}

void ABed_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (bIsSleeping) return;
	if (GameMode->GetWidgetIsVisible()) return;
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	if (!GameInstance) return;
	
	if (!GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetHasBeenToGymToday())
	{
		GymcelUtils::GetPlayer_Gymcel(GetWorld())->ShitReaction();
		return;
	}
	
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->SetMaxMovementSpeed(0.f);
	
	const FInputModeUIOnly Input;
	PlayerController->SetInputMode(Input);
	if (GameInstance->GetDayNumber() == 1)
	{
		GymcelUtils::GetGameInstance_Gymcel(GetWorld())->FinishDemo();
		return;
	}
	
	SetIsSleeping(true);


	if (APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager)
	{
		constexpr float FadeDuration = 2.f;

		CameraManager->StartCameraFade(0.f, 1.f, FadeDuration, FLinearColor::Black, true, true);

		if (SleepTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(SleepTimerHandle);
		}
		SleepDelay(FadeDuration);
	}
}

void ABed_OM::SleepDelay(const float FadeDuration)
{
	const FName LevelToChangeTo = FName("/Game/Levels/Home");

	GetWorld()->GetTimerManager().SetTimer(
			SleepTimerHandle,
			[this, LevelToChangeTo]()
			{
				constexpr float MaxEnergy = 1.f;
				Player->SetMaxMovementSpeed(Player->GetOriginalMovementSpeed());
				GameInstance->IncrementDay();
				FGymResStats& GymResStats = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetGymResStats();
				GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetGymResStats(GymResStats.Energy, MaxEnergy);	
				GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetHasBeenToGymToday(false);
				UGameplayStatics::OpenLevel(this, LevelToChangeTo);
			},
			FadeDuration, 
			false 
		);
}

void ABed_OM::SetIsSleeping(const bool InIsSleeping)
{
	bIsSleeping = InIsSleeping;
}
bool ABed_OM::GetIsSleeping() const
{
	return bIsSleeping;
}
