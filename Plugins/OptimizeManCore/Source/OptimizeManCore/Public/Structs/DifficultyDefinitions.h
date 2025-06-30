#pragma once

#include "CoreMinimal.h"
#include "DifficultyDefinitions.generated.h"

UENUM(BlueprintType)
enum class EDifficultyWaveType : uint8
{
	RestWave UMETA(DisplayName = "RestWave"),
	HardWave UMETA(DisplayName = "HardWave"),
	IntenseWave UMETA(DisplayName = "IntenseWave")
};
