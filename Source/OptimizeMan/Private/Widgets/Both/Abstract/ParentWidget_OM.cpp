// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Abstract/ParentWidget_OM.h"

#include "Components/Button.h"


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
