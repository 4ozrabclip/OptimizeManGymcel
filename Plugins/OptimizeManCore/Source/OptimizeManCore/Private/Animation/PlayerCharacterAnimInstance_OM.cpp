// Copyright © 2025 4ozStudio. All rights reserved.


#include "Animation/PlayerCharacterAnimInstance_OM.h"

#include "Characters/PlayerCharacterBase_OM.h"


void UPlayerCharacterAnimInstance_OM::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	bUseMultiThreadedAnimationUpdate = false;
	Player = Cast<APlayerCharacterBase_OM>(TryGetPawnOwner());

	bIsWalking = false;
	bIsJumping = false;
	
}

void UPlayerCharacterAnimInstance_OM::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Player && GetWorld() && !GetWorld()->IsPaused())
	{
		bIsWalking = Player->GetIsWalking();
		bIsJumping = Player->GetIsJumping();

	}

	
}
