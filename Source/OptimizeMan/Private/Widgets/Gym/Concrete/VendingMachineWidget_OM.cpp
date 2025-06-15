// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/VendingMachineWidget_OM.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UVendingMachineWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

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
	if (VendingMachine && Exit_Button)
	{
		Exit_Button->OnClicked.Clear();
		Exit_Button->OnClicked.AddDynamic(VendingMachine, &AVendingMachine_OM::ExitVendor);
	}

	SetConsumables();
	
}

void UVendingMachineWidget_OM::NativeDestruct()
{
	Super::NativeDestruct();

	Consumables.Empty();
}

void UVendingMachineWidget_OM::SetConsumables()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	if (VendingMachine)
	{
		for (AConsumable_OM* Item : VendingMachine->GetVendorInventory())
		{
			Consumables.Add(Item->GetConsumableType());
		}
	}
	SetConsumablesText();
}

void UVendingMachineWidget_OM::SetConsumablesText()
{
	if (Consumables.Num() <= 0) return;

	if (Consumables.IsValidIndex(0))
		SetConsumablesTextHelper(Option1Name_Text, FText::FromName(Consumables[0].Name));
	if (Consumables.IsValidIndex(1))
		SetConsumablesTextHelper(Option2Name_Text, FText::FromName(Consumables[1].Name));
	if (Consumables.IsValidIndex(2))
		SetConsumablesTextHelper(Option3Name_Text, FText::FromName(Consumables[2].Name));
		
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

	GameInstance->AddConsumable(InConsumable);
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
