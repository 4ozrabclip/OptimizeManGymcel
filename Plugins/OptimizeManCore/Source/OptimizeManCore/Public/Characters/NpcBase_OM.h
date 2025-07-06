// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "Structs/SocialData.h"

#include "NpcBase_OM.generated.h"


class AGymSpeaker_OM;
class UNPCBodyDeformationsComponent_OM;
class UPointLightComponent;
class UBlackboardComponent;
class UGameAudio_OM;
class UBehaviorTree;
class UNpcBaseAnimInstance_OM;

UCLASS(Abstract, Blueprintable)
class OPTIMIZEMANCORE_API ANpcBase_OM : public ACharacter, public IInteractableInterface_OM
{
	GENERATED_BODY()
public:
	ANpcBase_OM();
protected:
	/** Class Overrides **/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** Shader Helper **/
	UFUNCTION(BlueprintCallable)
	void CheckAndSetDarkMode(bool bDarkMode);
	virtual void Interact_Implementation() override;


	/** Animation / Audio Helper Funcs **/

	
	void Talk(USoundBase* InChatAudio) const;

	void PlayRandomTalkingHelper(TMap<USoundBase*, UAnimMontage*>& InChatMap);
	

	/** State Management Funcs **/


	
	/** Components **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AuraLight")
	UPointLightComponent* AuraLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Talking Audio Component")
	UGameAudio_OM* TalkingAudioComponent;

protected:
	/** Class Cache **/
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TWeakObjectPtr<UNpcBaseAnimInstance_OM> AnimInstance;

	UPROPERTY()
	class APlayerCharacterBase_OM* Player;
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	UPROPERTY()
	APlayerController* PlayerController;



protected:
	
	/** Interaction Propertys **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText InteractableText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractableWidget;

	/** Locomotion Params **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk Speed")
	float WalkSpeed;
	
	/** Identifier **/
	UPROPERTY(EditAnywhere)
	FString NpcID;
	
	/** Level Streaming **/
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Equipment")
	TArray<ANpcBase_OM*> NpcsInLevel;
	
	

	/** AI **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess=true))
	UBehaviorTree* Tree;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta=(AllowPrivateAccess=true))
	UBlackboardComponent* Blackboard;


	/** State Management Propertys **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Social")
	ENpcMood CurrentMood;
	UPROPERTY(EditAnywhere, Category = "NPC Social")
	FNpcRelationship PlayerRelationship;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerRange")
	float MaxPlayerLookAtRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerLookAt")
	FVector DefaultLookAtOffset = FVector::ZeroVector;

	

	
	/** Gameplay Tags **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer ActiveTags;



public:
	/** Getters **/
	UFUNCTION(BlueprintCallable)
	FName GetUniqueNpcID() const { return FName(NpcID); }
	UFUNCTION(BlueprintCallable)
	TArray<ANpcBase_OM*> GetNpcsInLevel() { return NpcsInLevel; };
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	bool GetPlayerCanInteract() const { return bCanInteract; }
	UFUNCTION(BlueprintCallable)
	FVector GetDistanceFromPlayerVector() const { return DistanceFromPlayerVector; };
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	ENpcRelationshipState GetCurrentRelationshipState();
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	ENpcMood GetCurrentMood() const { return CurrentMood;};
	
	float GetFriendshipLevel() const { return PlayerRelationship.FriendshipLevel; }
	bool GetHasMetPlayer() const { return PlayerRelationship.bHasMetPlayer; }
	float GetCurrentTalkTime() const { return CurrentTalkTime; }
	UBehaviorTree* GetBehaviorTree() const { return Tree; };
	bool GetIsOpenForConversation() const { return bOpenForConversationWithOtherNpcs; }
	bool GetIsInConversationWithNpc() const { return bIsInConversationWithOtherNpc; }
	AActor* GetCurrentInteractedItem() const { return CurrentInteractedItem; }
	UNpcBaseAnimInstance_OM* GetAnimInstance();


	/** Setters **/
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	virtual void SetCurrentMood(const ENpcMood InMood) { CurrentMood = InMood;};
	
	void SetIsInConversationWithNpc(const bool bIsInConvo) { bIsInConversationWithOtherNpc = bIsInConvo; };
	void SetIsOpenForConversation(const bool bInOpenForConversation) { bOpenForConversationWithOtherNpcs = bInOpenForConversation; }
	
	virtual void SetFriendshipLevel(const float InAmount, const bool bReset = false);
	void SetHasMetPlayer(const bool InHasMet) { PlayerRelationship.bHasMetPlayer = InHasMet; }

	void SetCurrentInteractedItem(AActor* InItem) { CurrentInteractedItem = InItem; }

	TSoftObjectPtr<ANpcBase_OM> GetCurrentInteractedNpc() const { return CurrentInteractedNpc; }
	void SetCurrentInteractedNpc(ANpcBase_OM* InNpc);


private:
	/** Class Cache **/

protected:
	UPROPERTY()
	FVector SmoothedLookAtLocation;
	UPROPERTY()
	FVector DistanceFromPlayerVector;
	UPROPERTY()
	AActor* CurrentInteractedItem;
	UPROPERTY()
	TSoftObjectPtr<ANpcBase_OM> CurrentInteractedNpc;
	
	
	bool bCanInteract;
	bool bIsInDialogue;

	bool bIsMoving = false;
	bool bLookStateToggleOpen = true;
	bool bOpenForConversationWithOtherNpcs = false;
	bool bIsInConversationWithOtherNpc = false;


	float DistanceFromPlayerValue;
	float CurrentTalkTime = 3.f;



	
};



