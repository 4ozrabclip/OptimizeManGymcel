// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/CameraComponent_OM.h"

UCameraComponent_OM::UCameraComponent_OM()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	DefaultFOV = FieldOfView;
	TargetFOV = DefaultFOV;
}

void UCameraComponent_OM::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);


}

void UCameraComponent_OM::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManageFOVTick(DeltaTime);
}


void UCameraComponent_OM::ManageFOVTick(float DeltaTime)
{

	if (FOVState == EFieldOfVisionState::Phasing)
	{
		TimeAccumulator += DeltaTime * PhaseSpeed; 
		float PhaseOffset = FMath::Sin(TimeAccumulator) * PhaseAmplitude;
		SetFieldOfView(DefaultFOV + PhaseOffset);
	}
	else
	{
		TargetFOV = FOVState == EFieldOfVisionState::Default ? DefaultFOV :
					FOVState == EFieldOfVisionState::Tight ? TightFOV : WideFOV;


		if (FMath::IsNearlyEqual(FieldOfView, TargetFOV, 0.01f))
		{
			SetComponentTickEnabled(false);
			return;
		}
		float FOVLerpSpeed = FOVState == EFieldOfVisionState::Default ? DefaultLerpSpeed : FastLerpSpeed;
		
		float NewFOV = FMath::FInterpTo(FieldOfView, TargetFOV, DeltaTime, FOVLerpSpeed);

		SetFieldOfView(NewFOV);
	}
	
}

void UCameraComponent_OM::SetFOVState(const EFieldOfVisionState InFOVState)
{
	if (InFOVState != EFieldOfVisionState::Default)
		SetComponentTickEnabled(true);

	FOVState = InFOVState;

}
