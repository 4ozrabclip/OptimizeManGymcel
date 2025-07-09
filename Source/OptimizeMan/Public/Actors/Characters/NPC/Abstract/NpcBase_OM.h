// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OptimizeMan/Public/Interfaces/InteractableInterface_OM.h"
#include "GameFramework/Character.h"
#include "Game/Persistent/SaveData/NpcDataSave.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/NpcStates.h"
#include "Utils/Structs/SocialData.h"
#include "NpcBase_OM.generated.h"


class AGymSpeaker_OM;
class UNPCBodyDeformationsComponent_OM;
class UPointLightComponent;
class UBlackboardComponent;
class UGameAudio_OM;
class UBehaviorTree;
class UNpcBaseAnimInstance_OM;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNpcStateChanged);

UCLASS(Abstract, Blueprintable)
class OPTIMIZEMAN_API ANpcBase_OM : public ACharacter, public IInteractableInterface_OM
{
	GENERATED_BODY()
public:
	ANpcBase_OM();
	virtual void Interact_Implementation() override;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:
	void ToggleNpcLookStates();
	void Talk(USoundBase* InChatAudio) const;
	void PlayRandomTalkingAnimForMood();
	FVector LookAtLocation(const float DeltaTime);
	
	//Helpers
	void PlayRandomTalkingHelper(TMap<USoundBase*, UAnimMontage*>& InChatMap);


	//UFUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "NPC Dialogue")
	virtual void StartDialogue();
	UFUNCTION(BlueprintCallable, Category = "NPC Dialogue")
	virtual void EndDialog();
	UFUNCTION(BlueprintCallable)
	void SayHello() { PlayRandomTalkingHelper(FriendlyHello); }
	UFUNCTION(BlueprintCallable)
	virtual void DarkModeToggle(const bool bIsDarkMode);


	//Delegates
	//UPROPERTY(BlueprintAssignable, Category = "Events")
	//FOnNpcStateChanged OnNpcStateChanged;

protected:
	
	//Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText InteractableText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractableWidget;

	//Locomation Params
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk Speed")
	float WalkSpeed;
	
	//Unique ID
	UPROPERTY(EditAnywhere)
	FString NpcID;
	
	//Level Streaming
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	TArray<TSoftObjectPtr<class AExerciseEquipment_OM>> EquipmentInLevel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	TArray<TSoftObjectPtr<ANpcBase_OM>> NpcsInLevel;
	
	
	//Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	AGymSpeaker_OM* GymSpeaker;

	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AuraLight")
	UPointLightComponent* AuraLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UGameAudio_OM* TalkingAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deformation")
	UNPCBodyDeformationsComponent_OM* DeformationComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UNpcBaseAnimInstance_OM* AnimInstance;

	//AI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess=true))
	UBehaviorTree* Tree;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta=(AllowPrivateAccess=true))
	UBlackboardComponent* Blackboard;


	//States
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
	ENpcState CurrentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
	ENpcLookStates CurrentLookState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta=(AllowPrivateAccess=true))
	ENpcState ExitDialogueState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Social")
	ENpcMood CurrentMood;
	UPROPERTY(EditAnywhere, Category = "NPC Social")
	FNpcRelationship PlayerRelationship;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
	EExerciseType CurrentExerciseType;

	//LookState
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerRange")
	float MaxPlayerLookAtRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerLookAt")
	FVector DefaultLookAtOffset = FVector::ZeroVector;

	
	// Gameplay Tags
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer ActiveTags;



	// Audio And Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conversation")
	TMap<USoundBase*, UAnimMontage*> AngryChats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conversation")
	TMap<USoundBase*, UAnimMontage*> ExplainingChats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conversation")
	TMap<USoundBase*, UAnimMontage*> AffirmingChats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conversation")
	TMap<USoundBase*, UAnimMontage*> DisagreeingChats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conversation")
	TMap<USoundBase*, UAnimMontage*> LaughingChats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conversation")
	TMap<USoundBase*, UAnimMontage*> ConfusedChats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conversation")
	TMap<USoundBase*, UAnimMontage*> DisgustedChats;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Conversation")
	TMap<USoundBase*, UAnimMontage*> FriendlyHello;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundBase*> NeutralTalkingSounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundBase*> HappyTalkingSounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundBase*> AngryTalkingSounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundBase*> RandyTalkingSounds;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TArray<USoundBase*> HelloTalking_Sounds;

