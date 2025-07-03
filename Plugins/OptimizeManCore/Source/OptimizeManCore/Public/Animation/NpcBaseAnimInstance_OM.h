// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NpcBaseAnimInstance_OM.generated.h"

class ANpcBase_OM;
class APlayerCharacterBase_OM;
/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMANCORE_API UNpcBaseAnimInstance_OM : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;


	/** Getters **/
	bool GetIsTalking() const { return bIsTalking; }

	
	/** Setters **/
	void SetPlayer(APlayerCharacterBase_OM* InPlayerCharacter) { Player = InPlayerCharacter; }


protected:
	/** Class Cache **/
	UPROPERTY()
	APlayerCharacterBase_OM* Player;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsWalking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Talking", meta = (AllowPrivateAccess = "true"))
	bool bIsTalking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LookAt", meta = (AllowPrivateAccess = "true"))
	FVector LookAtLocation;
	
};

