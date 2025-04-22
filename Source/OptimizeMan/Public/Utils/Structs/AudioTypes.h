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
