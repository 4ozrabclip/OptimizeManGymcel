// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NpcDataSave.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FNpcRelationshipData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasMetPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FriendshipLevel = 0.f;

};
UCLASS()
class OPTIMIZEMAN_API UNpcDataSave : public USaveGame
{
	GENERATED_BODY()

public:
	//UPROPERTY()
	//FNpcRelationshipData NpcRelationship;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasMetPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FriendshipLevel = 0.f;
	
};
