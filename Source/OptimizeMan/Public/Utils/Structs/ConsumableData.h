#pragma once

#include "CoreMinimal.h"
#include "ConsumableData.generated.h"


UENUM()
enum class EConsumableEffectTypes : uint8
{
	None		UMETA(DisplayName = "None"),
	Energy		UMETA(DisplayName = "Energy"),
	Focus		UMETA(DisplayName = "Focus"),
	Strength	UMETA(DisplayName = "Strength"),
	Bladder		UMETA(DisplayName = "Bladder"),
};
USTRUCT(BlueprintType)
struct FConsumableType
{
	GENERATED_USTRUCT_BODY()

	FConsumableType() :
		Name(FName("")),
		LifeTime(0)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Consumable)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EConsumableEffectTypes, int> ConsumableEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LifeTime;

	bool operator==(const FConsumableType& Other) const
	{
		return Name == Other.Name;
	}
};
