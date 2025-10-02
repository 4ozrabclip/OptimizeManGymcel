// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/VendingMachineWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UVendingMachineWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
		VendingMachine = Cast<AVendingMachine_OM>(Player->GetCurrentInteractedActor());

	Option1_Button->SetVisibility(ESlateVisibility::Hidden);
	Option2_Button->SetVisibility(ESlateVisibility::Hidden);
	Option3_Button->SetVisibility(ESlateVisibility::Hidden);
	Option1Price_Text->SetVisibility(ESlateVisibility::Hidden);
	Option2Price_Text->SetVisibility(ESlateVisibility::Hidden);
	Option3Price_Text->SetVisibility(ESlateVisibility::Hidden);
	Option1_Image->SetVisibility(ESlateVisibility::Hidden);
	Option2_Image->SetVisibility(ESlateVisibility::Hidden);
	Option3_Image->SetVisibility(ESlateVisibility::Hidden);
	Option1Desc_Text->SetVisibility(ESlateVisibility::Hidden);
	Option2Desc_Text->SetVisibility(ESlateVisibility::Hidden);
	Option3Desc_Text->SetVisibility(ESlateVisibility::Hidden);
	
	
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
		Exit_Button->OnClicked.AddDynamic(this, &UVendingMachineWidget_OM::ExitVendor);
	}
	
	SetConsumables();

	OpenWindow(FName("MainWindow"));
}

void UVendingMachineWidget_OM::InitWindowsArray()
{
	Super::InitWindowsArray();
	FUserInterfaceWindow MainWindow;
	MainWindow.WindowName = FName("MainWindow");
	MainWindow.Window = MainCanvas;
	MainWindow.FocusableContent.Add(MakeButton(Option1_Button, Option1_Button->GetStyle()));
	MainWindow.FocusableContent.Add(MakeButton(Option2_Button, Option2_Button->GetStyle()));
	MainWindow.FocusableContent.Add(MakeButton(Option3_Button, Option3_Button->GetStyle()));
	Windows.Add(MainWindow);
}

void UVendingMachineWidget_OM::ExitVendor()
{
	if (Player)
	{
		Player->SetCurrentPlayMode(EPlayModes::RegularMode);
		Player->bInteractableOpen = false;
	}
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
		if (VendingMachine->GetVendorInventory().Num() <= 0) return;
		
		for (size_t Index = 0; Index < VendingMachine->GetVendorInventory().Num(); ++Index)
		{
			if (VendingMachine->GetVendorInventory().IsValidIndex(Index) &&
				VendingMachine->GetVendorInventory()[Index])
			{
				if (TSubclassOf<AConsumable_OM> ItemObj = VendingMachine->GetVendorInventory()[Index])
				{
					if (AConsumable_OM* DefaultObject = ItemObj->GetDefaultObject<AConsumable_OM>())
					{
						FVendorItem Item;
						Item.ConsumableData = DefaultObject->GetConsumableType();
						if (Index == 0)
						{
							Item.PriceTextBlock = Option1Price_Text;
							Item.DescriptionTextBlock = Option1Desc_Text;
							Item.BuyButton = Option1_Button;
							Item.IconImage = Option1_Image;
						}
						else if (Index == 1)
						{
							Item.PriceTextBlock = Option2Price_Text;
							Item.DescriptionTextBlock = Option2Desc_Text;
							Item.BuyButton = Option2_Button;
							Item.IconImage = Option2_Image;
						}
						else if (Index == 2)
						{
							Item.PriceTextBlock = Option3Price_Text;
							Item.DescriptionTextBlock = Option3Desc_Text;
							Item.BuyButton = Option3_Button;
							Item.IconImage = Option3_Image;
						}
						SetConsumableTextAndImage(Item);
					}
				}
			}
		}
	}
}
void UVendingMachineWidget_OM::SetConsumableTextAndImage(FVendorItem& InItem)
{
	FConsumableType& Data = InItem.ConsumableData;
	if (!InItem.PriceTextBlock.IsValid() || !InItem.DescriptionTextBlock.IsValid() || !InItem.BuyButton.IsValid()) return;

	Consumables.Add(Data);
	
	InItem.BuyButton->SetVisibility(ESlateVisibility::Visible);
	InItem.DescriptionTextBlock->SetVisibility(ESlateVisibility::Visible);
	InItem.IconImage->SetVisibility(ESlateVisibility::Visible);
	InItem.PriceTextBlock->SetVisibility(ESlateVisibility::Visible);
	SetConsumablesTextHelper(InItem.DescriptionTextBlock.Get(), FText::FromString(Data.NameString));
	SetConsumablesTextHelper(InItem.PriceTextBlock.Get(), FText::FromString(FString::FromInt(Data.Price)));
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

	if (!GameInstance) return;
	
	int PlayerPoints = GameInstance->GetGamePoints();

	UE_LOG(LogTemp, Display, TEXT("Points (Widget): %d\n Consumables Price: %d"), PlayerPoints, InConsumable.Price);

	if (PlayerPoints >= InConsumable.Price)
	{
		VendingMachine->PlayBuySound();
		VendingMachine->SpawnItem(InConsumable);
		GameInstance->AddGamePoints(-InConsumable.Price);
		
	}
	else
	{
		VendingMachine->PlayNoMoneySound();
		GameInstance->AddGamePoints(0);
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
