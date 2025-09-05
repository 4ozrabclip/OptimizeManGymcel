// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Abstract/InteractiveWidgetBase_OM.h"

#include "Actors/Characters/Player/PlayerControllerBase_OM.h"
#include "Components/Button.h"
#include "Components/PanelWidget.h"
#include "Components/Slider.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Utils/Structs/AudioTypes.h"


void UInteractiveWidgetBase_OM::NativeConstruct()
{
	Super::NativeConstruct();

	

	InitWindowsArray();
	
}

void UInteractiveWidgetBase_OM::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInteractiveWidgetBase_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsUsingController)
		ManageControllerInteraction();
	
}

FUserInterfaceWindow UInteractiveWidgetBase_OM::InitializeWindow(UPanelWidget* InWindow, TArray<FFocusableWidgetStruct> InFocusableContent, FName InWindowName)
{
	FUserInterfaceWindow OutWindow;

	if (InWindow)
		OutWindow.Window = InWindow;
	for (const FFocusableWidgetStruct& Focusable : InFocusableContent)
	{
		OutWindow.FocusableContent.Add(Focusable);
		
	}

	if (!Windows.Contains(InWindowName))
		OutWindow.WindowName = InWindowName;
	
	return OutWindow;
}


FFocusableWidgetStruct UInteractiveWidgetBase_OM::MakeButton(UButton* InButton, const FButtonStyle& InStyle)
{
	FButtonStruct BtnStruct;
	BtnStruct.Button = InButton;
	BtnStruct.DefaultButtonStyle = InStyle;

	FFocusableWidgetStruct Focusable;
	Focusable.Type = "Button";
	Focusable.ButtonData = BtnStruct;
	return Focusable;
};
void UInteractiveWidgetBase_OM::OpenWindow(const FName InWindowName, bool bUsingGameAndUI, bool bPlayClick)
{
	for (FUserInterfaceWindow& Window : Windows)
	{
		if (Window.WindowName == InWindowName)
		{
			Window.bIsOpen = true;
			Window.Window->SetVisibility(ESlateVisibility::Visible);
			CurrentOpenWindow = &Window;
			if (Window.FocusableContent.IsValidIndex(0))
			{
				if (Window.FocusableContent[0].IsButton())
					Window.FocusableContent[0].ButtonData.Button->SetUserFocus(GetOwningPlayer());
				else
					Window.FocusableContent[0].SliderData.Slider->SetUserFocus(GetOwningPlayer());
			}

		}
		else
		{
			Window.bIsOpen = false;
			Window.Window->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (bPlayClick)
		PlayClickSound();


}

void UInteractiveWidgetBase_OM::UpdateButtonFocusVisuals(UButton* Button, const FButtonStyle& DefaultStyle, bool bIsFocused)
{
	if (!Button) return;

	if (bIsFocused)
	{
		FButtonStyle FocusedStyle = DefaultStyle;
		FocusedStyle.Normal = DefaultStyle.Hovered; 
		Button->SetStyle(FocusedStyle);
	}
	else
	{
		Button->SetStyle(DefaultStyle);
	}
}

void UInteractiveWidgetBase_OM::PlayClickSound()
{
	if (auto* PC = Cast<APlayerControllerBase_OM>(GetOwningPlayer()))
	{
		if (ClickSound)
			PC->PlayUISound(ClickSound);
	}
}

void UInteractiveWidgetBase_OM::ManageControllerInteraction()
{
	
	if (TSharedPtr<SWidget> FocusedWidget = FSlateApplication::Get().GetKeyboardFocusedWidget())
	{
		if (!CurrentOpenWindow) return;

		if (FocusedWidget.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Focused Widget: %s"), *FocusedWidget->GetTypeAsString());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("FocusedWidget is invalid"));
			return;
		}
		for (FFocusableWidgetStruct& FocusableWidget : CurrentOpenWindow->FocusableContent)
		{
			UButton* Button = FocusableWidget.ButtonData.Button.Get();
			if (!IsValid(Button)) continue;

			TSharedPtr<SWidget> CachedWidget = Button->GetCachedWidget();
			if (!CachedWidget.IsValid()) continue;

			bool bIsFocused = Button->HasUserFocus(GetOwningPlayer());

			UpdateButtonFocusVisuals(Button, FocusableWidget.ButtonData.DefaultButtonStyle, bIsFocused);
		}
	}
}