public:
	//GETTERS AND SETTERS
	UFUNCTION(BlueprintCallable)
	FName GetUniqueNpcID() const { return FName(NpcID); }
	UFUNCTION(BlueprintCallable)
	TArray<TSoftObjectPtr<AExerciseEquipment_OM>> GetEquipmentInLevel() { return EquipmentInLevel; };
	UFUNCTION(BlueprintCallable)
	TArray<TSoftObjectPtr<ANpcBase_OM>> GetNpcsInLevel() { return NpcsInLevel; };
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	bool GetPlayerCanInteract() const { return bCanInteract; }
	UFUNCTION(BlueprintCallable)
	FVector GetDistanceFromPlayerVector() const { return DistanceFromPlayerVector; };
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	ENpcRelationshipState GetCurrentRelationshipState();
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	ENpcMood GetCurrentMood() const { return CurrentMood;};
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	virtual void SetCurrentMood(ENpcMood InMood) { CurrentMood = InMood;};
	UFUNCTION(BlueprintCallable, Category = "NPC States")
	void SetCurrentState(const ENpcState InState);
	UFUNCTION(BlueprintCallable, Category = "NPC States")
	ENpcState GetCurrentState() const { return CurrentState; };
	float GetFriendshipLevel() const { return PlayerRelationship.FriendshipLevel; }
	bool GetHasMetPlayer() const { return PlayerRelationship.bHasMetPlayer; }
	float GetCurrentTalkTime() const { return CurrentTalkTime; }
	UBehaviorTree* GetBehaviorTree() const { return Tree; };
	UNpcBaseAnimInstance_OM* GetAnimInstance();
	EExerciseType GetCurrentExerciseType() const { return CurrentExerciseType; };
	bool GetIsOpenForConversation() const { return bOpenForConversationWithOtherNpcs; }
	bool GetIsInConversationWithNpc() const { return bIsInConversationWithOtherNpc;}

	void SetIsInConversationWithNpc(const bool bIsInConvo) { bIsInConversationWithOtherNpc = bIsInConvo; };
	void SetIsOpenForConversation(const bool bInOpenForConversation) { bOpenForConversationWithOtherNpcs = bInOpenForConversation; }
	
	void SetCurrentExerciseType(const EExerciseType InExerciseType) { CurrentExerciseType = InExerciseType; }
	virtual void SetFriendshipLevel(const float InAmount, const bool bReset = false);
	void SetHasMetPlayer(const bool InHasMet) { PlayerRelationship.bHasMetPlayer = InHasMet; }
	AActor* GetCurrentInteractedItem() const { return CurrentInteractedItem; }
	void SetCurrentInteractedItem(AActor* InItem) { CurrentInteractedItem = InItem; }

	TSoftObjectPtr<ANpcBase_OM> GetCurrentInteractedNpc() const { return CurrentInteractedNpc; }
	void SetCurrentInteractedNpc(ANpcBase_OM* InNpc);


protected:
	UPROPERTY()
	class APlayerCharacter_OM* Player;
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	FVector SmoothedLookAtLocation;
	UPROPERTY()
	FVector DistanceFromPlayerVector;
	UPROPERTY()
	AActor* CurrentInteractedItem;
	UPROPERTY()
	TSoftObjectPtr<ANpcBase_OM> CurrentInteractedNpc;

private:
	
	bool bCanInteract;
	bool bIsInDialogue;
	bool bHasMogFace = false;
	bool bIsMoving = false;
	bool bLookStateToggleOpen = true;
	bool bOpenForConversationWithOtherNpcs = false;
	bool bIsInConversationWithOtherNpc = false;

	int CurrentBiquadFrequency = 20000;
	
	float DistanceFromPlayerValue;
	float CurrentTalkTime = 3.f;
	float CurrentMusicPitch = 0.f;


	
};



