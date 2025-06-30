// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InteractableInterface.h"

#include "Blueprint/UserWidget.h"

// Add default functionality here for any IInteractableInterface_OM functions that are not pure virtual.
TSubclassOf<UUserWidget> IInteractableInterface::GetInteractableWidget() const
{
	return InteractableInterfaceProperties.InteractableWidget;
}

FString IInteractableInterface::GetInteractionWidgetText() const
{
	return InteractableInterfaceProperties.InteractableText.ToString();
}
void IInteractableInterface::SetInteractableWidgetText(const FString& InText)
{
	InteractableInterfaceProperties.InteractableText = FText::FromString(*InText);
	
}
