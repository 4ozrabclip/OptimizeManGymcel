// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Home/Concrete/ShelfWidget_OM.h"

#include "Actors/Other/Bedroom/Concrete/Shelf_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Button.h"

void UShelfWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();


	InitButtons();
	
}


void UShelfWidget_OM::InitButtons()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No game instance in shelf widget"));
		return;
	}
	FInventoryData& InventoryData = GameInstance->GetInventoryData();
	
	if (UseBabyCrackButton)
	{
		UseBabyCrackButton->OnClicked.RemoveAll(this);
		UseBabyCrackButton->OnClicked.AddDynamic(this, &UShelfWidget_OM::OnUseBabyCrackClicked);

		CheckItemForButtonVisibility(InventoryData.bOwnsPreWorkout, UseBabyCrackButton);
	}
	if (UseSteroidsButton)
	{
		UseSteroidsButton->OnClicked.RemoveAll(this);
		UseSteroidsButton->OnClicked.AddDynamic(this, &UShelfWidget_OM::OnUseSteroidsClicked);

		CheckItemForButtonVisibility(InventoryData.bOwnsSteroids, UseSteroidsButton);
	}
}

void UShelfWidget_OM::CheckItemForButtonVisibility(const bool InHasItem, UButton* InButton)
{
	if (!InButton)
	{
		UE_LOG(LogTemp, Error, TEXT("InButton is null in shelf widget"));
		return;
	}
	if (!InHasItem)
	{
		InButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		InButton->SetVisibility(ESlateVisibility::Visible);
	}
}


void UShelfWidget_OM::OnItemUsed(EShopAndBook InItem)
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No game instance in shelf widget"));
		return;
	}
	
	FInventoryData& InventoryData = GameInstance->GetInventoryData();
	FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();

	AShelf_OM* Shelf = Cast<AShelf_OM>(Player->GetCurrentInteractedActor());

	if (!Shelf)
	{
		UE_LOG(LogTemp, Error, TEXT("Shelf is not the current interacted actor"));
		return;
	}
		
	switch(InItem)
	{
	case EShopAndBook::None:
		return;
	case EShopAndBook::Steroids:
		if (InventoryData.bOwnsSteroids)
		{
			GameInstance->SetPossesion(InventoryData.bOwnsSteroids, false);
			GameInstance->SetPossesion(BodyStatus.bCurrentlyOnSteroids, true);
			UseSteroidsButton->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	case EShopAndBook::PreWorkout:
		if (InventoryData.bOwnsPreWorkout)
		{
			GameInstance->SetPossesion(InventoryData.bOwnsPreWorkout, false);
			UseBabyCrackButton->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	default:
		return;
	}

	Shelf->UpdateShelfItems();
}
