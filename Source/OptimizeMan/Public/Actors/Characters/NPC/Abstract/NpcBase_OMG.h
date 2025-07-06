// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/NpcStates.h"
#include "Characters/NpcBase_OM.h"
#include "Game/Persistent/GameInstance_OMG.h"
#include "NpcBase_OMG.generated.h"

UCLASS(Abstract)
class OPTIMIZEMAN_API ANpcBase_OMG : public ANpcBase_OM
{
	GENERATED_BODY()
public:
	ANpcBase_OMG();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;
public:
	/** Animation / Audio Helper Funcs **/
	UFUNCTION(BlueprintCallable, Category = "NPC Dialogue")
	virtual void StartDialogue();
	UFUNCTION(BlueprintCallable, Category = "NPC Dialogue")
	virtual void EndDialog();
	UFUNCTION(BlueprintCallable)
	void SayHello() { PlayRandomTalkingHelper(FriendlyHello); }
	void PlayRandomTalkingAnimForMood();

	/** State Management Funcs **/
	virtual FVector LookAtLocation(const float DeltaTime);
	virtual void ToggleNpcLookStates();
	
	/** Components **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deformation")
	UNPCBodyDeformationsComponent_OM* DeformationComponent;
	
private:
	/** Class Cache **/
	


public:

protected:
	//Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	AGymSpeaker_OM* GymSpeaker;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	TArray<TSoftObjectPtr<class AExerciseEquipment_OM>> EquipmentInLevel;

	/** State Management Propertys **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
	EExerciseType CurrentExerciseType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
	ENpcState CurrentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
	ENpcLookStates CurrentLookState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta=(AllowPrivateAccess=true))
	ENpcState ExitDialogueState;
	
	/** Audio And Animation **/
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
	/** Setters **/
	UFUNCTION(BlueprintCallable, Category = "NPC States")
	void SetCurrentState(const ENpcState InState);
	void SetCurrentExerciseType(const EExerciseType InExerciseType) { CurrentExerciseType = InExerciseType; }


	/** Getters **/
	UFUNCTION(BlueprintCallable, Category = "NPC States")
	ENpcState GetCurrentState() const { return CurrentState; };
	UFUNCTION(BlueprintCallable)
	TArray<TSoftObjectPtr<AExerciseEquipment_OM>> GetEquipmentInLevel() { return EquipmentInLevel; };
	EExerciseType GetCurrentExerciseType() const { return CurrentExerciseType; };

private:
	

protected:
	bool bHasMogFace = false;
	int CurrentBiquadFrequency = 20000;
	float CurrentMusicPitch = 0.f;
	
};
