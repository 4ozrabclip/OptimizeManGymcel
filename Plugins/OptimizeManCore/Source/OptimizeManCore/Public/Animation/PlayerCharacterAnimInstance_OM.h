// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance_OM.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMANCORE_API UPlayerCharacterAnimInstance_OM : public UAnimInstance
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
	

protected:
	/** Cache **/
	UPROPERTY(VisibleAnywhere, Category = "Player")
	class APlayerCharacterBase_OM* Player;

};

