// Copyright © 2025 4ozStudio. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "InputAction.h"
#include "GameplayTagContainer.h"

#include "GameplayAbilitySystem/AttributeSets/Concrete/GymSpecificStats_OM.h"
#include "GameplayAbilitySystem/AttributeSets/Concrete/MentalHealthStats_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyTick_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTick_OM.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/PlayerData.h"
#include "Utils/Structs/PlayModes.h"

#include "PlayerCharacter_OM.generated.h"

class UCameraDriftComponent_OM;
class UCameraComponent;
class UTodoManagementSubsystem;
class UGameInstance_OM;
class APlayerController_OM;
class ULevelSequence;
class AInteractableActor_OM;
class ANpcBase_OM;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayModeChange, EPlayModes, NewPlayMode);
UCLASS()
class OPTIMIZEMAN_API APlayerCharacter_OM : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:  
	APlayerCharacter_OM();
protected:
	/**** Class Overrides ****/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	/***** GAS Funcs *****/
	void InitializeAttributes();
protected:
	void InitializeConstantEffects();

	/**** Camera Tricks ****/
	UFUNCTION(BlueprintCallable)
	void SpawnSelfieCamera();

	
	/**** Components ****/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<USceneComponent> SelfieCameraLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<UCameraDriftComponent_OM> CameraDriftComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UPlayerVoiceAudio_OM> PlayerAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UFootstepAudio_OM> FootstepAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UNotificationAudio_OM> NotificationAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UExercise_OM> ExerciseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class USocialInteractionSystem_OM> SocialComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UPlayerDeformationsComponent_OM> BodyDeformerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UAbilitySystemComponent_OM> AbSysComp;

	/**** Movement + Jump Settings ****/
	UPROPERTY(EditAnywhere, Category = "Movement")
	float BaseJumpHeight = 220.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float JumpHeightMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxJumpHeight = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinJumpHeight = 300.0f;

	/**** Muscle View Location ****/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MuscleViewLocation")
	FVector PlayerFacingMuscleViewLocation;

private:
	/**** PlayMode + UI State ****/
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	EPlayModes CurrentPlayMode;
	TMap<EPlayModes, FPlayModeConfig> PlayModeConfigs;
	UPROPERTY()
	AInteractableActor_OM* CurrentInteractedActor;
	UPROPERTY()
	ANpcBase_OM* CurrentInteractedCharacter;

	/****** AnimCache *******/
	UPROPERTY()
	USkeletalMesh* DefaultSkeletalMesh;
	TWeakObjectPtr<class UPlayerCharacterAnimInstance_OM> CachedAnimInstance;

	/***** Gameplay Effects *****/
	FActiveGameplayEffectHandle FocusDrainEffectHandle;

public:
	bool bTodoOpen = false;
	bool bPauseMenuOpen = false;
	bool bInteractableOpen = false;


	/** Delegate Events **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Events)
	FOnPlayModeChange OnPlayModeChange;
	
protected:
	/**** Muscle Stats ****/
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

	/**** GAS effects ****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constant Effects")
	TSubclassOf<UFocusTick_OM> FocusTickClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constant Effects")
	TSubclassOf<UEnergyTick_OM> EnergyTickClass;
	

	/**** Timers + Head Location ****/
	FTimerHandle SetMirrorModeTimerHandle;
	FTimerHandle SetLaptopModeTimerHandle;
	FTimerHandle SetShelfModeTimerHandle;

	FVector HeadPosition;


private:
	/**** PC + GI + GISubSystems****/
	UPROPERTY()
	APlayerController_OM* PlayerController;
	UPROPERTY()
	UGameInstance_OM* GameInstance;
	UPROPERTY()
	UTodoManagementSubsystem* TodoManager;
	
	/**** Movement Tracking State ****/
	FVector LastPosition;
	float MinimumMovementThreshold = 0.5f;
	float TimeSinceLastFootstep = 0.f;
	float OriginalMovementSpeed = 600.f;

	bool bIsWalking = false;
	bool bIsJumping = false;
	bool bIsDoingRep = false;

	/**** Input Handling ****/
public:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;

	UFUNCTION()
	void InteractClick();

	UFUNCTION()
	void InteractToggle() { Interact(true); }

