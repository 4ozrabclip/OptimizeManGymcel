// Copyright © 2025 4ozStudio. All rights reserved.

#include "Widgets/Home/Concrete/SpeakerWidget_OM.h"

#include "Actors/Other/Bedroom/Concrete/Speaker_OM.h"
#include "Components/Button.h"
#include "Components/WidgetComponent.h"

void USpeakerWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	if (!Speaker) return;
	
	if (PlayButton)
	{
		PlayButton->OnClicked.RemoveAll(Speaker);
		PlayButton->OnClicked.AddDynamic(Speaker, &ASpeaker_OM::PlayNextSong);
	}
	if (StopButton)
	{
		StopButton->OnClicked.RemoveAll(Speaker);
		StopButton->OnClicked.AddDynamic(Speaker, &ASpeaker_OM::StopSong);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.RemoveAll(Speaker);
		ExitButton->OnClicked.AddDynamic(Speaker, &ASpeaker_OM::TurnOffWidget);
	}
}
