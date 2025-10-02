// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Minigames/Concrete/Slots/SlotReel_OM.h"

#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Widgets/Minigames/Concrete/Slots/SlotItem_OM.h"

void USlotReel_OM::NativeConstruct()
{
	Super::NativeConstruct();

	SetInitialItems();
	
}

void USlotReel_OM::SetInitialItems()
{
	TopItem->SetType(GetRandomType());
	TopItem->SetType(GetRandomType());
	UnderTopItem->SetType(GetRandomType());
	AboveBottomItem->SetType(GetRandomType());
	BottomItem->SetType(GetRandomType());
	CenterItem->SetType(GetRandomType());

	
}

void USlotReel_OM::StartScroll(int EnergyBid, int ReelIndex)
{
	AllItems = {
		BottomItem,
		AboveBottomItem,
		CenterItem,
		UnderTopItem,
		TopItem
	};

	ReelScrollBox->SetScrollOffset(StartScrollOffset);

	CurrentScrollOffset = StartScrollOffset;
	EndScrollOffset = ReelScrollBox->GetScrollOffsetOfEnd();

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	
	GetWorld()->GetTimerManager().SetTimer(ScrollTimerHandle, this, &USlotReel_OM::TickScroll, TickSpeed, true);

	float ScrollTime = FMath::FRandRange(4.f * ReelIndex, 7.f * ReelIndex);
	GetWorld()->GetTimerManager().SetTimer(EndScrollTimerHandle, this, &USlotReel_OM::EndScroll, ScrollTime, false);
	
}

void USlotReel_OM::SelectItemCenter(ESlotItemType InType)
{
	if (AllItems.Num() > 0)
	{
		for (auto& Item : AllItems)
		{
			if (Item->GetType().Type == InType)
			{
				Item->SetIsFinalCenter(true);
				return;
			}
		}
	}
}


void USlotReel_OM::TickScroll()
{
	float HalfWay = EndScrollOffset / 2;

	constexpr float RandMin = 5;
	constexpr float RandMax = 20;
	
	if (CurrentScrollOffset > HalfWay && FMath::RandBool())
	{
		CurrentScrollOffset -= ScrollSpeed * FMath::RandRange(RandMin, RandMax);
	}
	else
	{
		CurrentScrollOffset += ScrollSpeed * FMath::RandRange(RandMin, RandMax);
	}

	CurrentScrollOffset = FMath::Clamp(CurrentScrollOffset, StartScrollOffset, EndScrollOffset);
	ReelScrollBox->SetScrollOffset(CurrentScrollOffset);
	
}

void USlotReel_OM::EndScroll()
{
	GetWorld()->GetTimerManager().ClearTimer(ScrollTimerHandle);

	if (AllItems.Num() > 0)
	{
		for (auto& Item : AllItems)
		{
			if (auto* ItemPtr = Item.Get())
			{
				if (ItemPtr->GetIsFinalCenter())
				{
					ReelScrollBox->ScrollWidgetIntoView(ItemPtr);
					OnScrollFinished.Broadcast();
					break;
				}
			}
		}
	}

}


FSlotItemData USlotReel_OM::GetRandomType()
{
	return ItemTypes[FMath::RandRange(0, ItemTypes.Num() - 1)];
}
