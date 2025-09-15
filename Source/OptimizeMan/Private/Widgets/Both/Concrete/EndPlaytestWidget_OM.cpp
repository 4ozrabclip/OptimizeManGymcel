// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/EndPlaytestWidget_OM.h"
#include "Components/Button.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Kismet/GameplayStatics.h"

void UEndPlaytestWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (ExitButton)
	{
		if (!ExitButton->OnClicked.IsAlreadyBound(this, &UEndPlaytestWidget_OM::EndPlaytest))
			ExitButton->OnClicked.AddDynamic(this, &UEndPlaytestWidget_OM::EndPlaytest);
	}

	if (EndAnim)
	{
		FWidgetAnimationDynamicEvent EndDelegate;
		EndDelegate.BindDynamic(this, &UEndPlaytestWidget_OM::OnEndAnimFinished);
		BindToAnimationFinished(EndAnim, EndDelegate);

		PlayAnimation(EndAnim);
	}
}

void UEndPlaytestWidget_OM::OnEndAnimFinished()
{

}

void UEndPlaytestWidget_OM::OnGoodbyeAnimFinished()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Levels/MainMenu"));
}

void UEndPlaytestWidget_OM::EndPlaytest()
{
	if (auto* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		GameInstance->ResetGame();
	}
	if (GoodbyeAnim)
	{
		FWidgetAnimationDynamicEvent GoodbyeDelegate;
		GoodbyeDelegate.BindDynamic(this, &UEndPlaytestWidget_OM::OnGoodbyeAnimFinished);
		BindToAnimationFinished(GoodbyeAnim, GoodbyeDelegate);

		PlayAnimation(GoodbyeAnim);
	}
}
