// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/GymHud_OM.h"

#include "Components/ProgressBar.h"

void UGymHud_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	UpdateProgressBars();
	
}

void UGymHud_OM::UpdateProgressBars()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (!GameInstance)
		return;
	
	FPlayerData& PlayerData = GameInstance->GetPlayerData();
	FGymResStats& GymResStats = GameInstance->GetGymResStats();
	
	Focus_PBar->SetPercent(GymResStats.Focus);
	Energy_PBar->SetPercent(GymResStats.Energy);
	Bladder_PBar->SetPercent(GymResStats.Bladder);
}
