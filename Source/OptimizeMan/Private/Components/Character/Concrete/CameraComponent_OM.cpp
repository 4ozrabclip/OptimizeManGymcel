// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/CameraComponent_OM.h"

UCameraComponent_OM::UCameraComponent_OM()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	DefaultFOV = FieldOfView;
}

void UCameraComponent_OM::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);


}


void UCameraComponent_OM::FOVShift(bool bIncreaseFOV)
{
	const float TargetFOV = bIncreaseFOV ? MaxFOV : MinFOV;

	LerpFOV(FOVShiftSpeed, TargetFOV);
	
}

void UCameraComponent_OM::LerpFOV(const float InterpSpeed, const float TargetFOV)
{
	constexpr float DeltaTime = 0.065f;
	
	GetWorld()->GetTimerManager().ClearTimer(FovShiftHandle);
	GetWorld()->GetTimerManager().SetTimer(FovShiftHandle, [this, TargetFOV, InterpSpeed]()
	{
		if (FMath::IsNearlyEqual(FieldOfView, TargetFOV))
		{
			// Call Pull back func?
			GetWorld()->GetTimerManager().ClearTimer(FovShiftHandle);
		}
		FieldOfView = FMath::FInterpConstantTo(FieldOfView, TargetFOV, DeltaTime, InterpSpeed);
		
	}, DeltaTime, true);
}

void UCameraComponent_OM::FOVLerpToDefault()
{
	constexpr float SlowInterp = 0.8f;
	LerpFOV(FOVLerpToDefaultSpeed, DefaultFOV);
}
