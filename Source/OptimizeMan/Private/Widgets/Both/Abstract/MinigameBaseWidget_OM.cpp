// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"

void UMinigameBaseWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	


	if (!PlayerController)
		PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		if (!PlayerController->OnWidgetExited.IsAlreadyBound(this, &UMinigameBaseWidget_OM::OnExitButtonClicked))
			PlayerController->OnWidgetExited.AddDynamic(this, &UMinigameBaseWidget_OM::OnExitButtonClicked);
	}

	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		if (!Player->OnPauseMenuToggled.IsAlreadyBound(this, &UMinigameBaseWidget_OM::PauseMenuToggled))
			Player->OnPauseMenuToggled.AddDynamic(this, &UMinigameBaseWidget_OM::PauseMenuToggled);
	}
	
	if (OpenSound)
	{
		if (auto* pc = Cast<APlayerControllerBase_OM>(GetOwningPlayer()))
		{
			pc->PlayUISound(OpenSound);
		}
	}

}

void UMinigameBaseWidget_OM::PauseMenuToggled(bool bIsOpen)
{
	OnExitButtonClicked();
}

void UMinigameBaseWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	

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