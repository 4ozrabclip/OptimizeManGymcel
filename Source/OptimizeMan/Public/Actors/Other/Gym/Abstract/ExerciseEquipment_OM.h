// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Both/Abstract/InteractableActor_OM.h"
#include "Animation/SkeletalMeshActor.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/PlayModes.h"
#include "ExerciseEquipment_OM.generated.h"
class ALevelSequenceActor;
class ULevelSequencePlayer;
class ULevelSequence;
class UCameraComponent;
class UWidgetComponent;
class AGymCamera;
/*
 * Parent of all exercise equipment
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API AExerciseEquipment_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
	
public:	
	AExerciseEquipment_OM();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	void CreateInitialSequencePlayer(ULevelSequence* InitialLevelSequence = nullptr);


	UFUNCTION()
	void OnSequenceFinished();
	

	UPROPERTY(EditInstanceOnly, Category = "Sequences")
	TSoftObjectPtr<ASkeletalMeshActor> PlayerMesh;

	UPROPERTY(EditInstanceOnly, Category = "Flexing")
	TMap<ULevelSequence*, EExerciseType> InjurySequences;

	

	UPROPERTY()
	ULevelSequencePlayer* SequencePlayer;
	UPROPERTY()
	ALevelSequenceActor* SequenceActor;
public:

	void PlayInjurySequence();

	
	UFUNCTION()
	void TurnOffWidget();
	UFUNCTION()
	virtual void OnPlayModeChanged(EPlayModes InPlayMode) override;

	
	virtual void Interact_Implementation() override;
	void StartWorkoutMode();
	virtual void ChangeWeight(float InWeight);
	virtual void SetWeightClass();


	/** Getters/Finders **/
	
	FRotator GetLookAtCameraRotation() const;
	FVector GetLookAtCameraPosition() const;
	FTransform GetOriginalPosition() const;
	ACameraActor* GetGymCamera() const;

	float GetMaxWeight() const { return MaxWeight; }
	float GetMinWeight() const { return MinWeight; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UWidgetComponent* SelectWorkoutWidget;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	AGymCamera* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Position")
	FRotator LookAtCameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Position")
	FVector LookAtCameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weights")
	TArray<FEquipmentData> Equipment;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weights")
	float MaxWeight = 120.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weights")
	float MinWeight = 20.f;
	
	


	EWeightClass CurrentWeightClass;
	float CurrentWeight;
	
	FTransform OriginalPosition;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUnderConstruction = true;
	

private:
	EExerciseType CurrentExerciseType = EExerciseType::None;
};
