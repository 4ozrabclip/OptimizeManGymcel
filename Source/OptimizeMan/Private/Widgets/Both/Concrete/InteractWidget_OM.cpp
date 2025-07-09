// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/InteractWidget_OM.h"

#include "Components/TextBlock.h"

void UInteractWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (!TextBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("No Text Block in InteractableWidget"));
		return;
	}


}

void UInteractWidget_OM::SetText(const FString& InText)
{
	WidgetTextString = *InText;

	if (!TextBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("No Text Block in InteractableWidget"));
		return;
	}
	
	
	TextBlock->SetText(FText::FromString(WidgetTextString));

	
}


void UInteractWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	if (!TextBlock)
    {
    	UE_LOG(LogTemp, Error, TEXT("No Text Block in InteractableWidget"));
    	return;
    }
	if (bIsDarkMode)
	{
		TextBlock->SetColorAndOpacity(White);
	}
	else
	{
		TextBlock->SetColorAndOpacity(Black);
	}
}

FString UInteractWidget_OM::GetText()
{

	return WidgetTextString;
}
