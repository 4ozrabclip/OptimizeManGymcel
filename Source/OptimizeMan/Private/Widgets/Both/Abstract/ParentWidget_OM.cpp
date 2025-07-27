// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Abstract/ParentWidget_OM.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"



void UParentWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	Black = FLinearColor(0.f, 0.f, 0.f);

	White = FLinearColor(1.f, 1.f, 1.f);

	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}

	if (GameInstance)
	{
		GameSettings = GameInstance->GetGameSettings();

	
		DarkModeToggle(GameInstance->GetDarkMode());

	
		if (!GameInstance->OnDarkModeToggled.IsAlreadyBound(this, &UParentWidget_OM::DarkModeToggle))
		{
			GameInstance->OnDarkModeToggled.AddDynamic(this, &UParentWidget_OM::DarkModeToggle);
		}
	}
}

void UParentWidget_OM::NativeDestruct()
{
	Super::NativeDestruct();
	if (GameInstance)
	{
		GameInstance->OnDarkModeToggled.RemoveDynamic(this, &UParentWidget_OM::DarkModeToggle);
	}
}

void UParentWidget_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (TSharedPtr<SWidget> FocusedWidget = FSlateApplication::Get().GetKeyboardFocusedWidget())
	{
		if (!CurrentOpenWindow) return;
		for (UWidget* FocusableWidget : CurrentOpenWindow->FocusableContent)
		{
			if (UButton* FocusableButton = Cast<UButton>(FocusableWidget))
				UpdateButtonFocusVisuals(FocusableButton, CurrentButtonStyle, FocusedWidget == FocusableWidget->GetCachedWidget());
		}
	}
}

FUserInterfaceWindow UParentWidget_OM::InitializeWindow(UPanelWidget* InWindow, TArray<UWidget*> InFocusableContent, FName InWindowName)
{
	FUserInterfaceWindow OutWindow;

	if (InWindow)
		OutWindow.Window = InWindow;
	for (UWidget* FocusablePiece : InFocusableContent)
	{
		if (FocusablePiece && FocusablePiece->IsValidLowLevel())
		{
			OutWindow.FocusableContent.Add(FocusablePiece);
		}

	}

	if (!Windows.Contains(InWindowName))
		OutWindow.WindowName = InWindowName;
	
	return OutWindow;
}

void UParentWidget_OM::OpenWindow(const FName InWindowName, bool bUsingGameAndUI)
{
	for (FUserInterfaceWindow& Window : Windows)
	{
		if (Window.WindowName == InWindowName)
		{
			Window.bIsOpen = true;
			Window.Window->SetVisibility(ESlateVisibility::Visible);
			CurrentOpenWindow = &Window;
			if (Window.FocusableContent.IsValidIndex(0))
				Window.FocusableContent[0]->SetFocus();
		}
		else
		{
			Window.bIsOpen = false;
			Window.Window->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UParentWidget_OM::UpdateButtonFocusVisuals(UButton* Button, const FButtonStyle& DefaultStyle, bool bIsFocused)
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


void UParentWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
}

void UParentWidget_OM::FadeIn()
{
	if (IsInViewport() || bIsFadingIn)
		return;

	bIsFadingIn = true;
	SetRenderOpacity(0.f);
	AddToViewport();

	GetWorld()->GetTimerManager().SetTimer(
		FadeInTimerHandle,
		[this]()
		{
			const float CurrentOpacity = GetRenderOpacity();
			const float NewOpacity = FMath::FInterpConstantTo(CurrentOpacity, 1.0f, GetWorld()->GetDeltaSeconds(), 1.0f);

			SetRenderOpacity(NewOpacity);
		
			if (NewOpacity >= 1.f)
			{
				bIsFadingIn = false;
				GetWorld()->GetTimerManager().ClearTimer(FadeInTimerHandle);
			}
		},
		0.016f, 
		true    
	);
}
