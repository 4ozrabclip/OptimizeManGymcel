// Copyright © 2025 4ozStudio. All rights reserved.

#include "Widgets/Minigames/Concrete/Slots/SlotItem_OM.h"

#include "Components/Image.h"

void USlotItem_OM::NativeConstruct()
{
	Super::NativeConstruct();
}

void USlotItem_OM::SetType(FSlotItemData InType)
{
	Type = InType;

	if (Type.Image)
		SetImage(Type.Image);
}

void USlotItem_OM::SetImage(UTexture2D* InImage)
{
	if (InImage)
		ItemImage->SetBrushResourceObject(InImage);
}
