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

void UParentWidget_OM::SetupButtonStyle(FButtonStyle& Style, UMaterial* Image, UMaterial* HoverImage)
{
	if (!Image || !HoverImage)
	{
		UE_LOG(LogTemp, Error, TEXT("Image or HoverImage is null"));
		return;
	}
	Style.Normal.SetResourceObject(Image);
	Style.Hovered.SetResourceObject(HoverImage);
	Style.Pressed.SetResourceObject(Image);
	
	Style.Normal.Margin = FMargin(0);
	Style.Hovered.Margin = FMargin(0);
	Style.Pressed.Margin = FMargin(0);
    
	Style.NormalPadding = FMargin(15);
	Style.PressedPadding = FMargin(15);
}


void UParentWidget_OM::FadeIn()
{
	if (IsInViewport() || bIsFadingIn)
		return;

	UE_LOG(LogTemp, Display, TEXT("Fade iN called on: %s"), *this->GetName());
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
