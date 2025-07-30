// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/SpringArmComponent_OM.h"

USpringArmComponent_OM::USpringArmComponent_OM()
{
	PrimaryComponentTick.bCanEverTick = false;
	OriginalTargetOffset = TargetOffset;
}

void USpringArmComponent_OM::BeginPlay()
{
	Super::BeginPlay();
	
	if (bPlayBreathing)
		PlayBreathingMovementInterval();
}
void USpringArmComponent_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(BreathingTimerHandle);
	
}

void USpringArmComponent_OM::PlayBreathingMovementInterval()
{
	GetWorld()->GetTimerManager().ClearTimer(BreathingTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(BreathingTimerHandle, this, &USpringArmComponent_OM::BreathUp, BreathingTimerInterval, false); 
}

void USpringArmComponent_OM::BreathUp()
{
	float BreathTarget = GetRelativeLocation().Z + MaxBreathOffset;
	FVector NewLocation = GetRelativeLocation();
	GetWorld()->GetTimerManager().ClearTimer(BreathingTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(BreathingTimerHandle,[this, BreathTarget, NewLocation]()
	{
		if (FMath::IsNearlyEqual(GetRelativeLocation().Z, BreathTarget))
			BreathDown();

		//NewLocation.Z = FMath::FInterpConstantTo(GetRelativeLocation().Z, BreathTarget, BreathingTimerInterval, BreathUpInterpSpeed);
		//SetRelativeLocation() = 
	}, DeltaTime, true);
}

void USpringArmComponent_OM::BreathDown()
{
	GetWorld()->GetTimerManager().ClearTimer(BreathingTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(BreathingTimerHandle,[this]()
	{
		if (FMath::IsNearlyEqual(SocketOffset.Z, OriginalTargetOffset.Z))
			PlayBreathingMovementInterval();
		
		SocketOffset.Z = FMath::FInterpConstantTo(TargetOffset.Z, OriginalTargetOffset.Z, BreathingTimerInterval, BreathDownInterpSpeed);
	}, DeltaTime, true);
}