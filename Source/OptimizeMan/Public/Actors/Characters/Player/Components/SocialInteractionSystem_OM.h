// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/NPC/NpcBase_OM.h"
#include "Actors/Characters/Components/CharacterComponentBase_OM.h"
#include "Utils/Structs/PlayerData.h"
#include "SocialInteractionSystem_OM.generated.h"

/**
 * 
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API USocialInteractionSystem_OM : public UCharacterComponentBase_OM
{
	GENERATED_BODY()

	USocialInteractionSystem_OM();

public:
	virtual void BeginPlay() override;
	void InitConversation();
	void SaveNpcFriendshipData();
	void LoadNpcFriendshipData();
	void ProcessConversationData();
	void ProcessFriendshipLevel();
	void CheckForSocialAchievements();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void LeaveConversationOnWalkingOff();

	void ManageInteractionLogic(ESocialType InSocialType);
	void LeaveConversation();


	float GetEnemyThreshold() const { return EnemyThreshold; }
	float GetFriendThreshold() const { return FriendThreshold; }

protected:
	UPROPERTY()
	class ANpcBase_OM* CurrentInteractedNpc;

	UPROPERTY()
	ENpcMood CurrentNpcMood;

	UPROPERTY()
	FPlayerData PlayerData;

	UPROPERTY()
	class UNpcBaseAnimInstance_OM* NpcAnimInstance;

	TArray<FGameplayTag> CompletedTodosCheckList;

private:

	float CharismaFactor = 0.5;
	
	const float NeutralThreshold = 0.f;
	UPROPERTY(EditAnywhere, Category = "Relationship Threshold")
	float EnemyThreshold = -0.5;
	UPROPERTY(EditAnywhere, Category = "Relationship Threshold")
	float HateThreshold = -0.9f;
	UPROPERTY(EditAnywhere, Category = "Relationship Threshold")
	float FriendThreshold = 0.5;
	
};
