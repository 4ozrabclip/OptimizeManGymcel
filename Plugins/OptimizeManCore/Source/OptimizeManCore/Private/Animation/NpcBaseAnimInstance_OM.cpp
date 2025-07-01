// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "Chaos/Character/CharacterGroundConstraintContainer.h"

void UNpcBaseAnimInstance_OM::NativeInitializeAnimation()
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

	OwningNpc = Cast<ANpcBase_OM>(GetOwningActor());

	//May be something here with making there heads look up before Tick Starts
}

void UNpcBaseAnimInstance_OM::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningNpc && Player && GetWorld() && !GetWorld()->IsPaused())
	{
		LookAtLocation = OwningNpc->LookAtLocation(DeltaSeconds);
		
		UpdateIsMoving();
	}
}
void UNpcBaseAnimInstance_OM::UpdateIsMoving()
{
	if (!OwningNpc) return;

	const float SpeedSq = OwningNpc->GetVelocity().SizeSquared2D();

	if (const bool bCurrentlyMoving = SpeedSq > 25.0f)
	{
		bPreviousIsMoving = true;
		GetWorld()->GetTimerManager().ClearTimer(MovementDecayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(MovementDecayTimerHandle, this, &UNpcBaseAnimInstance_OM::ResetMovementFlag, 0.2f, false); 
	}
	bIsWalking = bPreviousIsMoving;
}
void UNpcBaseAnimInstance_OM::SetIsTalking(const bool InIsTalking)
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

bool UNpcBaseAnimInstance_OM::GetIsInSquatPosition() const
{
	return bIsInSquatPosition;
}

void UNpcBaseAnimInstance_OM::SetIsInSquatPosition(const bool InIsInSquatPosition)
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

void UNpcBaseAnimInstance_OM::SetIsInCurlPosition(bool InIsInCurlPosition)
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

void UNpcBaseAnimInstance_OM::SetIsInOverheadPressPosition(bool InIsInOverheadPressPosition)
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

void UNpcBaseAnimInstance_OM::SetIsInLeftCurlPosition(bool InIsInLeftCurlPosition)
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

void UNpcBaseAnimInstance_OM::SetIsInRightCurlPosition(bool InIsInRightCurlPosition)
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


void UNpcBaseAnimInstance_OM::DoRepAnim(bool& InIsRepping, bool& InIsInPosition, float AnimDuration)
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

void UNpcBaseAnimInstance_OM::ExitPosition(bool& InIsRepping, bool& InIsInPosition)
{
	InIsRepping = false;
	InIsInPosition = false;

	if (RepAnimTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RepAnimTimerHandle);
	}
}

