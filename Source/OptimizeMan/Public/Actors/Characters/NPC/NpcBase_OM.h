// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OptimizeMan/Public/Interfaces/InteractableInterface_OM.h"
#include "GameFramework/Character.h"
#include "Utils/NpcDataSave.h"
#include "Utils/Structs/NpcStates.h"
#include "Utils/Structs/SocialData.h"
#include "NpcBase_OM.generated.h"


class UBlackboardComponent;
class UGameAudio_OM;
class UBehaviorTree;
class UNpcBaseAnimInstance_OM;

UCLASS(Blueprintable)
class OPTIMIZEMAN_API ANpcBase_OM : public ACharacter, public IInteractableInterface_OM
{
	GENERATED_BODY()
public:
	ANpcBase_OM();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;

	//UFUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "NPC Dialogue")
	virtual void StartDialogue();
	UFUNCTION(BlueprintCallable, Category = "NPC Dialogue")
	virtual void EndDialog();
	UFUNCTION(BlueprintCallable)
	void SayHello() { PlayRandomTalkingHelper(FriendlyHello); }
	void Talk(USoundBase* InChatAudio) const;
	
	
	void ToggleNpcLookStates();
	FVector LookAtLocation(const float DeltaTime);
	void PlayRandomTalkingAnimForMood();
	void PlayRandomTalkingHelper(TMap<USoundBase*, UAnimMontage*>& InChatMap);


	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
	ENpcState CurrentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
	ENpcLookStates CurrentLookState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Social")
	ENpcMood CurrentMood;
	UPROPERTY(EditAnywhere, Category = "NPC Social")
	FNpcRelationship PlayerRelationship;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerLookAt")
	FVector DefaultLookAtOffset = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerRange")
	float MaxPlayerLookAtRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText InteractableText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractableWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class AGymSpeaker_OM* GymSpeaker;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk Speed")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	TArray<TSoftObjectPtr<class AExerciseEquipment_OM>> EquipmentInLevel;


	



protected: //Audio Stuff
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

protected: //Anim stuff
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UNpcBaseAnimInstance_OM* AnimInstance;

protected: //AI stuff
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess=true))
	UBehaviorTree* Tree;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta=(AllowPrivateAccess=true))
	UBlackboardComponent* Blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta=(AllowPrivateAccess=true))
	ENpcState ExitDialogueState;

protected: //Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AuraLight")
	class UPointLightComponent* AuraLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UGameAudio_OM* TalkingAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deformation")
	class UNPCBodyDeformationsComponent_OM* DeformationComponent;


protected: // Gameplay Tags
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer ActiveTags;

public: //Getters and Setters

	UFUNCTION()
	TArray<TSoftObjectPtr<AExerciseEquipment_OM>> GetEquipmentInLevel() { return EquipmentInLevel; };
	
	UFUNCTION(Category = "NPC Social")
	float GetFriendshipLevel() const { return PlayerRelationship.FriendshipLevel; };
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	bool GetPlayerCanInteract() const { return bCanInteract; }
	UFUNCTION(BlueprintCallable)
	FVector GetDistanceFromPlayerVector() const { return DistanceFromPlayerVector; };
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	ENpcRelationshipState GetCurrentRelationshipState();
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	ENpcMood GetCurrentMood() const { return CurrentMood;};
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	bool GetHasMetPlayer() const { return PlayerRelationship.bHasMetPlayer; };
	UFUNCTION()
	float GetCurrentTalkTime() const { return CurrentTalkTime; }
	UFUNCTION()
	UBehaviorTree* GetBehaviorTree() const { return Tree; };
	UFUNCTION()
	UNpcBaseAnimInstance_OM* GetAnimInstance();

	
	UFUNCTION(BlueprintCallable, Category = "NPC Social")
	virtual void SetCurrentMood(ENpcMood InMood) { CurrentMood = InMood;};
	UFUNCTION(BlueprintCallable, Category = "NPC States")
	void SetCurrentState(const ENpcState InState);
	UFUNCTION()
	virtual void SetFriendshipLevel(const float InAmount, const bool bReset = false);
	UFUNCTION()
	void SetHasMetPlayer(const bool InHasMet) { PlayerRelationship.bHasMetPlayer = InHasMet; }

private:
	UPROPERTY()
	class APlayerCharacter_OM* Player;
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	FVector SmoothedLookAtLocation;
	FVector DistanceFromPlayerVector;
	
	bool bCanInteract;
	bool bIsInDialogue;
	bool bHasMogFace = false;
	bool bIsMoving = false;
	bool bLookStateToggleOpen = true;

	
	float DistanceFromPlayerValue;
	float CurrentTalkTime = 3.f;
	float CurrentMusicPitch = 0.f;
	
	int CurrentBiquadFrequency = 20000;
	
};



