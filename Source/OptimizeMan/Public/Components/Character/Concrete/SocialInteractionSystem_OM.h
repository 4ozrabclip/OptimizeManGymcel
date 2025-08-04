// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "Components/Character/Abstract/CharacterComponentBase_OM.h"
#include "Utils/Structs/PlayerData.h"
#include "SocialInteractionSystem_OM.generated.h"

/**
 * 
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API USocialInteractionSystem_OM : public UCharacterComponentBase_OM
{
	GENERATED_BODY()
public:
	USocialInteractionSystem_OM();
protected:
	/** Class Overrides **/
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	virtual void ManageSideEffects(ETemporaryEmotionalStates InState) override;
public:
	/** Inits **/
	void InitConversation();

	/** Processing **/
	void ProcessConversationData();
	void ProcessFriendshipLevel();
	void CheckForSocialAchievements();
	void ManageInteractionLogic(ESocialType InSocialType);

	/** Exit Convo **/
	void LeaveConversationOnWalkingOff();
	void LeaveConversation();

	/** Save/Load **/
	void SaveNpcFriendshipData();
	void LoadNpcFriendshipData();
	
	/** Getters **/
	float GetEnemyThreshold() const { return EnemyThreshold; }
	float GetFriendThreshold() const { return FriendThreshold; }

	/** Setters/Adders **/
	virtual void AddFocus(const float InFocus) override;


	/** Delegate Events **/
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Events)
//	FOnSocialEntered OnSocialEntered;

protected:
	/** Cache **/
	UPROPERTY()
	class ANpcBase_OM* CurrentInteractedNpc;
	UPROPERTY()
	class UNpcBaseAnimInstance_OM* NpcAnimInstance;

	/** State Management **/
	UPROPERTY()
	ENpcMood CurrentNpcMood;
	

	/** Todos **/
	TArray<FGameplayTag> CompletedTodosCheckList;

private:
	FRotator TargetRotation;
	bool bShouldRotateToNPC = false;

	
	float CharismaFactor = 0.5;
	
	const float NeutralThreshold = 0.f;
	UPROPERTY(EditAnywhere, Category = "Relationship Threshold")
	float EnemyThreshold = -0.5;
	UPROPERTY(EditAnywhere, Category = "Relationship Threshold")
	float HateThreshold = -0.9f;
	UPROPERTY(EditAnywhere, Category = "Relationship Threshold")
	float FriendThreshold = 0.5;
	
};
