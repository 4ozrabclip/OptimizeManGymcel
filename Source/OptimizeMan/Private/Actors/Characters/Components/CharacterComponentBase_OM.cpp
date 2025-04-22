// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Components/CharacterComponentBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Utils/GameInstance_OM.h"
#include "Utils/TodoManagementSubsystem.h"

UCharacterComponentBase_OM::UCharacterComponentBase_OM()
{
	PrimaryComponentTick.bCanEverTick = true;

	TodoManager = nullptr;
	GameInstance = nullptr;
	Player = nullptr;
	AnimInstance = nullptr;
}

void UCharacterComponentBase_OM::BeginPlay()
{
	Super::BeginPlay();
	

	GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is null, cast may have failed"));
		return;
	}

	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("TodoManager is null in your Player Component base"));
		return;
	}
	
	Player = Cast<APlayerCharacter_OM>(GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is NULL"));
		return;
	}

	
	AnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(Player->GetMesh()->GetAnimInstance());
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is NULL"));
		return;
	}
}



