#pragma once

#include "CoreMinimal.h"
#include "EventAndGPData.generated.h"


UENUM(BlueprintType)
enum class EDifficultyWaveType : uint8
{
	RestWave UMETA(DisplayName = "RestWave"),
	HardWave UMETA(DisplayName = "HardWave"),
	IntenseWave UMETA(DisplayName = "IntenseWave")
};


UENUM(Blueprintable)
enum class EEventAndGPData : uint8
{
	AnxBathroomSpook UMETA(DisplayName = "Anxious Bathroom Spook"),
};

USTRUCT(BlueprintType)
struct FEventAndGPData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Random Events")
	TMap<EEventAndGPData, bool> RandomEventsWitnessedMap;

	FEventAndGPData()
	{
		RandomEventsWitnessedMap.Add(EEventAndGPData::AnxBathroomSpook, false);
	}
};

