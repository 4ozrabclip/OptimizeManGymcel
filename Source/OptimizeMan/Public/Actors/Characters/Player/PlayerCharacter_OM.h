// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Utils/Structs/PlayerData.h"
#include "Utils/Structs/PlayModes.h"
#include "PlayerCharacter_OM.generated.h"

class APlayerController_OM;
class ULevelSequence;
class AInteractableActor_OM;
class ANpcBase_OM;


UCLASS()
class OPTIMIZEMAN_API APlayerCharacter_OM : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter_OM();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	bool GetIsJumping();


	bool GetIsDoingRep() const { return bIsDoingRep; };
	void SetIsDoingRep(bool InIsDoingRep) { bIsDoingRep = InIsDoingRep; };
	
protected: //Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class UPlayerVoiceAudio_OM* PlayerAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class UFootstepAudio_OM* FootstepAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class UNotificationAudio_OM* NotificationAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exercise")
	class UExercise_OM* ExerciseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocialSystem")
	class USocialInteractionSystem_OM* SocialComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyDeformer")
	class UPlayerDeformationsComponent_OM* BodyDeformerComponent;
	

public: //Input variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MuscleViewLocation")	
	FVector PlayerFacingMuscleViewLocation;

private: //Private Variables
	UPROPERTY()
	APlayerController_OM* PlayerController;
	
	bool bTodoOpen;
	bool bPauseMenuOpen;
	bool bIsWalking;
	bool bIsJumping;
	bool bIsDoingRep = false;

	//Used for UpdateMovementState
	FVector LastPosition;
	float MinimumMovementThreshold;
	float TimeSinceLastFootstep;
	
	float OriginalMovementSpeed;
	
	FTimerHandle SetMirrorModeTimerHandle;
	FTimerHandle SetLaptopModeTimerHandle;
	FTimerHandle SetShelfModeTimerHandle;


protected: //Protected Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float LeftArmSize = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float RightArmSize = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float LowerBodySize = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float CalvesSize = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float JawSize = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float ShouldersSize = 0.f;
	
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	EPlayModes CurrentPlayMode;
	UPROPERTY()
	AInteractableActor_OM* CurrentInteractedActor;
	UPROPERTY()
	ANpcBase_OM* CurrentInteractedCharacter;
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	UPROPERTY()
	class UTodoManagementSubsystem* TodoManager;

private:
	TMap<EPlayModes, FPlayModeConfig> PlayModeConfigs;

	void InitPlayModes();

	//TSoftObjectPtr<USkeletalMesh DefaultSkeletalMeshRef;
//	TSubclassOf<UAnimInstance> AnimInstance;
	UPROPERTY()
	USkeletalMesh* DefaultSkeletalMesh;

	TWeakObjectPtr<class UPlayerCharacterAnimInstance_OM> CachedAnimInstance;


	


public:
	void ShitDay();
	void ShitReaction();
	void ClearTimers();
	void ResetPlayer();
	void SetToUIMode(const bool bSetToUiMode, const bool bAllowGameMovement = false) const;
	

	void TogglePlayMode(EPlayModes InPlayMode, bool& InOpenOrClosedState, AInteractableActor_OM* InInteractableActor = nullptr);
	UFUNCTION()
	void TogglePauseMode() { TogglePlayMode(EPlayModes::PauseMode, bPauseMenuOpen);}
	UFUNCTION()
	void ToggleTodoMode() { TogglePlayMode(EPlayModes::TodoMode, bTodoOpen);}


	// Dont like how this bool is public, should suss it out later as passing it into as paramater from actor funcs
	bool bInteractableOpen;

public: //Input amd Locomotion
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	UFUNCTION()
	void InteractClick() { Interact(false);}
	UFUNCTION()
	void InteractToggle() { Interact(true);}

protected:
	void Interact(const bool bToggleable);
	float CalculateJumpHeight(float LowerBodyStat) const;

	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float BaseJumpHeight = 220.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float JumpHeightMultiplier = 1.5f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxJumpHeight = 1000.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinJumpHeight = 300.0f;

	
protected: //Update States and Playmodes
	void UpdateMovementState();

	void CheckInteractable();

	
public: //Getters and Setters
	UFUNCTION()
	UPlayerCharacterAnimInstance_OM* GetCachedAnimInstance() const { return CachedAnimInstance.Get(); }

	UFUNCTION(Category = "Gameplay")
	void SetCurrentPlayMode(const EPlayModes InPlayMode, const TWeakObjectPtr<AInteractableActor_OM> InInteractedActor = nullptr, const TWeakObjectPtr<ANpcBase_OM> InInteractedCharacter = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	EPlayModes GetCurrentPlayMode() const { return CurrentPlayMode; }
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AInteractableActor_OM* GetCurrentInteractedActor() const { return CurrentInteractedActor; };

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	ANpcBase_OM* GetCurrentInteractedCharacter() const { return CurrentInteractedCharacter; };

	void SetCurrentInteractedCharacter(ANpcBase_OM* InInteractedCharacter = nullptr) { CurrentInteractedCharacter = InInteractedCharacter; };
	
	void SetIsWalking(const bool InIsWalking) { bIsWalking = InIsWalking; };
	bool GetIsWalking() const { return bIsWalking; };

	bool GetIsJumping() const { return bPressedJump; };
	
	void SetMaxMovementSpeed(const float InMaxMovementSpeed);
	void SetEmotionalState();

	float GetMaxMovementSpeed() const;
	
	void SetOriginalMovementSpeed(const float InOriginalMovementSpeed) { OriginalMovementSpeed = InOriginalMovementSpeed; };
	float GetOriginalMovementSpeed() const { return OriginalMovementSpeed; };
	
	void SetMinimumMovementThreshold(const float InMinimumMovementThreshold) { 	MinimumMovementThreshold = InMinimumMovementThreshold;}
	float GetMinimumMovementThreshold() const { return MinimumMovementThreshold; }
	


protected: //Manage PlayModes
	UFUNCTION(BlueprintCallable, Category = "InteractionModes")
	void ManageWorkoutMode();
	UFUNCTION(BlueprintCallable, Category = "InteractionModes")
	void ManageRegularMode();
	UFUNCTION(BlueprintCallable, Category = "InteractionModes")
	void ManageSocialMode();
	UFUNCTION(BlueprintCallable, Category = "InteractionModes")
	void ManageTodoMode();



private:
	void ManageCurrentPlayMode();
	void ManagePauseMode();

	FVector HeadPosition;
	
};
