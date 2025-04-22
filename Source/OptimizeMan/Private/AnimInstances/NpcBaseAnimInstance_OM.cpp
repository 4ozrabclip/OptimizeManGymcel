// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "Actors/Characters/NPC/NpcBase_OM.h"

void UNpcBaseAnimInstance_OM::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	bIsTalking = false;
	bIsWalking = false;
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
	}
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
