// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterBase_OM.generated.h"

class UCameraComponent;

UCLASS(Abstract)
class OPTIMIZEMANCORE_API APlayerCharacterBase_OM : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	APlayerCharacterBase_OM();
protected:
	/** Overrides **/
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	virtual void Tick(float DeltaTime) override;



	/** Getters **/
	UFUNCTION()
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	/** Input Funcs **/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	UFUNCTION()
	void InteractClick() { Interact(false); }
	UFUNCTION()
	void InteractToggle() { Interact(true); }

protected:
	/** Interaction **/
	virtual void Interact(const bool bToggleable);
	virtual void HandleNoHitInteraction() {};
	
protected:
	/************
	 * Components
	 ************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UAbilitySystemComponent_OM> AbSysComp;

	/** Audio Components **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UPlayerVoiceAudio_OM> PlayerVoiceAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UFootstepAudio_OM> FootstepAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class UNotificationAudio_OM> NotificationAudioComponent;

};
