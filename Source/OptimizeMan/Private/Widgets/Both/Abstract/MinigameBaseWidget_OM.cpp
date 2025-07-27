// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"

void UMinigameBaseWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ExitButton)
	{
		ExitButton->OnClicked.RemoveAll(this);
		ExitButton->OnClicked.AddDynamic(this, &UMinigameBaseWidget_OM::OnExitButtonClicked);
	}

	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	
	
}


void UMinigameBaseWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);

	if (!WhiteExitButton || !WhiteHoveredExitButton || !BlackExitButton || !BlackHoveredExitButton)
	{
		UE_LOG(LogTemp, Error, TEXT("No dark/light mode exit buttons in the widget"));
		return;
	}
	
	if (bIsDarkMode)
	{
		DarkExitStyle.Normal.SetResourceObject(WhiteExitButton);
		DarkExitStyle.Hovered.SetResourceObject(WhiteHoveredExitButton);
		DarkExitStyle.Pressed.SetResourceObject(WhiteExitButton);
		ExitButton->SetStyle(DarkExitStyle);
	}
	else
	{
		LightExitStyle.Normal.SetResourceObject(BlackExitButton);
		LightExitStyle.Hovered.SetResourceObject(BlackHoveredExitButton);
		LightExitStyle.Pressed.SetResourceObject(BlackExitButton);
		ExitButton->SetStyle(LightExitStyle);
	}
}

void UMinigameBaseWidget_OM::OnExitButtonClicked()
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is NULL in Minigame Base Widget"));
	}
	Player->SetCurrentPlayMode(EPlayModes::RegularMode);


	Player->bInteractableOpen = false;
}

