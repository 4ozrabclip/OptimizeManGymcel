// Copyright © 2025 4ozStudio. All rights reserved.

#include "Actors/InteractableActor_OM.h"

#include "Characters/PlayerCharacterBase_OM.h"
#include "Components/PointLightComponent.h"
#include "Controllers/PlayerController_OM.h"
#include "Game/GameInstance_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


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

	ConstructorHelpers::FClassFinder<UUserWidget>
		InteractWidgetBPClassRef(TEXT("/OptimizeManCore/Widgets/BPInteractWidget"));
	if (InteractWidgetBPClassRef.Succeeded())
		InteractableWidget = InteractWidgetBPClassRef.Class;
	
}

void AInteractableActor_OM::BeginPlay()
{
	Super::BeginPlay();
	InteractableInterfaceProperties.InteractableText = InteractableText;
	InteractableInterfaceProperties.InteractableWidget = InteractableWidget;

	GameInstance = Cast<UGameInstance_OM>(GetGameInstance());

	PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Player = Cast<APlayerCharacterBase_OM>(PlayerController->GetPawn());

	if (GameInstance)
		GameInstance->OnDarkModeToggled.AddDynamic(this, &AInteractableActor_OM::CheckAndSetDarkMode);
}

void AInteractableActor_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
}
