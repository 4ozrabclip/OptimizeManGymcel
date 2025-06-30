#pragma once

#include "CoreMinimal.h"
#include "Structs/PlayModes.h"
#include "PlayModes_Gymcel.generated.h"

UENUM(BlueprintType)
enum class EPlayModes : uint8
{
	RegularMode,
	MirrorMode,
	WorkoutMode,
	SocialMode,
	LaptopMode,
	TodoMode,
	WakeUpMode,
	PauseMode,
	ShelfMode,
	CalenderMode,
	MuscleViewMode
};
