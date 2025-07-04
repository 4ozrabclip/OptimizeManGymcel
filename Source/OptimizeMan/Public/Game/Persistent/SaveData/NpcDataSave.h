// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/NPC/Abstract/NpcBase_OMG.h"
#include "GameFramework/SaveGame.h"
#include "NpcDataSave.generated.h"

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
