// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Minigames/Concrete/Slots/SlotsMinigame_OM.h"

#include "Components/Button.h"
#include "Widgets/Minigames/Concrete/Slots/SlotReel_OM.h"

USlotsMinigame_OM::USlotsMinigame_OM()
{
	MiniGameType = EMiniGameType::Slots;
}

void USlotsMinigame_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (MiniGameClickButton)
	{
		MiniGameClickButton->OnClicked.Clear();
		MiniGameClickButton->OnClicked.AddDynamic(this, &USlotsMinigame_OM::PlayButton_OnClick);
	}

	if (IncreaseBet_Button && DecreaseBet_Button)
	{
		IncreaseBet_Button->OnClicked.Clear();
		DecreaseBet_Button->OnClicked.Clear();

		IncreaseBet_Button->OnClicked.AddDynamic(this, &USlotsMinigame_OM::IncreaseBet);
		DecreaseBet_Button->OnClicked.AddDynamic(this, &USlotsMinigame_OM::DecreaseBet);
	}
}


/*
 * A higher bet will increase your odds of winning (Your bet is larger than the bet factor).
 * If your bet == betfactor, success + keep your energy
 */
void USlotsMinigame_OM::CalculateChanceOfWin()
{
	constexpr int KeepYourEnergyFactor = -1;
	const int MaxBetFactor = MaxBet + 1;
	const int MinBetFactor = MinBet - 1;
	const int BetFactor = FMath::RandRange(MinBetFactor, MaxBetFactor);
	
	if (CurrentBet > BetFactor)
	{
		CurrentMinigameResult.Result = EMinigameResult::Success;
		CurrentMinigameResult.EnergyFactor = CurrentBet;
	}
	else if (CurrentBet == BetFactor)
	{
		CurrentMinigameResult.Result = EMinigameResult::Success;
		CurrentMinigameResult.EnergyFactor = KeepYourEnergyFactor;
	}
	else
	{
		CurrentMinigameResult.Result = EMinigameResult::Failed;
		CurrentMinigameResult.EnergyFactor = CurrentBet;
	}
}

void USlotsMinigame_OM::OnScrollFinished()
{
	OnMinigameResult.Broadcast(CurrentMinigameResult);
}

void USlotsMinigame_OM::SetWorkoutState(EWorkoutStates NewWorkoutState)
{
	Super::SetWorkoutState(NewWorkoutState);
	switch (CurrentWorkoutState)
	{
	case EWorkoutStates::InExercisePosition:
		{
			if (!MiniGameClickButton->GetIsEnabled())
				MiniGameClickButton->SetIsEnabled(true);
			break;
		}
	default:
		if (MiniGameClickButton->GetIsEnabled())
			MiniGameClickButton->SetIsEnabled(false);
		return;
	}
}

void USlotsMinigame_OM::PlayButton_OnClick()
{
	if (!SlotReel_1 || !SlotReel_2 || !SlotReel_3) return;
	
	CalculateChanceOfWin();
	
	SlotReel_3->OnScrollFinished.Clear();
	SlotReel_3->OnScrollFinished.AddDynamic(this, &USlotsMinigame_OM::OnScrollFinished);

	SlotReel_1->StartScroll(0, 1);
	SlotReel_2->StartScroll(0, 2);
	SlotReel_3->StartScroll(0, 3);
	
}
void USlotsMinigame_OM::ChangeBet(const float InBet)
{
	CurrentBet = FMath::Clamp(CurrentBet + InBet, MinBet, MaxBet);
}