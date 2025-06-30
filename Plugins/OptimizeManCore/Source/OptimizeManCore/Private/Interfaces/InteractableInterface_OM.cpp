// Copyright © 2025 4ozStudio. All rights reserved.


#include "Interfaces/InteractableInterface_OM.h"


#include "Blueprint/UserWidget.h"

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
