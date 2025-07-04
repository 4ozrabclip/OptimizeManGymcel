// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ParentWidget_OM.h"

#include "Game/GameInstance_OM.h"


void UParentWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}

	if (GameInstance)
	{
		GameSettings = GameInstance->GetGameSettings();

		GameInstance->OnDarkModeToggled.AddDynamic(this, &UParentWidget_OM::CheckAndSetDarkMode);
	}


	Black = FLinearColor(0.f, 0.f, 0.f);

	White = FLinearColor(1.f, 1.f, 1.f);
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