#pragma once

#include "CoreMinimal.h"
#include "Structs/SocialData.h"
#include "SocialData_Gymcel.generated.h"

UENUM(BlueprintType)
enum class ESocialType : uint8
{
	Neutral		UMETA(DisplayName = "Neutral"),
	Friendly	UMETA(DisplayName = "Friendly"),
	Randy		UMETA(DisplayName = "Randy"),
	Angry		UMETA(DisplayName = "Angry"),
	DontListen	UMETA(DisplayName = "NoListen"),
	Funny		UMETA(DisplayName = "Funny"),
	Hilarious	UMETA(DisplayName = "Hilarious"),
	WeirdJoke	UMETA(DisplayName = "Weird Joke"),
	Awkward		UMETA(DisplayName = "Awkward"),
	Flexing		UMETA(DisplayName = "Flexing")
};