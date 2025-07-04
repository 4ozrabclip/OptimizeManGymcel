// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/VendingMachineWidget_OM.h"

#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Game/GameInstance_OM.h"
#include "Utils/UtilityHelpers_OMG.h"

void UVendingMachineWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);
	if (!OptionBuy_Button || !OptionBuy_Button_1 || !OptionBuy_Button_2) return;
	if (!VendingMachine) return;
	if (!Exit_Button) return;
	if (!NoMoney_Overlay) return;

	OptionBuy_Button->OnClicked.Clear();
	OptionBuy_Button->OnClicked.AddDynamic(this, &UVendingMachineWidget_OM::OnOption1Clicked);

	OptionBuy_Button_1->OnClicked.Clear();
	OptionBuy_Button_1->OnClicked.AddDynamic(this, &UVendingMachineWidget_OM::OnOption2Clicked);

	OptionBuy_Button_2->OnClicked.Clear();
	OptionBuy_Button_2->OnClicked.AddDynamic(this, &UVendingMachineWidget_OM::OnOption3Clicked);
	

	Exit_Button->OnClicked.Clear();
	Exit_Button->OnClicked.AddDynamic(VendingMachine, &AVendingMachine_OM::ExitVendor);

	NoMoney_Overlay->SetVisibility(ESlateVisibility::Hidden);
	
	
	SetConsumables();
	
}

void UVendingMachineWidget_OM::NativeDestruct()
{
	Super::NativeDestruct();
	
	GetWorld()->GetTimerManager().ClearTimer(NoMoneyTimer);
	
	Consumables.Empty();
	
}

void UVendingMachineWidget_OM::SetConsumables()
{
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
		SetConsumablesTextHelper(OptionTitle_Text, FText::FromString(Consumables[0].NameString));
	if (Consumables.IsValidIndex(1))
		SetConsumablesTextHelper(OptionTitle_Text_1, FText::FromString(Consumables[1].NameString));
	if (Consumables.IsValidIndex(2))
		SetConsumablesTextHelper(OptionTitle_Text_2, FText::FromString(Consumables[2].NameString));
		
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

	int PlayerMoney = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetMoney();

	if (PlayerMoney >= InConsumable.Price)
	{
		VendingMachine->PlayBuySound();
		VendingMachine->SpawnItem(InConsumable);
		GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetMoney(-InConsumable.Price);
	}
	else
	{
		VendingMachine->PlayNoMoneySound();
		ShowNoMoneyWindow();
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
void UVendingMachineWidget_OM::ShowNoMoneyWindow()
{
	NoMoney_Overlay->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().ClearTimer(NoMoneyTimer);
	GetWorld()->GetTimerManager().SetTimer(NoMoneyTimer, [this]()
	{
		NoMoney_Overlay->SetVisibility(ESlateVisibility::Hidden);
	}, 2.5f, false);
	
}