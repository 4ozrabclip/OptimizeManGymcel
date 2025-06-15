// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Utils/Structs/SocialData.h"
#include "NpcDataSave.generated.h"

enum class ENpcRelationshipState : uint8;
/**
* USTRUCT(BlueprintType)
struct FNpcRelationshipData
{
	GENERATED_BODY()

	UPROPERTY()
	FName NpcIdentifier;

	UPROPERTY()
	float FriendshipLevel;

	UPROPERTY()
	bool bHasMetPlayer;

	UPROPERTY()
	ENpcRelationshipState RelationshipState;

};
 */

UCLASS()
class OPTIMIZEMAN_API UNpcDataSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FNpcRelationship> NpcRelationships;
	
};
