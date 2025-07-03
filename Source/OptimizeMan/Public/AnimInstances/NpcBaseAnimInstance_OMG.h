// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Animation/NpcBaseAnimInstance_OM.h"
#include "NpcBaseAnimInstance_OMG.generated.h"

class APlayerCharacter_OM;
class ANpcBase_OMG;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UNpcBaseAnimInstance_OMG : public UNpcBaseAnimInstance_OM
{
	GENERATED_BODY()
	public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void UpdateIsMoving();


	UFUNCTION()
	void ResetMovementFlag() { bPreviousIsMoving = false; }
	

	void SetIsTalking(const bool InIsTalking);
	void SetIsYelling(const bool InIsYelling) { bIsYelling = InIsYelling; }
	void SetIsExplaining(const bool InIsExplaining) { bIsExplaining = InIsExplaining; }
	void SetIsAffirming(const bool InIsAffirming) {	bIsAffirming = InIsAffirming; }
	void SetIsDisagreeing(const bool InIsDisagreeing) { bIsDisagreeing = InIsDisagreeing; }
	void SetIsDisgusted(const bool InIsDisgusted) { bIsDisgusted = InIsDisgusted; }
	void SetIsLaughing(const bool InIsLaughing) { bIsLaughing = InIsLaughing; }
	void SetIsConfused(const bool InIsConfused) { bIsConfused = InIsConfused; }


	bool GetIsYelling() const { return bIsYelling; }
	bool GetIsExplaining() const { return bIsExplaining; }
	bool GetIsAffirming() const { return bIsAffirming; }
	bool GetIsDisagreeing() const { return bIsDisagreeing; }
	bool GetIsDisgusted() const { return bIsDisgusted; }
	bool GetIsLaughing() const { return bIsLaughing; }
	bool GetIsConfused() const { return bIsConfused; }
	bool GetIsInSquatPosition() const;
	bool GetIsSquatting() const { return bIsSquatting; }
	

	


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


	UFUNCTION(BlueprintCallable, Category = "ExercisePositions")
	void ExitSquatPosition() { ExitPosition(bIsSquatting, bIsInSquatPosition); }
	UFUNCTION(BlueprintCallable, Category = "ExercisePositions")
	void ExitCurlPosition() { ExitPosition(bIsCurling, bIsInCurlPosition); }
	UFUNCTION(BlueprintCallable, Category = "ExercisePositions")
	void ExitOverheadPressPosition() { ExitPosition(bIsOverheadPressing, bIsInOverheadPressPosition);}
	UFUNCTION(BlueprintCallable, Category = "ExercisePositions")
	void ExitLeftCurlPosition() { ExitPosition(bIsLeftCurling, bIsInLeftCurlPosition); }
	UFUNCTION(BlueprintCallable, Category = "ExercisePositions")
	void ExitRightCurlPosition() { ExitPosition(bIsRightCurling, bIsInRightCurlPosition); }

	UFUNCTION()
	void ExitPosition(bool& InIsRepping, bool& InIsInPosition);

protected:
	
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

	
	
	FORCEINLINE APlayerCharacter_OM* GetPlayer_Gymcel() const
	{
		return Cast<APlayerCharacter_OM>(Player);
	}
	/** Refactor this to fit with optimize man core **/
	UPROPERTY()
	ANpcBase_OM* OwningNpc;
	/** ------ **/




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
