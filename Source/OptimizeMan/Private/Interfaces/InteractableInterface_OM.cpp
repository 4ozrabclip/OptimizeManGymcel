// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InteractableInterface_OM.h"

#include "Blueprint/UserWidget.h"

// Add default functionality here for any IInteractableInterface_OM functions that are not pure virtual.
TSubclassOf<UUserWidget> IInteractableInterface_OM::GetInteractableWidget() const
{
	return InteractableInterfaceProperties.InteractableWidget;
}

FString IInteractableInterface_OM::GetInteractionWidgetText() const
{
	return InteractableInterfaceProperties.InteractableText.ToString();
}
void IInteractableInterface_OM::SetInteractableWidgetText(const FString& InText)
{
	InteractableInterfaceProperties.InteractableText = FText::FromString(*InText);
	
}
