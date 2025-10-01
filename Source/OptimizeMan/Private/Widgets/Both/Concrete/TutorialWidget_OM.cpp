// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/TutorialWidget_OM.h"

#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Kismet/GameplayStatics.h"

void UTutorialWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (!PlayerController)
		PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
}

void UTutorialWidget_OM::OnExitButtonClicked()
{
	Super::OnExitButtonClicked();

	if (TurnTutorialsOff_CheckBox && TurnTutorialsOff_CheckBox->IsChecked())
	{
		if (!GameInstance)
			GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			GameInstance->SetTutorialsOn(false);
		}
	}

	if (InfoSign)
	{
		InfoSign->OnTutorialOff();
	}
}
