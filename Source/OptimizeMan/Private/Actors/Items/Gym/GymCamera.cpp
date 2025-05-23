// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Gym/GymCamera.h"
#include "Camera/CameraComponent.h"
#include "Utils/GameInstance_OM.h"

AGymCamera::AGymCamera()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(RootComponent);
	
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

void AGymCamera::OnEmotionalStateChanged(EPlayerEmotionalStates NewState)
{
	UE_LOG(LogTemp, Error, TEXT("CALLED IN GYM CAM"));
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

