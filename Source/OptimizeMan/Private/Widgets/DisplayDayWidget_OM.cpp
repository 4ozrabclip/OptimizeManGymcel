// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DisplayDayWidget_OM.h"
#include "Components/TextBlock.h"
#include "Utils/GameInstance_OM.h"

void UDisplayDayWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	CheckAndSetTextColour();
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
void UDisplayDayWidget_OM::CheckAndSetTextColour()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No game instance, recasting.."));
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}
	if (!DisplayDayText)
	{
		UE_LOG(LogTemp, Error, TEXT("No Display Day TextBlock"));
		return;
	}

	if (GameInstance->GetDarkMode())
	{
		DisplayDayText->SetColorAndOpacity(White);
		UE_LOG(LogTemp, Error, TEXT("Set text to white"));
	}
	else
	{
		DisplayDayText->SetColorAndOpacity(Black);
		UE_LOG(LogTemp, Error, TEXT("Set text to black"));
	}
}
FString UDisplayDayWidget_OM::GetText()
{
	return WidgetTextString;
}
