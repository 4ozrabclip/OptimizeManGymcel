// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Components/Character/Abstract/CharacterComponentBase_OM.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/ExerciseParameters.h"
#include "Utils/Structs/MinigameData.h"
#include "Utils/Structs/PlayerData.h"
#include "Exercise_OM.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorkoutStateChanged, EWorkoutStates, NewWorkoutState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinigameSelected, EMinigameType, MinigameToPlay);


class AExerciseEquipment_OM;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API UExercise_OM : public UCharacterComponentBase_OM
{
	GENERATED_BODY()
public:	
	UExercise_OM();
protected:
	/** Class Overrides **/
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	void InitInjuries();

public:
	void ClearBodyPartsInUse() { BodyParts.Empty(); }


	UFUNCTION()
	void SetMinigame(const EMinigameType MinigameToPlay) const;

protected:
	UPROPERTY()
	AExerciseEquipment_OM* Equipment;
	
	/** State Management **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Exercise")
	EExerciseType CurrentExerciseType;

	EWorkoutStates CurrentWorkoutState;



	/** BodyParts And Other Struct Data **/
	TArray<FBodyPartData> BodyParts;
	TArray<FGameplayTag> CompletedTodosCheckList;

	FExerciseParameters ExerciseParameters;


	/** GAS **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TSubclassOf<UGameplayEffect> EnergyNegativeHitEffect;


public:
	
	/** Delegate Events **/
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWorkoutStateChanged OnWorkoutStateChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMinigameSelected OnMinigameSelected;

	/** Setters/Adders **/
	UFUNCTION()
	void SetBodyPartInUse(const FBodyPartData& InBodyPart);
	UFUNCTION(BlueprintCallable, Category="Exercise")
	void SetExerciseType(const EExerciseType InExerciseType);
	
	void SetRep();
	void SetStoppedExercise(const bool InStoppedExercise) { bStoppedExercise = InStoppedExercise; };
	void SetCurrentWorkoutState(const EWorkoutStates InWorkoutState);
	void AddMuscleStat(const EBodyPart Part, const EBodyPartSide Side, float Increase) const;


	/** Getters **/
	EExerciseType GetCurrentExerciseType();
	float GetRepDuration();
	bool GetHasEnergy();
	bool GetIsDoingRep() const { return bDoingRep; }
	int GetRepCount() const { return RepCount; }
	int GetSetCount() const { return SetCount; }
	EWorkoutStates GetCurrentWorkoutState() const { return CurrentWorkoutState; }
	float GetEnergy() const;
	float GetFocus() const;

	FBodyPartData* GetCurrentInjuredPart() const { return CurrentInjuredPart; }


	
	/** Functional **/
	UFUNCTION(BlueprintCallable, Category = "Exercise")
	void LeaveExercise();
	UFUNCTION(BlueprintCallable, Category = "Exercise")
	void MiniGame(EMinigameResult MinigameResult = EMinigameResult::Success);

	void PrepareExercise();
	
	void DoRep(const TFunction<void(float)>& ModifyMuscleValueFunc,
	           float MuscleIncrease, float EnergyUse, float RepDuration);
	void CheckForExerciseAchievements();

	void Injury(const EInjuryLevel& InInjuryLevel);
	void UseEnergy(float InLevel = 1.f);

	void EnterExercisePosition();

	void DetachEquipment() const;

	
	//void TimerForExercise(const float ExerciseDuration, TFunction<void()> Cleanup) const
	//void StopExercise();
	
protected:
	/** Class References **/
	UPROPERTY()
	class UPlayerVoiceAudio_OM* AudioComponent; // This is just a reference, maybe if cast instead
	UPROPERTY()
	class UAbilitySystemComponent_OM* AbSysComp;
	UPROPERTY()
	const class UGymSpecificStats_OM* GymStats;
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SocketOffset")
	FVector NewRelativeLocation;



	/** Timer Handles **/
	FTimerHandle ExerciseTimerHandle;
	FTimerHandle FinishSetTimerHandle;



private:
	FBodyPartData* CurrentInjuredPart;


	
public: //Getters and Setters


	
private:
	bool bStoppedExercise;

	bool bDoingRep;
	int RepCount;
	int SetCount;

	bool bStartedSet;

	const float SquatDuration = 4.2f;
	const float BicepCurlDuration = 4.2f;
	const float OverheadPressDuration = 4.2f;
	const float ChestDipDuration = 4.2f;

	float TimeSinceLastRep;

	


	
	
};