protected:
	void Interact(const bool bToggleable);
	float CalculateJumpHeight(float LowerBodyStat) const;

	/**** Play Mode State Management ****/
public:
	void TogglePlayMode(EPlayModes InPlayMode, bool& InOpenOrClosedState, AInteractableActor_OM* InInteractableActor = nullptr, ANpcBase_OM* InInteractedCharacter = nullptr);

	UFUNCTION()
	void TogglePauseMode() { TogglePlayMode(EPlayModes::PauseMode, bPauseMenuOpen); }

	UFUNCTION()
	void ToggleTodoMode() { TogglePlayMode(EPlayModes::TodoMode, bTodoOpen); }

	void SyncStatsToGameInstance();

protected:
	void InitPlayModes();
	void ManageCurrentPlayMode();

	void ManagePauseMode();

	UFUNCTION(BlueprintCallable, Category = "InteractionModes")
	void ManageWorkoutMode();

	UFUNCTION(BlueprintCallable, Category = "InteractionModes")
	void ManageRegularMode();
	void SwitchTag(FGameplayTag InTag, FGameplayTag RootTag);
public:
	void SwitchStateTag(const FGameplayTag NewState) { SwitchTag(NewState, FGameplayTag::RequestGameplayTag("State")); }
	void SwitchLevelTag(const FGameplayTag NewLevel) { SwitchTag(NewLevel, FGameplayTag::RequestGameplayTag("Level")); }
protected:

	UFUNCTION(BlueprintCallable, Category = "InteractionModes")
	void ManageSocialMode();

	UFUNCTION(BlueprintCallable, Category = "InteractionModes")
	void ManageTodoMode();

	void UpdateMovementState();
	void CheckInteractable();

	/**** Gameplay Logic ****/
public:
	void ShitDay();
	void ShitReaction();
	void ClearTimers();
	void ResetPlayer();
	void SetToUIMode(const bool bSetToUiMode, const bool bAllowGameMovement = false, UUserWidget* InWidget = nullptr, bool bAllowCameraRotation = false) const;

	/**** Getters / Setters ****/
public:
	UFUNCTION()
	UPlayerCharacterAnimInstance_OM* GetCachedAnimInstance() const { return CachedAnimInstance.Get(); }
	float GetFocus() const;

	UFUNCTION()
	EWorkoutStates GetWorkoutState() const;
	UFUNCTION()
	EExerciseType GetCurrentExerciseType() const;

	UFUNCTION(Category = "Gameplay")
	void SetCurrentPlayMode(const EPlayModes InPlayMode, const TWeakObjectPtr<AInteractableActor_OM> InInteractedActor = nullptr, const TWeakObjectPtr<ANpcBase_OM> InInteractedCharacter = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	EPlayModes GetCurrentPlayMode() const { return CurrentPlayMode; }

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AInteractableActor_OM* GetCurrentInteractedActor() const { return CurrentInteractedActor; }

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	ANpcBase_OM* GetCurrentInteractedCharacter() const { return CurrentInteractedCharacter; }

	void SetCurrentInteractedCharacter(ANpcBase_OM* InInteractedCharacter = nullptr) { CurrentInteractedCharacter = InInteractedCharacter; }

	void SetIsWalking(const bool InIsWalking) { bIsWalking = InIsWalking; }
	bool GetIsWalking() const { return bIsWalking; }

	bool GetIsJumping() const;

	void SetIsDoingRep(const bool InIsDoingRep) { bIsDoingRep = InIsDoingRep; }
	bool GetIsDoingRep() const { return bIsDoingRep; }

	void SetMaxMovementSpeed(const float InMaxMovementSpeed);
	float GetMaxMovementSpeed() const;

	void SetOriginalMovementSpeed(const float InOriginalMovementSpeed) { OriginalMovementSpeed = InOriginalMovementSpeed; }
	float GetOriginalMovementSpeed() const { return OriginalMovementSpeed; }

	void SetMinimumMovementThreshold(const float InMinimumMovementThreshold) { MinimumMovementThreshold = InMinimumMovementThreshold; }
	float GetMinimumMovementThreshold() const { return MinimumMovementThreshold; }

	void SetEmotionalState();
};

