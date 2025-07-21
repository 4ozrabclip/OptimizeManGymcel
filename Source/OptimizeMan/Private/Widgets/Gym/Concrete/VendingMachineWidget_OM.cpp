// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/VendingMachineWidget_OM.h"

#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"

void UVendingMachineWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);
	if (Option1_Button)
	{
		Option1_Button->OnClicked.Clear();
		Option1_Button->OnClicked.AddDynamic(this, &UVendingMachineWidget_OM::OnOption1Clicked);
	}
	if (Option2_Button)
	{
		Option2_Button->OnClicked.Clear();
		Option2_Button->OnClicked.AddDynamic(this, &UVendingMachineWidget_OM::OnOption2Clicked);
	}
	if (Option3_Button)
	{
		Option3_Button->OnClicked.Clear();
		Option3_Button->OnClicked.AddDynamic(this, &UVendingMachineWidget_OM::OnOption3Clicked);
	}
	if (Exit_Button)
	{
		Exit_Button->OnClicked.Clear();
		Exit_Button->OnClicked.AddDynamic(this, &UVendingMachineWidget_OM::ExitVendor);
	}

	
	SetConsumables();
	
}

void UVendingMachineWidget_OM::ExitVendor()
{
	UE_LOG(LogTemp, Display, TEXT("Exit Vendor Called from widget"));
	RemoveFromParent();
	VendingMachine->ExitVendor();
}

void UVendingMachineWidget_OM::NativeDestruct()
{
	Super::NativeDestruct();
	
	GetWorld()->GetTimerManager().ClearTimer(NoMoneyTimer);
	
	Consumables.Empty();
	
}

void UVendingMachineWidget_OM::SetConsumables()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	if (VendingMachine)
	{
		for (TSubclassOf<AConsumable_OM> Item : VendingMachine->GetVendorInventory())
		{
			if (Item)
			{
				if (AConsumable_OM* DefaultObject = Item->GetDefaultObject<AConsumable_OM>())
				{
					Consumables.Add(DefaultObject->GetConsumableType());
				}
			}
		}
	}
	SetConsumablesText();
}

void UVendingMachineWidget_OM::SetConsumablesText()
{
	if (Consumables.Num() <= 0) return;

	if (Consumables.IsValidIndex(0))
		SetConsumablesTextHelper(Option1Desc_Text, FText::FromString(Consumables[0].NameString));
	if (Consumables.IsValidIndex(1))
		SetConsumablesTextHelper(Option2Desc_Text, FText::FromString(Consumables[1].NameString));
	if (Consumables.IsValidIndex(2))
		SetConsumablesTextHelper(Option3Desc_Text, FText::FromString(Consumables[2].NameString));
		
}

void UVendingMachineWidget_OM::SetConsumablesTextHelper(UTextBlock* InTextBlock, const FText& InText)
{
	if (InTextBlock)
	{
		InTextBlock->SetText(InText);
	}
}

void UVendingMachineWidget_OM::BuyConsumable(const FConsumableType& InConsumable)
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	int PlayerMoney = GameInstance->GetMoney();

	if (PlayerMoney >= InConsumable.Price)
	{
		VendingMachine->PlayBuySound();
		VendingMachine->SpawnItem(InConsumable);
		GameInstance->SetMoney(-InConsumable.Price);
	}
	else
	{
		VendingMachine->PlayNoMoneySound();
	}
}

void UVendingMachineWidget_OM::OnOption1Clicked()
{
	if (Consumables.IsValidIndex(0))
		BuyConsumable(Consumables[0]);
}
void UVendingMachineWidget_OM::OnOption2Clicked()
{
	if (Consumables.IsValidIndex(1))
		BuyConsumable(Consumables[1]);
}
void UVendingMachineWidget_OM::OnOption3Clicked()
{
	if (Consumables.IsValidIndex(2))
		BuyConsumable(Consumables[2]);
}
