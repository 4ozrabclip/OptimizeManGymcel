// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/NPC/NpcBase_OM.h"
#include "Animation/AnimInstance.h"
#include "NpcBaseAnimInstance_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UNpcBaseAnimInstance_OM : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void UpdateIsMoving();

	void SetIsTalking(const bool InIsTalking);
	void SetIsYelling(const bool InIsYelling) { bIsYelling = InIsYelling; }
	void SetIsExplaining(const bool InIsExplaining) { bIsExplaining = InIsExplaining; }
	void SetIsAffirming(const bool InIsAffirming) {	bIsAffirming = InIsAffirming; }
	void SetIsDisagreeing(const bool InIsDisagreeing) { bIsDisagreeing = InIsDisagreeing; }
	void SetIsDisgusted(const bool InIsDisgusted) { bIsDisgusted = InIsDisgusted; }
	void SetIsLaughing(const bool InIsLaughing) { bIsLaughing = InIsLaughing; }
	void SetIsConfused(const bool InIsConfused) { bIsConfused = InIsConfused; }

	bool GetIsTalking() const { return bIsTalking; }
	bool GetIsYelling() const { return bIsYelling; }
	bool GetIsExplaining() const { return bIsExplaining; }
	bool GetIsAffirming() const { return bIsAffirming; }
	bool GetIsDisagreeing() const { return bIsDisagreeing; }
	bool GetIsDisgusted() const { return bIsDisgusted; }
	bool GetIsLaughing() const { return bIsLaughing; }
	bool GetIsConfused() const { return bIsConfused; }
	
	UPROPERTY()
	class APlayerCharacter_OM* Player;


protected:
	//Locomotion
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsWalking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LookAt", meta = (AllowPrivateAccess = "true"))
	FVector LookAtLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsTalking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsExplaining;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsAffirming;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsYelling;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsDisagreeing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsDisgusted;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsLaughing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsConfused;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion", meta = (AllowPrivateAccess = "true"))
	bool bIsMoving;
	
	
	UPROPERTY()
	class ANpcBase_OM* OwningNpc;

	float MaxPlayerLookAtRange = 500.f;
	FVector DefaultLookAtOffset = FVector::ZeroVector;

private:
	int RandomIndex = 0;

	float AnimationLength = 0;

};

