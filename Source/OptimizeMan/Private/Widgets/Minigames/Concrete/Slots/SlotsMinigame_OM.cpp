// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Minigames/Concrete/Slots/SlotsMinigame_OM.h"

#include "Components/Button.h"
#include "Widgets/Minigames/Concrete/Slots/SlotReel_OM.h"

void USlotsMinigame_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		PlayButton->OnClicked.Clear();
		PlayButton->OnClicked.AddDynamic(this, &USlotsMinigame_OM::PlayButton_OnClick);
	}

	
}

void USlotsMinigame_OM::PlayButton_OnClick()
{
	if (!SlotReel_1 || !SlotReel_2 || !SlotReel_3) return;
	
	SlotReel_3->OnScrollFinished.Clear();
	SlotReel_3->OnScrollFinished.AddDynamic(this, &USlotsMinigame_OM::OnScrollFinished);

	SlotReel_1->StartScroll(0, 1);
	SlotReel_2->StartScroll(0, 2);
	SlotReel_3->StartScroll(0, 3);


}

void USlotsMinigame_OM::OnScrollFinished()
{
	OnMinigameResult.Broadcast(EMinigameResult::Success);
}
