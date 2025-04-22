// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Gym/GymGate_OM.h"

#include "Audio/GameAudio_OM.h"
#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
#include "Utils/Structs/AudioTypes.h"

AGymGate_OM::AGymGate_OM()
{
	PrimaryActorTick.bCanEverTick = true;
	bGateIsOpen = false;

	CurrentRotationAlpha = 0.f;
	TimeSinceTriggered = 0.f;
	GateOpenSpeed = 3.f;

	GateOne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GymGates"));
	GateOne->SetCollisionProfileName(TEXT("Default"));
	GateOne->SetupAttachment(RootComponent);

	GateTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GymGates2"));
	GateTwo->SetCollisionProfileName(TEXT("Default"));
	GateTwo->SetupAttachment(RootComponent);


	AudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAudioType(EAudioTypes::SfxAudio);
}

void AGymGate_OM::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	AuraLight->SetLightFColor(GateRedColour);

	DoorOneClosedRotation = GateOne->GetComponentRotation();
	DoorTwoClosedRotation = GateTwo->GetComponentRotation();
}

void AGymGate_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (!bGateIsOpen)
	{
		AuraLight->SetLightFColor(GateGreenColour);
		if (AudioComponent && GateBeepSound)
		{
			AudioComponent->SetSound(GateBeepSound);
			AudioComponent->Play();
		}
		SetActorTickEnabled(true);
	}
}

void AGymGate_OM::ClearGateTimer()
{
	if (GateCloseTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(GateCloseTimerHandle);
	}
	SetActorTickEnabled(false);
}


void AGymGate_OM::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bGateIsOpen) OpenGate(DeltaSeconds);
	else CloseGate(DeltaSeconds);

}
void AGymGate_OM::OpenGate(float DeltaTime)
{
	TimeSinceTriggered += DeltaTime;

	
	CurrentRotationAlpha = FMath::Clamp(TimeSinceTriggered * GateOpenSpeed, 0.f, 1.f);
	
	GateOne->SetWorldRotation(FMath::Lerp(DoorOneClosedRotation, DoorOpenRotation, CurrentRotationAlpha));
	GateTwo->SetWorldRotation(FMath::Lerp(DoorTwoClosedRotation, DoorOpenRotation, CurrentRotationAlpha));
	if (CurrentRotationAlpha >= 1.f)
	{
		bGateIsOpen = true;
		SetActorTickEnabled(false);
		TimeSinceTriggered = 0.f;
		CurrentRotationAlpha = 0.f;
		PrepareDelayForGateClose();
		
	}
}
void AGymGate_OM::PrepareDelayForGateClose()
{
	if (GateCloseTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(GateCloseTimerHandle);
	}
    
	GetWorld()->GetTimerManager().SetTimer(
		GateCloseTimerHandle,
		[this]()
		{
			SetActorTickEnabled(true);
		},
		GateCloseDelay,
		false
	);
}
void AGymGate_OM::CloseGate(float DeltaTime)
{
	TimeSinceTriggered += DeltaTime;

	
	CurrentRotationAlpha = FMath::Clamp(TimeSinceTriggered * GateOpenSpeed, 0.f, 1.f);
	
	GateOne->SetWorldRotation(FMath::Lerp(DoorOpenRotation, DoorOneClosedRotation, CurrentRotationAlpha));
	GateTwo->SetWorldRotation(FMath::Lerp(DoorOpenRotation, DoorTwoClosedRotation, CurrentRotationAlpha));

	if (CurrentRotationAlpha >= 1.f)
	{
		bGateIsOpen = false;
		AuraLight->SetLightFColor(GateRedColour);
		SetActorTickEnabled(false);
		TimeSinceTriggered = 0.f;
		CurrentRotationAlpha = 0.f;
	}
	
}


