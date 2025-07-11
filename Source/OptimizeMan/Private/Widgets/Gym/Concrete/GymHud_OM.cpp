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
	if (bIsDarkMode)
	{
		TutorialText->SetColorAndOpacity(White);
		TutorialText_1->SetColorAndOpacity(White);
	}
	else
	{
		TutorialText->SetColorAndOpacity(Black);
		TutorialText_1->SetColorAndOpacity(Black);
	}
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

