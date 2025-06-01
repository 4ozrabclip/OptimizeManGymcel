// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/PointLightComponent.h"
#include "Utils/GameInstance_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/TodoManagementSubsystem.h"

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
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Game instance null in interactable actor"));
		return;
	}
	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return;
	PlayerController = Cast<APlayerController_OM>(Player->GetController());
	if (!PlayerController) return;
	InteractableInterfaceProperties.InteractableText = InteractableText;
	InteractableInterfaceProperties.InteractableWidget = InteractableWidget;
}

void AInteractableActor_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void AInteractableActor_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AInteractableActor_OM::Interact_Implementation()
{
}
