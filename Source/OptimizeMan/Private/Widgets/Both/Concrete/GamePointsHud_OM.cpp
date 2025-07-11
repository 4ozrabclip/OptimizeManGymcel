// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/GamePointsHud_OM.h"

#include "Components/TextBlock.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

void UGamePointsHud_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	if (GameInstance)
	{
		if (!TodoManager)
			TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
		if (TodoManager)
			TodoManager->OnPointsChanged.AddDynamic(this, &UGamePointsHud_OM::UpdateGamePoints);
	}
	
	
	UpdateGamePoints();
}

void UGamePointsHud_OM::UpdateGamePoints()
{
	if (!Points_TextBlock) return;

	int CurrentGamePoints = 9999;

	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		CurrentGamePoints = GameInstance->GetGamePoints();
	}

	FString GamePointsString = FString::FromInt(CurrentGamePoints);
	
	Points_TextBlock->SetText(FText::FromString(GamePointsString));
	
}

void UGamePointsHud_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);

	if (bIsDarkMode)
	{
		Points_TextBlock->SetColorAndOpacity(White);
	}
	else
	{
		Points_TextBlock->SetColorAndOpacity(Black);
	}
}
