// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/YouDiedWidget_OM.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UYouDiedWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (TryAgainButton)
	{
		TryAgainButton->OnClicked.Clear();
		TryAgainButton->OnClicked.AddDynamic(this, &UYouDiedWidget_OM::TryAgain);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.Clear();
		ExitButton->OnClicked.AddDynamic(this, &UYouDiedWidget_OM::ExitToMainMenu);
	}

	if (DaysLastedTextBlock)
	{
		if (!GameInstance)
			GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
		if (!GameInstance) return;

		int DayNumber = GameInstance->GetDayNumber();

		FString DaysLastedString = FString::Printf((TEXT("Days Lasted: %d")), DayNumber);

		DaysLastedTextBlock->SetText(FText::FromString(DaysLastedString));
		
	}

	if (YouDiedOpenAnim)
	{
		PlayAnimation(YouDiedOpenAnim);
	}
	
}

void UYouDiedWidget_OM::TryAgain()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	if (!GameInstance) return;

	GameInstance->ResetGame();

	UGameplayStatics::OpenLevel(GetWorld(), FName("Home"));
}

void UYouDiedWidget_OM::ExitToMainMenu()
{
	GameInstance->ResetGame();

	UGameplayStatics::OpenLevel(GetWorld(), FName("EndPlaytest"));
}
