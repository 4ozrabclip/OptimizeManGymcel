#pragma once

#include "CoreMinimal.h"
#include "AudioTypes.generated.h"

UENUM(BlueprintType)
enum class EAudioTypes : uint8
{
	None,
	VoiceAudio,
	MusicAudio,
	NotificationAudio,
	SfxAudio
};
UENUM(BlueprintType)
enum class EBiquadFilterType : uint8
{
	LowPass = 0,
	HighPass = 1,
	BandPass = 2,
	BandStop = 3,
	AllPass = 4,
	LowShelf = 5,
	HighShelf = 6,
	PeakingEQ = 7
};