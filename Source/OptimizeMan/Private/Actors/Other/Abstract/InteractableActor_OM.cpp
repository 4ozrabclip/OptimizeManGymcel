// Copyright © 2025 4ozStudio. All rights reserved.

#include "Actors/Other/Abstract/InteractableActor_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/PointLightComponent.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

// Sets default values
AInteractableActor_OM::AInteractableActor_OM()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionProfileName(TEXT("Default"));
	RootComponent = ItemMesh;
	
	AuraLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AuraLight"));
	AuraLight->SetupAttachment(RootComponent);
	AuraLight->SetVisibility(true);
	AuraLight->SetCastShadows(false);
	AuraLight->SetAttenuationRadius(100.f);
	AuraLight->SetIntensityUnits(ELightUnits::Candelas);
	AuraLight->SetIntensity(6.f);
}

void AInteractableActor_OM::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	if (!GameInstance) return;
	PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) return;
	Player = Cast<APlayerCharacter_OM>(PlayerController->GetPawn());
	if (!Player) return;

	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoManager) return;
	InteractableInterfaceProperties.InteractableText = InteractableText;
	InteractableInterfaceProperties.InteractableWidget = InteractableWidget;

	DarkModeToggle(GameInstance->GetDarkMode());

	if (!GameInstance->OnDarkModeToggled.IsAlreadyBound(this, &AInteractableActor_OM::DarkModeToggle))
	{
		GameInstance->OnDarkModeToggled.AddDynamic(this, &AInteractableActor_OM::DarkModeToggle);
	}
}

void AInteractableActor_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
	if (GameInstance)
	{
		GameInstance->OnDarkModeToggled.RemoveDynamic(this, &AInteractableActor_OM::DarkModeToggle);
	}
}

void AInteractableActor_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AInteractableActor_OM::Interact_Implementation()
{
}
