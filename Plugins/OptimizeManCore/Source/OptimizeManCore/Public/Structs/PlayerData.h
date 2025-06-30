#pragma once
#include "CoreMinimal.h"
#include "PlayerData.generated.h"


UENUM(BlueprintType)
enum class EPlayerEmotionalStates : uint8
{
	VeryBad		UMETA(DisplayName = "VeryBad"),
	Bad			UMETA(DisplayName = "Bad"),
	Normal		UMETA(DisplayName = "Normal"),
	Good		UMETA(DisplayName = "Good"),
	VeryGood	UMETA(DisplayName = "VeryGood"),
};

USTRUCT(BlueprintType)
struct FGamePointsData
{
	GENERATED_USTRUCT_BODY()

	FGamePointsData() :
		GamePoints(0.f)
	{}
	UPROPERTY(BlueprintReadWrite)
	int GamePoints;
	
};
