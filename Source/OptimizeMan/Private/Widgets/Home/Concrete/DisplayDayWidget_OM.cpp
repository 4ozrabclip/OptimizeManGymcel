// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Home/Concrete/DisplayDayWidget_OM.h"

#include "Components/TextBlock.h"
#include "Game/Persistent/GameInstance_OM.h"

void UDisplayDayWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UDisplayDayWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	if (!DisplayDayText)
	{
		UE_LOG(LogTemp, Error, TEXT("No Display Day TextBlock"));
		return;
	}

	if (bIsDarkMode)
	{
		DisplayDayText->SetColorAndOpacity(White);
	}
	else
	{
		DisplayDayText->SetColorAndOpacity(Black);
	}
}

void UDisplayDayWidget_OM::SetText(const FString& InText)
{
	WidgetTextString = *InText;

	if (!DisplayDayText)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Textblock"));
		return;
	}
	
	DisplayDayText->SetText(FText::FromString(WidgetTextString));

}

FString UDisplayDayWidget_OM::GetText()
{
	return WidgetTextString;
}
