#pragma once

#include "CoreMinimal.h"
#include "MinigameData.generated.h"

UENUM()
enum class EMinigameResult : uint8
{
	Success	UMETA(DisplayName = "Success"),
	Failed	UMETA(DisplayName = "Failed"),
};