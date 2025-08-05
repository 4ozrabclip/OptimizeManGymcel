// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/GymCamera.h"

#include "CineCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "Game/Persistent/GameInstance_OM.h"

AGymCamera::AGymCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	GameInstance = nullptr;

	GetCameraComponent()->SetConstraintAspectRatio(false);
}

void AGymCamera::BeginPlay()
{
	Super::BeginPlay();
	DefaultTransform = GetActorTransform();
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	if (GameInstance)
	{
		GameInstance->OnEmotionalStateChanged.AddDynamic(this, &AGymCamera::OnEmotionalStateChanged);
	}
}
// Rewrite this
void AGymCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetCineCameraComponent()) return;

	switch (AutoState)
	{
	case ECameraAutoState::Idle:
		HoldTimer += DeltaTime;
		if (HoldTimer >= HoldDuration)
		{
			AutoState = ECameraAutoState::ZoomingOut;
			HoldTimer = 0.0f;
		}
			break;

	case ECameraAutoState::ZoomingIn:
		{
			float CurrentFOV = GetCineCameraComponent()->FieldOfView;
			CurrentFOV = FMath::FInterpTo(CurrentFOV, ZoomedFOV, DeltaTime, FOVInterpSpeed);
			GetCineCameraComponent()->SetFieldOfView(CurrentFOV);

			float& Focus = GetCineCameraComponent()->FocusSettings.ManualFocusDistance;
			Focus = FMath::FInterpTo(Focus, FocusNear, DeltaTime, FocusInterpSpeed);

			if (FMath::IsNearlyEqual(CurrentFOV, ZoomedFOV, 0.1f))
			{
				AutoState = ECameraAutoState::Hold;
				HoldTimer = 0.0f;
			}
			break;
		}

	case ECameraAutoState::Hold:
		HoldTimer += DeltaTime;
		if (HoldTimer >= HoldDuration)
		{
			AutoState = ECameraAutoState::ZoomingOut;
			HoldTimer = 0.0f;
		}
		break;

	case ECameraAutoState::ZoomingOut:
		{
			float CurrentFOV = GetCineCameraComponent()->FieldOfView;
			CurrentFOV = FMath::FInterpTo(CurrentFOV, NormalFOV, DeltaTime, FOVInterpSpeed);
			GetCineCameraComponent()->SetFieldOfView(CurrentFOV);

			float& Focus = GetCineCameraComponent()->FocusSettings.ManualFocusDistance;
			Focus = FMath::FInterpTo(Focus, FocusFar, DeltaTime, FocusInterpSpeed);

			if (FMath::IsNearlyEqual(CurrentFOV, NormalFOV, 0.1f))
			{
				AutoState = ECameraAutoState::Idle; 
			}
			break;
		}
	}
	
}

void AGymCamera::OnEmotionalStateChanged(EPlayerEmotionalStates NewState)
{
	switch (NewState)
	{
	case EPlayerEmotionalStates::Doomer:
		{
			UE_LOG(LogTemp, Error, TEXT("doom in gym cam"));
			SetActorTransform(DoomerTransform);
			break;
		}
	case EPlayerEmotionalStates::Cope:
		{
			UE_LOG(LogTemp, Error, TEXT("cope in gym cam"));
			SetActorTransform(DefaultTransform);
			break;
		}
	case EPlayerEmotionalStates::Gigachad:
		{
			UE_LOG(LogTemp, Error, TEXT("giga in gym cam"));
			SetActorTransform(GigachadTransform);
			break;
		}
	case EPlayerEmotionalStates::GoblinMode:
		{
			UE_LOG(LogTemp, Error, TEXT("goblin in gym cam1"));
			SetActorTransform(GoblinTransform);
			UE_LOG(LogTemp, Error, TEXT("goblin in gym cam2"));
			break;
		}
	case EPlayerEmotionalStates::Grindset:
		{
			UE_LOG(LogTemp, Error, TEXT("grindset in gym cam"));
			SetActorTransform(GrindsetTransform);
			break;
		}
	default:
		SetActorTransform(DefaultTransform);
		UE_LOG(LogTemp, Error, TEXT("Default in gym cam"));
		return;
	}
}

