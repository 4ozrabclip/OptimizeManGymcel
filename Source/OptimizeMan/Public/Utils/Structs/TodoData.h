#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PlayerData.h"
#include "TodoData.generated.h"

UENUM(BlueprintType)
enum class ETodoArrayList : uint8
{
	None,
	CompleteWorkout,
	BuySomething,
	TalkToAGirl,
	BuySteroids,
	MakeSomeoneLikeYou,
	HitTenSquats,
	StartBulking,
	GetARealGirlfriend,
	HitFiveDips,
	IncreaseSquatLift,
	TakeColdShower,
	HitFiveSquats
};

USTRUCT()
struct FTodoItem
{
	GENERATED_USTRUCT_BODY()

	FTodoItem()
	: Name(""),
	Level(""),
	Todo(ETodoArrayList::None),
	Desc(""),
	Tag(FGameplayTag::EmptyTag),
	bIsCompleted(false),
	Points(0)
	{}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Level;

	UPROPERTY()
	ETodoArrayList Todo;

	TMap<EPlayerStatTypes, float> StatBuffs;

	UPROPERTY()
	FString Desc;

	UPROPERTY()
	FGameplayTag Tag;
	
	UPROPERTY()
	bool bIsCompleted;

	UPROPERTY()
	int Points;

	bool operator==(const FTodoItem& Other) const
	{
		return Name == Other.Name && Todo == Other.Todo;
	}

};
