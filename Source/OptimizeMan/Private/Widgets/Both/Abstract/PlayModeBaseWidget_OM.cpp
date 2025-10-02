// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Abstract/PlayModeBaseWidget_OM.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/PlayerController/WidgetManagementComponent_OM.h"

void UPlayModeBaseWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!PlayerController)
		PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		if (auto* wm = PlayerController->GetWidgetManagementComponent())
		{
			if (!wm->OnWidgetExited.IsAlreadyBound(this, &UPlayModeBaseWidget_OM::OnExitButtonClicked))
				wm->OnWidgetExited.AddDynamic(this, &UPlayModeBaseWidget_OM::OnExitButtonClicked);
		}
	}

	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		if (!Player->OnPauseMenuToggled.IsAlreadyBound(this, &UPlayModeBaseWidget_OM::PauseMenuToggled))
			Player->OnPauseMenuToggled.AddDynamic(this, &UPlayModeBaseWidget_OM::PauseMenuToggled);
	}
	
	if (OpenSound)
	{
		if (auto* pc = Cast<APlayerControllerBase_OM>(GetOwningPlayer()))
		{
			pc->PlayUISound(OpenSound);
		}
	}

}

void UPlayModeBaseWidget_OM::PauseMenuToggled(bool bIsOpen)
{
	OnExitButtonClicked();
}

void UPlayModeBaseWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	

}

void UPlayModeBaseWidget_OM::OnExitButtonClicked()
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is NULL in Minigame Base Widget"));
	}
	Player->SetCurrentPlayMode(EPlayModes::RegularMode);



	Player->bInteractableOpen = false;
}