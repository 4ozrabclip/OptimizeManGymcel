// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/GymHud_OM.h"


#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGymHud_OM::NativeConstruct()
{
	Super::NativeConstruct();
	PlayerController = Cast<APlayerController_OM>(GetOwningPlayer());
	if (!PlayerController) return;
	Player = Cast<APlayerCharacter_OM>(PlayerController->GetPawn());
	if (!Player) return;
	AbSysComp = Cast<UAbilitySystemComponent_OM>(Player->GetAbilitySystemComponent());
	GymStats = AbSysComp->GetSet<UGymSpecificStats_OM>();
	if (GymStats) bRetrievedGymStats = true;

	DarkModeToggle(GameInstance->GetDarkMode());


	if (GameInstance->GetDayNumber() == 1)
	{
		FTimerHandle PreTutorialTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(PreTutorialTimerHandle, [this]()
		{
			PlayGymHudTutorial();
		}, 2.f, false);

	}
}

void UGymHud_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bRetrievedGymStats)
		UpdateProgressBars();
}

void UGymHud_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	FProgressBarStyle EnergyStyle = Focus_PBar->GetWidgetStyle();
	FProgressBarStyle FocusStyle = Energy_PBar->GetWidgetStyle();
	FProgressBarStyle BladderStyle = Bladder_PBar->GetWidgetStyle();
	if (bIsDarkMode)
	{
		EnergyStyle.BackgroundImage.SetResourceObject(EnergyBorder_White);
		FocusStyle.BackgroundImage.SetResourceObject(FocusBorder_White);
		BladderStyle.BackgroundImage.SetResourceObject(BladderBorder_White);
		Focus_TextBlock->SetColorAndOpacity(White);
		Energy_TextBlock->SetColorAndOpacity(White);
		Bladder_TextBlock->SetColorAndOpacity(White);
	}
	else
	{
		EnergyStyle.BackgroundImage.SetResourceObject(EnergyBorder_Black);
		FocusStyle.BackgroundImage.SetResourceObject(FocusBorder_Black);
		BladderStyle.BackgroundImage.SetResourceObject(BladderBorder_Black);
		Focus_TextBlock->SetColorAndOpacity(Black);
		Energy_TextBlock->SetColorAndOpacity(Black);
		Bladder_TextBlock->SetColorAndOpacity(Black);
	}
	Energy_PBar->SetWidgetStyle(EnergyStyle);
	Focus_PBar->SetWidgetStyle(FocusStyle);
	Bladder_PBar->SetWidgetStyle(BladderStyle);
}

void UGymHud_OM::UpdateProgressBars() const
{
	const float FocusVal = GymStats->GetFocus();
	const float EnergyVal = GymStats->GetEnergy();
	const float BladderVal = GymStats->GetBladder();
	Focus_PBar->SetPercent(FocusVal);
	Energy_PBar->SetPercent(EnergyVal);
	Bladder_PBar->SetPercent(BladderVal);
}

void UGymHud_OM::PlayGymHudTutorial()
{
	Player->GetCharacterMovement()->SetMovementMode(MOVE_None);
	PlayerController->SetIgnoreLookInput(true);
	
	PlayAnimation(GymHudTutorial);

	FTimerHandle TutorialTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TutorialTimerHandle, [this]()
	{
		Player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		PlayerController->SetIgnoreLookInput(false);
		
	}, 7, false);
	
}

