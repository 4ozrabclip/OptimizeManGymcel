// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Gym/Equipment/ExerciseEquipment_OM.h"

#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Items/Gym/GymCamera.h"
#include "Utils/GameInstance_OM.h"

AExerciseEquipment_OM::AExerciseEquipment_OM()
{
	Camera = nullptr;
	Player = nullptr;
	LookAtCameraPosition = FVector::ZeroVector;
	LookAtCameraRotation = FRotator::ZeroRotator;

}
void AExerciseEquipment_OM::BeginPlay()
{
	Super::BeginPlay();
	OriginalPosition = GetActorTransform();
}

void AExerciseEquipment_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (!Player || !Player->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Player is invalid"));
		return;
	}
	if (GameInstance && GameInstance->GetGymResStats().Energy > 0)
	{
		Player->SetCurrentPlayMode(EPlayModes::WorkoutMode, this);
	}
}

FRotator AExerciseEquipment_OM::GetLookAtCameraRotation() const
{
	return LookAtCameraRotation;
}

FVector AExerciseEquipment_OM::GetLookAtCameraPosition() const
{
	return LookAtCameraPosition;
}

AActor* AExerciseEquipment_OM::GetGymCamera() const
{
	return Camera;
}

FTransform AExerciseEquipment_OM::GetOriginalPosition() const
{
	return OriginalPosition;
}
