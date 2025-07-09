#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "TodoData.generated.h"


USTRUCT(Blueprintable)
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

	TMap<FName, float> StatBuffs;

	UPROPERTY()
	FString Desc;

	UPROPERTY()
	FGameplayTag Tag;
	
	UPROPERTY()
	bool bIsCompleted;

	UPROPERTY()
	int Points;
};
