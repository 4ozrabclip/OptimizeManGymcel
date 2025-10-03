#pragma once

#include "CoreMinimal.h"
#include "MinigameData.generated.h"

UENUM()
enum class EMinigameResult : uint8
{
	None	UMETA(DisplayName = "None"),
	Success	UMETA(DisplayName = "Success"),
	Failed	UMETA(DisplayName = "Failed"),
};

UENUM()
enum class EMiniGameType : uint8
{
	None		UMETA(DisplayName = "None"),
	TimingGauge	UMETA(DisplayName = "Timing Gauge"),
	Slots		UMETA(DisplayName = "Slots"),
};

USTRUCT(Blueprintable)
struct FMinigameResultData
{
	GENERATED_BODY()

	FMinigameResultData() :
	EnergyFactor(1.f),
	Result(EMinigameResult::Success)
	{}

	UPROPERTY()
	float EnergyFactor;
	UPROPERTY()
	EMinigameResult Result;
	
	
};


USTRUCT(Blueprintable)
struct FMiniGameData
{
	GENERATED_BODY()
	FMiniGameData() :
	Minigame(EMiniGameType::None),
	bHasPlayed(false)
	{}
	
	UPROPERTY(EditDefaultsOnly)
	EMiniGameType Minigame;

	UPROPERTY(EditDefaultsOnly)
	bool bHasPlayed;
	
};