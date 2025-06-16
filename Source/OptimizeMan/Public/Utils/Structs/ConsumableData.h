#pragma once

#include "CoreMinimal.h"
#include "ConsumableData.generated.h"

UENUM(Blueprintable)
enum class EConsumableName : uint8
{
	None		UMETA(DisplayName = "None"),
	EnergyDrink UMETA(DisplayName = "EnergyDrink"),
	Nicotine	UMETA(DisplayName = "Nicotine"),
};
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
		Name(EConsumableName::None),
		NameString(""),
		LifeTime(0),
		Price(0)
	{}

	FConsumableType(const EConsumableName InName, const FString& InNameString, const int InLifeTime, const int InPrice) :
		Name(InName),
		NameString(InNameString),
		LifeTime(InLifeTime),
		Price(InPrice)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Consumable)
	EConsumableName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Consumable)
	FString NameString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EConsumableEffectTypes, int> ConsumableEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Price;

	bool operator==(const FConsumableType& Other) const
	{
		return Name == Other.Name;
	}
};
