// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/SpringArmComponent_OM.h"

USpringArmComponent_OM::USpringArmComponent_OM()
{
	PrimaryComponentTick.bCanEverTick = true;
	OriginalSocketOffset = SocketOffset;

	MinBreathOffset = OriginalSocketOffset.Z;

	bDoCollisionTest = false;
}

void USpringArmComponent_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void USpringArmComponent_OM::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManageBreathingTick(DeltaTime);

}

void USpringArmComponent_OM::ManageBreathingTick(float DeltaTime)
{
	switch (BreathingPhase)
	{
	case EBreathingPhase::Idle:
		{
			
			TimeSinceIdle+=DeltaTime;
			UE_LOG(LogTemp, Error, TEXT("Idle\n - TimeSinceIdle: %.2f"), TimeSinceIdle);
			if (TimeSinceIdle >= BreathingTimerInterval)
			{
				TimeSinceIdle = 0;
				SetBreathingPhase(EBreathingPhase::BreathingIn);
			}
			break;
		}
	case EBreathingPhase::BreathingIn:
		{
			BreathingPhaseTime += DeltaTime;
			
			float Alpha = FMath::Clamp(BreathingPhaseTime / BreathUpInterpSpeed, 0.0f, 1.0f);
			SocketOffset.Z = FMath::Lerp(MinBreathOffset, MaxBreathOffset, Alpha);
			
			UE_LOG(LogTemp, Error, TEXT("Breathing In\n - PhaseTime: %.3f\n - Alpha: %.5f"), BreathingPhaseTime, Alpha);
			if (Alpha >= 1.f)
			{
				BreathingPhaseTime = 0;
				SetBreathingPhase(EBreathingPhase::BreathingOut);
			}
			break;
		}
	case EBreathingPhase::BreathingOut:
		{
			BreathingPhaseTime += DeltaTime;
			
			float Alpha = FMath::Clamp(BreathingPhaseTime / BreathDownInterpSpeed, 0.0f, 1.0f);
			SocketOffset.Z = FMath::Lerp(MaxBreathOffset, MinBreathOffset, Alpha);
			UE_LOG(LogTemp, Error, TEXT("Breathing Out\n PhaseTime: %.3f\n - Alpha: %.5f"), BreathingPhaseTime, Alpha);

			if (Alpha >= 1.f)
			{
				BreathingPhaseTime = 0;
				SetBreathingPhase(EBreathingPhase::Idle);
			}
			break;
		}
	default:
		return;
	}
	
}

void USpringArmComponent_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(BreathingTimerHandle);
	
}

