// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Abstract/CharacterComponentBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

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
	
	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is NULL in Character Component base"));
		return;
	}

	
	AnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(Player->GetMesh()->GetAnimInstance());
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is NULL"));
		return;
	}
}

void UCharacterComponentBase_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void UCharacterComponentBase_OM::AddFocus(const float InFocus)
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	FGymResStats& GymResStats = GameInstance->GetGymResStats();

	const float DifficultyMultiplier = GameInstance->GetDifficultyMultiplier();

	const float FocusAdd = InFocus * DifficultyMultiplier;
	
	GameInstance->AddGymResStats(GymResStats.Focus, FocusAdd);
}

