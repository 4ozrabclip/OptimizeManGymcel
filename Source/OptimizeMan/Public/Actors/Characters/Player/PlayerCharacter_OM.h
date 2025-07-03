// Copyright © 2025 4ozStudio. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Characters/PlayerCharacterBase_OM.h"

#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/EnergyTick_OM.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTick_OM.h"
#include "Utils/Structs/PlayModes_Gymcel.h"

#include "PlayerCharacter_OM.generated.h"


class UGameInstance_OMG;
class APlayerController_OMG;
class UTodoManagement_OMG;
class ANpcBase_OMG;

UCLASS()
class OPTIMIZEMAN_API APlayerCharacter_OM : public APlayerCharacterBase_OM
{
	GENERATED_BODY()
public:
	APlayerCharacter_OM();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
public:
	/***** GAS Init *****/
	virtual void InitializeAttributes() override;
	virtual void InitializeEffects() override;
protected:
	
	/************
	 * Components
	 ************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<USceneComponent> SelfieCameraLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UExercise_OM> ExerciseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class USocialInteractionSystem_OM> SocialComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UPlayerDeformationsComponent_OM> BodyDeformerComponent;


	/**** Movement Settings ****/
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
	
	/***** Gameplay Effects *****/
	FActiveGameplayEffectHandle FocusDrainEffectHandle;

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
	/** Class Cache **/
	APlayerController_OMG* GetPlayerController_Gymcel() const;
	UGameInstance_OMG* GetGameInstance_Gymcel() const;
	UTodoManagement_OMG* GetTodoManager_Gymcel() const;



	TWeakObjectPtr<class UPlayerCharacterAnimInstance_OMG> CachedAnimInstance;

	/** Current Interacted **/

	FORCEINLINE ANpcBase_OMG* GetCurrentInteractedCharacter_Gymcel() const
	{
		return Cast<ANpcBase_OMG>(CurrentInteractedCharacter);
	}

	/**** Movement Tracking State ****/
	bool bIsDoingRep = false;


public:
	/**** Input Handling ****/
	virtual void Jump() override;

	/** Interaction **/
	virtual void HandleNoHitInteraction() override;
	
	/**** Camera Tricks ****/
	UFUNCTION(BlueprintCallable)
	void SpawnSelfieCamera();

protected:
	float CalculateJumpHeight(float LowerBodyStat) const;

	/**** Play Mode State Management ****/
public:
	void TogglePlayMode(EPlayModes InPlayMode, bool& InOpenOrClosedState, AInteractableActor_OM* InInteractableActor = nullptr);

	UFUNCTION()
	void TogglePauseMode() { TogglePlayMode(EPlayModes::PauseMode, bPauseMenuOpen); }

	UFUNCTION()
	void ToggleTodoMode() { TogglePlayMode(EPlayModes::TodoMode, bTodoOpen); }

	void SyncStatsToGameInstance();

protected:
	void InitPlayModes();
	void ManageCurrentPlayMode();
	void InitializeConstantEffects();
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
	

	/**** Gameplay Logic ****/
public:
	void ShitDay();
	void ShitReaction();
	void ClearTimers();
	void ResetPlayer();
	void SetToUIMode(const bool bSetToUiMode, const bool bAllowGameMovement = false, UUserWidget* InWidget = nullptr) const;

	/**** Getters ****/

	/*** Setters ***/
	UFUNCTION(Category = "Gameplay")
	void SetCurrentPlayMode(const EPlayModes InPlayMode, const TWeakObjectPtr<AInteractableActor_OM> InInteractedActor = nullptr, const TWeakObjectPtr<ANpcBase_OMG> InInteractedCharacter = nullptr);

public:



	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	EPlayModes GetCurrentPlayMode() const { return CurrentPlayMode; }

private:
	
public:
	void SetEmotionalState();
	void SetIsDoingRep(const bool InIsDoingRep) { bIsDoingRep = InIsDoingRep; }
	bool GetIsDoingRep() const { return bIsDoingRep; }

	


};

