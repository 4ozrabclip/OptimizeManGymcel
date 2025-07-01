// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/PlayerData.h"
#include "PlayerCharacterAnimInstance_OM.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API UPlayerCharacterAnimInstance_OM : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:


	//Locomotion
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsWalking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsJumping;
	


private:
	/** Cache **/
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	class APlayerCharacterBase_OM* Player;

};

