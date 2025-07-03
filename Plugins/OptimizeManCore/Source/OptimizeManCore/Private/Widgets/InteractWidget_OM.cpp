// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractWidget_OM.h"

#include "Components/TextBlock.h"

void UInteractWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (!TextBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("No Text Block in InteractableWidget"));
		return;
	}
	CheckAndSetTextColour();

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

void UInteractWidget_OM::CheckAndSetTextColour()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No game instance, recasting.."));
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}

	if (!TextBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("No Text Block in InteractableWidget"));
		return;
	}
	
	if (GameInstance->GetDarkMode())
	{
		TextBlock->SetColorAndOpacity(White);
		UE_LOG(LogTemp, Error, TEXT("Set text to white"));
	}
	else
	{
		TextBlock->SetColorAndOpacity(Black);
		UE_LOG(LogTemp, Error, TEXT("Set text to black"));
	}
}

FString UInteractWidget_OM::GetText()
{

	return WidgetTextString;
}
