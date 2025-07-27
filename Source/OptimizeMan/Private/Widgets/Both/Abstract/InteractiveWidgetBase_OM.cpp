// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Abstract/InteractiveWidgetBase_OM.h"

#include "Components/Button.h"
#include "Components/PanelWidget.h"
#include "Components/Slider.h"


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

	if (TSharedPtr<SWidget> FocusedWidget = FSlateApplication::Get().GetKeyboardFocusedWidget())
	{
		UE_LOG(LogTemp, Error, TEXT("Ticking"));
		if (!CurrentOpenWindow) return;
		for (FFocusableWidgetStruct& FocusableWidget : CurrentOpenWindow->FocusableContent)
		{
			UE_LOG(LogTemp, Error, TEXT("Ticking 2 %s: "), *FocusableWidget.Type.ToString());
			if (FocusableWidget.IsButton())
				UpdateButtonFocusVisuals(FocusableWidget.ButtonData.Button, FocusableWidget.ButtonData.DefaultButtonStyle, FocusedWidget == FocusableWidget.ButtonData.Button->GetCachedWidget());
		}
	}
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
void UInteractiveWidgetBase_OM::OpenWindow(const FName InWindowName, bool bUsingGameAndUI)
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
					Window.FocusableContent[0].ButtonData.Button->SetFocus();
				else
					Window.FocusableContent[0].SliderData.Slider->SetFocus();
				
			}

		}
		else
		{
			Window.bIsOpen = false;
			Window.Window->SetVisibility(ESlateVisibility::Hidden);
		}
	}
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

