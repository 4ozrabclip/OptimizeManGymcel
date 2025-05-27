#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PlayerData.h"
#include "TodoData.generated.h"

UENUM(BlueprintType)
enum ETodoArrayList : uint8
{
	CompleteWorkout = 0,
	BuySomething,
	TalkToAGirl,
	BuySteroids,
	MakeSomeoneLikeYou,
	HitTenSquats,
	StartBulking,
	GetARealGirlfriend
};

USTRUCT()
struct FTodoItem
{
	GENERATED_USTRUCT_BODY()

	FTodoItem()
	: Name(""),
	Level(""),
	CompletedName(""),
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
	FString CompletedName;

	TMap<EPlayerStatTypes, float> StatBuffs;

	UPROPERTY()
	FString Desc;

	UPROPERTY()
	FGameplayTag Tag;
	
	UPROPERTY()
	bool bIsCompleted;

	UPROPERTY()
	int Points;
};
