// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/CameraDriftComponent_OM.h"

#include "Camera/CameraComponent.h"


UCameraDriftComponent_OM::UCameraDriftComponent_OM()
{
	PrimaryComponentTick.bCanEverTick = true;
	Camera = nullptr;
	BaseRotation = FRotator(0, 0, 0);

}

void UCameraDriftComponent_OM::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Camera Drift Component Begin Play"));

	if (!Camera)
	{
		Camera = GetOwner()->FindComponentByClass<UCameraComponent>();

		if (!Camera)
		{
			UE_LOG(LogTemp, Warning, TEXT("CameraDriftComponent: Could not find camera component!"));
		}
	}
	if (Camera)
	{
		UE_LOG(LogTemp, Display, TEXT("Camera Drift Component: Setting Base Rotation"));
		BaseRotation = Camera->GetRelativeRotation();
	}
}


void UCameraDriftComponent_OM::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Camera)
	{
		UE_LOG(LogTemp, Display, TEXT("Camera Drift Component: Ticking With Camera"));
		float Time = GetWorld()->GetTimeSeconds();
		float PitchOffset = FMath::Sin(Time * 0.6f) * (2.0f * Intensity);
		float YawOffset   = FMath::PerlinNoise1D(Time * 0.2f) * (1.5f * Intensity);
		float RollOffset  = FMath::Sin(Time * 0.3f + 47.f) * (1.0f * Intensity);

		FRotator NewDrift = FRotator(PitchOffset, YawOffset, RollOffset);
		Camera->SetRelativeRotation(BaseRotation + NewDrift);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Camera Drift Component: Ticking No Camera"));
	}
		

}

