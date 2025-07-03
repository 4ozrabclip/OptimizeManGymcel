// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Animation/PlayerCharacterAnimInstance_OM.h"
#include "Utils/Structs/PlayerData_Gymcel.h"
#include "PlayerCharacterAnimInstance_OMG.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UPlayerCharacterAnimInstance_OMG : public UPlayerCharacterAnimInstance_OM
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable, Category = "Exercises")
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


	UFUNCTION(BlueprintCallable, Category = "ExercisePositions")
	void EnterSquatPosition();

	UFUNCTION(BlueprintCallable, Category = "ExerciseInjuries")
	void SetHasSquatInjury(const bool InHasSquatInjury) { bHasSquatInjury1 = InHasSquatInjury; }

	UFUNCTION(BlueprintCallable, Category = "ExerciseInjuries")
	void SetInjuryLevel(const EInjuryLevel InInjuryLevel) { InjuryLevel = InInjuryLevel; };
	UFUNCTION(BlueprintCallable, Category = "ExerciseInjuries")
	EInjuryLevel GetInjuryLevel() const { return InjuryLevel; };

	UFUNCTION(BlueprintCallable, Category = "ExerciseInjuries")
	void SetHasMinorSquatInjury(const bool InHasSquatInjuryMinor) { bHasSquatInjuryMinor = InHasSquatInjuryMinor; }

	
//Barbell
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void DoSquatRep() { DoRepAnim(bIsSquatting, bIsInSquatPosition, SquatAnimationDuration); }
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void DoCurlRep() { DoRepAnim(bIsCurling, bIsInCurlPosition, CurlAnimationDuration); }
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void DoOverheadPressRep() { DoRepAnim(bIsOverheadPressing, bIsInOverheadPressPosition, OverheadPressAnimationDuration); }
//Dumbell
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void DoLeftCurlRep() { DoRepAnim(bIsLeftCurling, bIsInLeftCurlPosition, LeftCurlAnimationDuration); }
	UFUNCTION(BlueprintCallable, Category = "Exercises")
	void DoRightCurlRep() { DoRepAnim(bIsRightCurling, bIsInRightCurlPosition, RightCurlAnimationDuration); }
	void DoRepAnim(bool& InIsRepping, bool& InIsInPosition, float AnimDuration);

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

	
	void ExitPosition(bool& InIsRepping, bool& InIsInPosition);

private:
	
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

	

	//Injuries
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Injury", meta = (AllowPrivateAccess = "true"))
	EInjuryLevel InjuryLevel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Injury", meta = (AllowPrivateAccess = "true"))
	bool bHasSquatInjury1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Injury", meta = (AllowPrivateAccess = "true"))
	bool bHasSquatInjuryMinor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Surgery", meta = (AllowPrivateAccess = "true"))
	bool bHasJawSurgery;

	
	FTimerHandle RepAnimTimerHandle;
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exercises")
	float SquatAnimationDuration = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exercises")
	float CurlAnimationDuration = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exercises")
	float OverheadPressAnimationDuration = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exercises")
	float LeftCurlAnimationDuration = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exercises")
	float RightCurlAnimationDuration = 4.f;

private:
	FORCEINLINE APlayerCharacter_OM* GetPlayer_Gymcel() const
	{
		return Cast<APlayerCharacter_OM>(Player);
	}

};
