// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/VendingMachine_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/WidgetComponent.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Structs/AudioTypes.h"
#include "Widgets/Gym/Concrete/VendingMachineWidget_OM.h"


AVendingMachine_OM::AVendingMachine_OM()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	VendorWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	VendorWidgetComponent->SetupAttachment(RootComponent);
	VendorWidgetComponent->SetVisibility(false);

	VendorAudio = CreateDefaultSubobject<UGameAudio_OM>(TEXT("Audio"));
	VendorAudio->SetupAttachment(RootComponent);
	VendorAudio->SetAudioType(EAudioTypes::SfxAudio);
	VendorAudio->bAutoActivate = true;

	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocation"));
	SpawnLocation->SetupAttachment(RootComponent);
	SpawnLocation->SetVisibility(false);
}

void AVendingMachine_OM::BeginPlay()
{
	Super::BeginPlay();
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!PlayerController)
		PlayerController = Cast<APlayerController_OM>(Player->GetController());
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	SetActorTickEnabled(false);

	if (UVendingMachineWidget_OM* Widg = Cast<UVendingMachineWidget_OM>(VendorWidgetComponent->GetWidget()))
		Widg->InitVendingMachine(this);
}

void AVendingMachine_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Player) return;

	if (Player)
	{
		FVector2D Delta = FVector2D(this->GetActorLocation()) - FVector2D(Player->GetActorLocation());
		
		if (Delta.Size() > 200)
		{
			ExitVendor();
		}
	}
}

void AVendingMachine_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	VendorWidgetComponent->SetVisibility(true);
	Player->SetToUIMode(true);
	PlayerController->HideUnhideInteractableWidget(true);
	SetActorTickEnabled(true);
}


void AVendingMachine_OM::PlaySound(USoundBase* InSound) const
{
	if (!VendorAudio) return;
	if (!InSound) return;

	VendorAudio->SetSound(InSound);

	VendorAudio->Play();
	
}

void AVendingMachine_OM::ExitVendor()
{
	VendorWidgetComponent->SetVisibility(false);
	Player->SetToUIMode(false);
	PlayerController->HideUnhideInteractableWidget(false);
	SetActorTickEnabled(false);
}

void AVendingMachine_OM::SpawnItem(const FConsumableType& ItemToSpawn)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (const TSubclassOf<AConsumable_OM> Item : VendingInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Item->GetName());
		if (AConsumable_OM* Consumable = Item->GetDefaultObject<AConsumable_OM>())
		{
			if (Consumable->GetConsumableType() == ItemToSpawn)
			{

				FTransform SpawnTransform = SpawnLocation->GetComponentTransform();
				UE_LOG(LogTemp, Warning, TEXT("Spawning: %s At Location X: %f, Y: %f, Z: %f"),
					*Consumable->GetName(),
					SpawnTransform.GetLocation().X,
					SpawnTransform.GetLocation().Y,
					SpawnTransform.GetLocation().Z);
				if (AConsumable_OM* SpawnedItem = GetWorld()->SpawnActor<AConsumable_OM>(Item, SpawnTransform, SpawnParams))
				{
					SpawnedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				}
				break;
			}
		}
	}
}
