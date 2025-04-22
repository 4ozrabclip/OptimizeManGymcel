#pragma once

#include "CoreMinimal.h"
#include "SubLevelData.generated.h"

UENUM(BlueprintType)
enum class EGymRooms : uint8
{
	MainRoom UMETA(DisplayName = "MainRoom"),
	Reception UMETA(DisplayName = "Reception"),
	Bathroom UMETA(DisplayName = "Bathroom"),
	ZumbaRoom UMETA(DisplayName = "ZumbaRoom")
};
