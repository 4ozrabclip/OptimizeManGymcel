// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Abstract/ExerciseEquipment_OM.h"

#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Actors/Other/Gym/Concrete/GymCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Widgets/Gym/Abstract/ExerciseSelectionParentWidget_OM.h"


AExerciseEquipment_OM::AExerciseEquipment_OM()
{
	SelectWorkoutWidget = nullptr;
	CurrentWeightClass = EWeightClass::Light_A;
	CurrentWeight = 20.f;
	Camera = nullptr;
	Player = nullptr;
	LookAtCameraPosition = FVector::ZeroVector;
	LookAtCameraRotation = FRotator::ZeroRotator;

	SelectWorkoutWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	SelectWorkoutWidget->SetupAttachment(RootComponent);
	SelectWorkoutWidget->SetVisibility(false);
	SelectWorkoutWidget->SetWidgetSpace(EWidgetSpace::Screen);
	SelectWorkoutWidget->SetDrawSize(FVector2D(320.f, 180.f));
}
void AExerciseEquipment_OM::BeginPlay()
{
	Super::BeginPlay();
	OriginalPosition = GetActorTransform();

	if (bUnderConstruction)
		SetInteractableWidgetText("Under Construction");

	if (UExerciseSelectionParentWidget_OM* Widg = Cast<UExerciseSelectionParentWidget_OM>(SelectWorkoutWidget->GetWidget()))
	{
		Widg->InitEquipment(this);
	}
}
void AExerciseEquipment_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		FVector2D Delta = FVector2D(this->GetActorLocation()) - FVector2D(Player->GetActorLocation());
		
		if (Delta.Size() > 200)
		{
			TurnOffWidget();
		}
	}
}

void AExerciseEquipment_OM::TurnOffWidget()
{
	SelectWorkoutWidget->SetVisibility(false);
	//InteractableInterfaceProperties.bIsInteractable = true;
	SetIsInteractable(true);
	Player->SetToUIMode(false);
	PlayerController->HideUnhideInteractableWidget(false);
	SetActorTickEnabled(false);
}

void AExerciseEquipment_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (bUnderConstruction) return;

	if (!PlayerController)
		PlayerController = Cast<APlayerController_OM>(Player->GetController());

	if (!PlayerController) return;
	
	PlayerController->HideUnhideInteractableWidget(true);
	SelectWorkoutWidget->SetVisibility(true);
	SetIsInteractable(false);
	//InteractableInterfaceProperties.bIsInteractable = false;
	Player->SetToUIMode(true, true);
}

void AExerciseEquipment_OM::StartWorkoutMode()
{
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

void AExerciseEquipment_OM::ChangeWeight(const float InWeight)
{
	CurrentWeight = InWeight;

	SetWeightClass();

	if (Equipment.Num() <= 0) return;

	for (const FEquipmentData Equip : Equipment)
	{
		if (Equip.WeightClass == CurrentWeightClass && Equip.EquipmentMesh != nullptr)
		{
			ItemMesh->SetStaticMesh(Equip.EquipmentMesh);
			break;
		}
	}
}

void AExerciseEquipment_OM::SetWeightClass()
{
	if (CurrentWeight <= 20)
		CurrentWeightClass = EWeightClass::Light_A;
	else if (CurrentWeight <= 30)
		CurrentWeightClass = EWeightClass::Light_B;
	else if (CurrentWeight <= 40)
		CurrentWeightClass = EWeightClass::Light_C;
	else if (CurrentWeight <= 50)
		CurrentWeightClass = EWeightClass::Medium_A;
	else if (CurrentWeight <= 60)
		CurrentWeightClass = EWeightClass::Medium_B;
	else if (CurrentWeight <= 70)
		CurrentWeightClass = EWeightClass::Medium_C;
	else if (CurrentWeight <= 80)
		CurrentWeightClass = EWeightClass::Heavy_A;
	else if (CurrentWeight <= 100)
		CurrentWeightClass = EWeightClass::Heavy_B;
	else
		CurrentWeightClass = EWeightClass::Heavy_C;
}

FRotator AExerciseEquipment_OM::GetLookAtCameraRotation() const
{
	return LookAtCameraRotation;
}

FVector AExerciseEquipment_OM::GetLookAtCameraPosition() const
{
	return LookAtCameraPosition;
}

ACameraActor* AExerciseEquipment_OM::GetGymCamera() const
{
	return Camera;
}

FTransform AExerciseEquipment_OM::GetOriginalPosition() const
{
	return OriginalPosition;
}
