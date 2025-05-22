// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Gym/GymGate_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
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
	
	DoorOneClosedLocation = GateOne->GetComponentLocation();
	DoorTwoClosedLocation = GateTwo->GetComponentLocation();
	
}

void AGymGate_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (!bGateIsOpen)
	{
		AuraLight->SetLightFColor(GateGreenColour);
		CheckIfInwardOrOutward();
		if (AudioComponent && GateBeepSound)
		{
			AudioComponent->SetSound(GateBeepSound);
			AudioComponent->Play();
		}
		SetActorTickEnabled(true);
	}
}
void AGymGate_OM::CheckIfInwardOrOutward()
{
	const FRotator RecToGymRot = FRotator(-90, 0, 180);
	const FRotator GymToRecRot = FRotator(-90, 0, 360);
	
	FVector GateForward = GetActorForwardVector();
	FVector ToPlayer = Player->GetActorLocation() - GetActorLocation();
	ToPlayer.Normalize();

	float Dot = FVector::DotProduct(GateForward, ToPlayer);
	UE_LOG(LogTemp, Error, TEXT("Dot Product: %f"), Dot);
	
	if (Dot > 0)
	{
		DoorOpenRotation = RecToGymRot;
	}
	else
	{
		DoorOpenRotation = GymToRecRot;
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, "GymToRec");
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
	const FVector DoorOneOpenLocation = FVector(DoorOneClosedLocation.X, DoorOneClosedLocation.Y - 100, DoorOneClosedLocation.Z);
	const FVector DoorTwoOpenLocation = FVector(DoorTwoClosedLocation.X, DoorTwoClosedLocation.Y + 100, DoorTwoClosedLocation.Z);

	
	CurrentRotationAlpha = FMath::Clamp(TimeSinceTriggered * GateOpenSpeed, 0.f, 1.f);
	GateOne->SetWorldLocation(FMath::Lerp(DoorOneClosedLocation, DoorOneOpenLocation, CurrentRotationAlpha));
	GateTwo->SetWorldLocation(FMath::Lerp(DoorTwoClosedLocation, DoorTwoOpenLocation, CurrentRotationAlpha));
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
	const FVector DoorOneOpenLocation = FVector(DoorOneClosedLocation.X, DoorOneClosedLocation.Y - 100, DoorOneClosedLocation.Z);
	const FVector DoorTwoOpenLocation = FVector(DoorTwoClosedLocation.X, DoorTwoClosedLocation.Y + 100, DoorTwoClosedLocation.Z);

	
	CurrentRotationAlpha = FMath::Clamp(TimeSinceTriggered * GateOpenSpeed, 0.f, 1.f);
	GateOne->SetWorldLocation(FMath::Lerp(DoorOneOpenLocation, DoorOneClosedLocation, CurrentRotationAlpha));
	GateTwo->SetWorldLocation(FMath::Lerp(DoorTwoOpenLocation, DoorTwoClosedLocation, CurrentRotationAlpha));

	if (CurrentRotationAlpha >= 1.f)
	{
		bGateIsOpen = false;
		AuraLight->SetLightFColor(GateRedColour);
		SetActorTickEnabled(false);
		TimeSinceTriggered = 0.f;
		CurrentRotationAlpha = 0.f;
	}
	
}
