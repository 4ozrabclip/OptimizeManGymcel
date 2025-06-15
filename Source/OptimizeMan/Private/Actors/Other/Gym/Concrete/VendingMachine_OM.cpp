// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/VendingMachine_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Gym/Concrete/VendingMachineWidget_OM.h"


AVendingMachine_OM::AVendingMachine_OM()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	VendorWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	VendorWidgetComponent->SetupAttachment(RootComponent);
	VendorWidgetComponent->SetVisibility(false);

	
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

void AVendingMachine_OM::ExitVendor()
{
	VendorWidgetComponent->SetVisibility(false);
	Player->SetToUIMode(false);
	PlayerController->HideUnhideInteractableWidget(false);
	SetActorTickEnabled(false);
}
