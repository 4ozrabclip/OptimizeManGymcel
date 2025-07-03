// Copyright © 2025 4ozStudio. All rights reserved.


#include "AnimInstances/NpcBaseAnimInstance_OMG.h"

#include "Actors/Characters/NPC/Abstract/NpcBase_OMG.h"

void UNpcBaseAnimInstance_OMG::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	

	bIsTalking = false;
	bIsWalking = false;
	
	bPreviousIsMoving = false;
	
	bIsYelling = false;
	bIsExplaining = false;
	bIsAffirming = false;
	bIsDisagreeing = false;
	bIsDisgusted = false;
	bIsLaughing = false;
	bIsConfused = false;

	OwningNpc = Cast<ANpcBase_OMG>(GetOwningActor());

	
}

void UNpcBaseAnimInstance_OMG::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!GetWorld() || GetWorld()->IsPaused() || !OwningNpc)

	if (OwningNpc && Player && GetWorld() && !GetWorld()->IsPaused())
	{
		LookAtLocation = OwningNpc->LookAtLocation(DeltaSeconds);
		
		UpdateIsMoving();
	}
}
void UNpcBaseAnimInstance_OMG::UpdateIsMoving()
{
	if (!OwningNpc) return;

	const float SpeedSq = OwningNpc->GetVelocity().SizeSquared2D();

	if (const bool bCurrentlyMoving = SpeedSq > 25.0f)
	{
		bPreviousIsMoving = true;
		GetWorld()->GetTimerManager().ClearTimer(MovementDecayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(MovementDecayTimerHandle, this, &UNpcBaseAnimInstance_OMG::ResetMovementFlag, 0.2f, false); 
	}
	bIsWalking = bPreviousIsMoving;
}
void UNpcBaseAnimInstance_OMG::SetIsTalking(const bool InIsTalking)
{
	bIsTalking = InIsTalking;

	if (InIsTalking)
	{
		bIsTalking = true;
		if (OwningNpc)
		{
			OwningNpc->PlayRandomTalkingAnimForMood();
		}
	}
	else
	{
		bIsTalking = false;
		
		bIsYelling = false;
		bIsAffirming = false;
		bIsExplaining = false;
		bIsDisagreeing = false;
		bIsDisgusted = false;
		bIsLaughing = false;
		bIsConfused = false;
	}
}

bool UNpcBaseAnimInstance_OMG::GetIsInSquatPosition() const
{
	return bIsInSquatPosition;
}

void UNpcBaseAnimInstance_OMG::SetIsInSquatPosition(const bool InIsInSquatPosition)
{
	if (InIsInSquatPosition)
	{
		UE_LOG(LogTemp, Error, TEXT("Set is in squat position true")); 
		bIsInCurlPosition = false;
		bIsInOverheadPressPosition = false;
		bIsInLeftCurlPosition = false;
		bIsInRightCurlPosition = false;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Set is in squat position false"));
	}
	bIsInSquatPosition = InIsInSquatPosition;
}

void UNpcBaseAnimInstance_OMG::SetIsInCurlPosition(bool InIsInCurlPosition)
{
	if (InIsInCurlPosition)
	{
		bIsInSquatPosition = false;
		bIsInOverheadPressPosition = false;
		bIsInLeftCurlPosition = false;
		bIsInRightCurlPosition = false;
	}
	bIsInCurlPosition = InIsInCurlPosition;
}

void UNpcBaseAnimInstance_OMG::SetIsInOverheadPressPosition(bool InIsInOverheadPressPosition)
{
	if (InIsInOverheadPressPosition)
	{
		bIsInSquatPosition = false;
		bIsInCurlPosition = false;
		bIsInLeftCurlPosition = false;
		bIsInRightCurlPosition = false;
	}
	bIsInOverheadPressPosition = InIsInOverheadPressPosition;
}

void UNpcBaseAnimInstance_OMG::SetIsInLeftCurlPosition(bool InIsInLeftCurlPosition)
{
	if (InIsInLeftCurlPosition)
	{
		bIsInSquatPosition = false;
		bIsInCurlPosition = false;
		bIsInOverheadPressPosition = false;
		bIsInRightCurlPosition = false;

	}
	bIsInLeftCurlPosition = InIsInLeftCurlPosition;
}

void UNpcBaseAnimInstance_OMG::SetIsInRightCurlPosition(bool InIsInRightCurlPosition)
{
	if (InIsInRightCurlPosition)
	{
		bIsInSquatPosition = false;
		bIsInCurlPosition = false;
		bIsInOverheadPressPosition = false;
		bIsInLeftCurlPosition = false;
	}
	bIsInRightCurlPosition = InIsInRightCurlPosition;
}

void UNpcBaseAnimInstance_OMG::DoRepAnim(bool& InIsRepping, bool& InIsInPosition, float AnimDuration)
{
	UE_LOG(LogTemp, Error, TEXT("DO Rep Anim"));
	if (!InIsInPosition)
	{
		UE_LOG(LogTemp, Error, TEXT("Set is in pos false"));
		return;
	}
	if (InIsRepping)
	{
		UE_LOG(LogTemp, Error, TEXT("already repping"));
		return;
	}

	InIsRepping = true;
	UE_LOG(LogTemp, Display, TEXT("IN IS REPPING"));

	GetWorld()->GetTimerManager().ClearTimer(RepAnimTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RepAnimTimerHandle, [this, &InIsRepping]()
	{
		InIsRepping = false;
	}, AnimDuration, false);
}

void UNpcBaseAnimInstance_OMG::ExitPosition(bool& InIsRepping, bool& InIsInPosition)
{
	InIsRepping = false;
	InIsInPosition = false;

	if (RepAnimTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RepAnimTimerHandle);
	}
}

