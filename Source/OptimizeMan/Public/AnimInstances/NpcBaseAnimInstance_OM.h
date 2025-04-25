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


	UFUNCTION()
	void ResetMovementFlag() { bPreviousIsMoving = false; }
	
	void SetPlayer(APlayerCharacter_OM* InPlayerCharacter) { Player = InPlayerCharacter; }
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
	bool GetIsInSquatPosition() const;

	


	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void SetIsInSquatPosition(const bool InIsInSquatPosition);
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void SetIsInCurlPosition(bool InIsInCurlPosition);
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void SetIsInOverheadPressPosition(bool InIsInOverheadPressPosition);
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void SetIsInLeftCurlPosition(bool InIsInLeftCurlPosition);
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void SetIsInRightCurlPosition(bool InIsInRightCurlPosition);
	
	UFUNCTION()
	void DoRepAnim(bool& InIsRepping, bool& InIsInPosition, float AnimDuration);
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void DoSquatRep() { DoRepAnim(bIsSquatting, bIsInSquatPosition, SquatAnimationDuration); }
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void DoCurlRep() { DoRepAnim(bIsCurling, bIsInCurlPosition, CurlAnimationDuration); }

	UFUNCTION()
	void ExitPosition(bool& InIsRepping, bool& InIsInPosition);

protected:
	UPROPERTY()
	APlayerCharacter_OM* Player;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsInSquatPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsInCurlPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsInOverheadPressPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsInLeftCurlPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsInRightCurlPosition;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsSquatting;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsCurling;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsOverheadPressing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsLeftCurling;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Exercises", meta = (AllowPrivateAccess = "true"))
	bool bIsRightCurling;

	
	
	
	UPROPERTY()
	class ANpcBase_OM* OwningNpc;



private:
	FTimerHandle RepAnimTimerHandle;
	FTimerHandle MovementDecayTimerHandle;
	bool bPreviousIsMoving;
	int RandomIndex = 0;
	float MaxPlayerLookAtRange = 500.f;
	float AnimationLength = 0;
	FVector DefaultLookAtOffset = FVector::ZeroVector;
	float SquatAnimationDuration = 4.f;
	float CurlAnimationDuration = 4.f;
	float OverheadPressAnimationDuration = 4.f;
	float LeftCurlAnimationDuration = 4.f;
	float RightCurlAnimationDuration = 4.f;
	
};

