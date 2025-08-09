// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/SpringArmComponent_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Audio/Concrete/PlayerVoiceAudio_OM.h"

USpringArmComponent_OM::USpringArmComponent_OM()
{
	PrimaryComponentTick.bCanEverTick = true;
	bDoCollisionTest = false;
}

void USpringArmComponent_OM::BeginPlay()
{
	Super::BeginPlay();

	OriginalSocketOffset = SocketOffset;
	
	TargetInBreath = OriginalSocketOffset.Z + MaxBreathOffset;

	SetBreathingPhase(EBreathingPhase::Idle);

	SetComponentTickEnabled(true);


	if (auto* Player = Cast<APlayerCharacter_OM>(GetOwner()))
	{
		if (auto* BreathAudioComp = Cast<UPlayerVoiceAudio_OM>(Player->GetComponentByClass<UPlayerVoiceAudio_OM>()))
		{
			BreathAudioComp->OnBreathTaken.AddDynamic(this, &USpringArmComponent_OM::TakeBreath);
		}
	}
}

void USpringArmComponent_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
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
		return;
	case EBreathingPhase::BreathingIn:
		{
			BreathingPhaseTime += DeltaTime;
			
			float Alpha = FMath::Clamp(BreathingPhaseTime / BreathUpInterpSpeed, 0.0f, 1.0f);
			SocketOffset.Z = FMath::Lerp(OriginalSocketOffset.Z, TargetInBreath, Alpha);
			
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
			SocketOffset.Z = FMath::Lerp(TargetInBreath, OriginalSocketOffset.Z, Alpha);

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

void USpringArmComponent_OM::TakeBreath(EBreathingIntensity InIntensity)
{
	SetBreathingPhase(EBreathingPhase::BreathingIn);
}
