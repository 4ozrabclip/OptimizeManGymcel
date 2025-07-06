// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterBase_OM.generated.h"


class UPlayerCharacterAnimInstance_OM;
class ANpcBase_OM;
class AInteractableActor_OM;
class UCameraComponent;

UCLASS(Abstract)
class OPTIMIZEMANCORE_API APlayerCharacterBase_OM : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	APlayerCharacterBase_OM();
protected:
	/** Class Overrides **/
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
public:
	/** GAS Init **/
	virtual void InitializeAttributes() {};
	virtual void InitializeEffects() {};


	/** Input Funcs **/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override {};
	UFUNCTION()
	void InteractClick() { Interact(false); }
	UFUNCTION()
	void InteractToggle() { Interact(true); }

protected:
	/** Interaction **/
	virtual void Interact(const bool bToggleable);
	virtual void HandleNoHitInteraction() {};
	void CheckInteractable();
	/** Movement Helper **/
	void UpdateMovementState();
	
protected:
	/************
	 * Components
	 ************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UAbilitySystemComponent_OM> AbSysComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UFootstepAudio_OM> FootstepAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UNotificationAudio_OM> NotificationAudioComponent;


	

	/** Movement Settings **/
	UPROPERTY(EditAnywhere, Category = "Movement")
	float BaseJumpHeight = 220.0f;




	
	/** Anim Cache **/
	UPROPERTY()
	USkeletalMesh* DefaultSkeletalMesh;
protected:
	/** Class Cache **/
	UPROPERTY()
	class APlayerController_OM* PlayerController;
	UPROPERTY()
	class UTodoManagementSubsystem* TodoManager;
	UPROPERTY()
	class UGameInstance_OM* GameInstance;

	/** Current Interacted **/
	UPROPERTY()
	AInteractableActor_OM* CurrentInteractedActor;
	UPROPERTY()
	ANpcBase_OM* CurrentInteractedCharacter;


public:
	/** Boolean Checks **/
	bool bTodoOpen = false;
	bool bPauseMenuOpen = false;
protected:
	bool bInteractableOpen = false;
	bool bIsWalking = false;
	bool bIsJumping = false;

	/** Movement Vars **/
	FVector LastPosition;
	float MinimumMovementThreshold = 0.5f;
	float TimeSinceLastFootstep = 0.f;
	float OriginalMovementSpeed = 600.f;

	

	
public:
	/** Getters **/
	UFUNCTION()
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	ANpcBase_OM* GetCurrentInteractedCharacter() const { return CurrentInteractedCharacter; }
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AInteractableActor_OM* GetCurrentInteractedActor() const { return CurrentInteractedActor; }
	bool GetIsJumping() const;
	float GetMaxMovementSpeed() const;
	float GetMinimumMovementThreshold() const { return MinimumMovementThreshold; }
	float GetOriginalMovementSpeed() const { return OriginalMovementSpeed; }
	bool GetTodoOpen() const { return bTodoOpen; }
	bool GetPauseMenuOpen() const { return bPauseMenuOpen; }
	bool& GetInteractableOpen() { return bInteractableOpen; }

	/** Setters **/
	void SetCurrentInteractedCharacter(ANpcBase_OM* InInteractedCharacter = nullptr) { CurrentInteractedCharacter = InInteractedCharacter; }
	void SetIsWalking(const bool InIsWalking) { bIsWalking = InIsWalking; }
	bool GetIsWalking() const { return bIsWalking; }
	void SetMaxMovementSpeed(const float InMaxMovementSpeed);
	void SetMinimumMovementThreshold(const float InMinimumMovementThreshold) { MinimumMovementThreshold = InMinimumMovementThreshold; }
	void SetOriginalMovementSpeed(const float InOriginalMovementSpeed) { OriginalMovementSpeed = InOriginalMovementSpeed; }
};
