#pragma once

#include "CoreMinimal.h"
#include "NpcStates.generated.h"

UENUM()
enum class ENpcLookStates : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	LookingAtPlayer UMETA(DisplayName = "LookingAtPlayer"),
	IgnoringPlayer UMETA(DisplayName = "IgnoringPlayer")
};

UENUM(BlueprintType)
enum class ENpcState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walking UMETA(DisplayName = "Walking"),
	Talking UMETA(DisplayName = "Talking"),
	GoingToWorkout UMETA(DisplayName = "GoingToWorkout"),
	WorkingOut UMETA(DisplayName = "WorkingOut")
};

