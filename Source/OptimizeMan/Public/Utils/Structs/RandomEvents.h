#pragma once

#include "CoreMinimal.h"
#include "RandomEvents.generated.h"

UENUM(Blueprintable)
enum class ERandomEvents : uint8
{
	AnxBathroomSpook UMETA(DisplayName = "Anxious Bathroom Spook"),
};

USTRUCT(BlueprintType)
struct FRandomEvents
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Random Events")
	TMap<ERandomEvents, bool> RandomEventsWitnessedMap;

	FRandomEvents()
	{
		RandomEventsWitnessedMap.Add(ERandomEvents::AnxBathroomSpook, false);
	}
};