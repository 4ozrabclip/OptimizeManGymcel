// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/Components/CharacterComponentBase_OM.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/ExerciseParameters.h"
#include "Utils/Structs/PlayerData.h"
#include "Exercise_OM.generated.h"


class AExerciseEquipment_OM;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorkoutStateChanged, EWorkoutStates, NewWorkoutState);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API UExercise_OM : public UCharacterComponentBase_OM
{
	GENERATED_BODY()

public:	
	UExercise_OM();
protected:
	virtual void BeginPlay() override;
	void InitInjurys() const;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ClearBodyPartsInUse() {BodyParts.Empty(); }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Exercise")
	EExerciseType CurrentExerciseType;

	EWorkoutStates CurrentWorkoutState;

	TArray<FBodyPartData*> BodyParts;
	
	UPROPERTY()
	AExerciseEquipment_OM* Equipment;

public: // Exercise Management
	
// Events
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWorkoutStateChanged OnWorkoutStateChanged;

	//Getters and Setters
	UFUNCTION()
	void SetBodyPartInUse(const FBodyPartData& InBodyPart, const int Index = 0);
	UFUNCTION(BlueprintCallable, Category="Exercise")
	void SetExerciseType(const EExerciseType InExerciseType);

	EExerciseType GetCurrentExerciseType();
	float GetRepDuration();
	bool GetHasEnergy();
	// Functional
	void PrepareExercise();
	void AddMuscleStat(const EBodyPart Part, const EBodyPartSide Side, float Increase) const;
	UFUNCTION(BlueprintCallable, Category = "Exercise")
	void DoASquat();

	UFUNCTION(BlueprintCallable, Category = "Exercise")
	void LeaveExercise();

	void SetRep();

	void DoRep(const TFunction<void()>& AnimFunction, const TFunction<void(float)>& ModifyMuscleValueFunc,
	           float MuscleIncrease, float EnergyUse, float RepDuration);
	void CheckForExerciseAchievements();

	void Injury(const EInjuryLevel& InInjuryLevel);
	void MinorInjury();

	UFUNCTION(BlueprintCallable, Category = "Exercise")
	void MiniGame();


	void EnterExercisePosition();
	
	void DetachEquipment() const;

	
	//void TimerForExercise(const float ExerciseDuration, TFunction<void()> Cleanup) const
	//void StopExercise();
	
protected:
	UPROPERTY()
	class UPlayerVoiceAudio_OM* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SocketOffset")
	FVector NewRelativeLocation;


	FTimerHandle ExerciseTimerHandle;
	FTimerHandle FinishSetTimerHandle;

	TArray<FGameplayTag> CompletedTodosCheckList;

	FExerciseParameters ExerciseParameters;




	
public: //Getters and Setters
	void SetStoppedExercise(const bool InStoppedExercise) { bStoppedExercise = InStoppedExercise; };

	bool GetIsDoingRep() const { return bDoingRep; }

	int GetRepCount() const { return RepCount; }
	int GetSetCount() const { return SetCount; }

	EWorkoutStates GetCurrentWorkoutState() const { return CurrentWorkoutState; }

	void SetCurrentWorkoutState(const EWorkoutStates InWorkoutState);

	
private:
	bool bStoppedExercise;

	bool bDoingRep;
	int RepCount;
	int SetCount;

	bool bStartedSet;

	const float SquatDuration = 4.2f;
	const float BicepCurlDuration = 4.2f;
	const float OverheadPressDuration = 4.2f;

	float TimeSinceLastRep;

	


	
	
};

