// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/PlayerData.h"
#include "Utils/Structs/PlayModes.h"
#include "PlayerCharacterAnimInstance_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UPlayerCharacterAnimInstance_OM : public UAnimInstance
{
	GENERATED_BODY()

public:
	/** Overrides **/
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
	void SetHasInjury(const bool InHasInjury) { bHasInjury = InHasInjury; }

	UFUNCTION(BlueprintCallable, Category = "ExerciseInjuries")
	void SetInjuryLevel(const EInjuryLevel InInjuryLevel) { InjuryLevel = InInjuryLevel; };
	UFUNCTION(BlueprintCallable, Category = "ExerciseInjuries")
	EInjuryLevel GetInjuryLevel() const { return InjuryLevel; };


	
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

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	class APlayerCharacter_OM* Player;

	//Locomotion
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsWalking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsJumping;
	


	//Exercises


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
	bool bHasInjury;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Surgery", meta = (AllowPrivateAccess = "true"))
	bool bHasJawSurgery;

	
	FTimerHandle RepAnimTimerHandle;
	


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




	/** Cache **/
	UPROPERTY(BlueprintReadOnly, Category = "State Management")
	EPlayModes CurrentPlayMode = EPlayModes::RegularMode;

	UPROPERTY(BlueprintReadOnly, Category = "State Management")
	EExerciseType CurrentExerciseType = EExerciseType::None;
	UPROPERTY(BlueprintReadOnly, Category = "State Management")
	EWorkoutStates CurrentWorkoutState = EWorkoutStates::NotInExercisePosition;

	UPROPERTY(BlueprintReadOnly, Category = "Strength")
	FBodyPartData Thigh_Left;
	UPROPERTY(BlueprintReadOnly, Category = "Strength")
	FBodyPartData Thigh_Right;
	UPROPERTY(BlueprintReadOnly, Category = "Strength")
	FBodyPartData Arm_Left;
	UPROPERTY(BlueprintReadOnly, Category = "Strength")
	FBodyPartData Arm_Right;


public:
	/** State Setters **/
	void SetCurrentPlayMode(const EPlayModes InPlayMode) { CurrentPlayMode = InPlayMode; }
	void SetCurrentWorkoutState(const EWorkoutStates InWorkoutState) { CurrentWorkoutState = InWorkoutState; }
	
};

