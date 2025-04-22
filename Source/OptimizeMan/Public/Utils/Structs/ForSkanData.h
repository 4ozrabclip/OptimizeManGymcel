#pragma once

#include "CoreMinimal.h"
#include "ForSkanData.generated.h"

UENUM()
enum class EForSkanType : uint8
{
	Good,
	Bad,
	Mixed,
	Crazy
};

USTRUCT()
struct FForSkanData
{
	GENERATED_USTRUCT_BODY()
	static TMap<EForSkanType, TArray<FString>> ForSkanPotentialStrings;
};
