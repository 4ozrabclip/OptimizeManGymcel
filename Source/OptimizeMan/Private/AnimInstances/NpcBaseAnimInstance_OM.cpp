// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "Actors/Characters/NPC/NpcBase_OM.h"
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
	UE_LOG(LogTemp, Error, TEXT("SpeedSq: %f\n bIsWalking: %hs"), SpeedSq, bIsWalking ? "true" : "false");
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
