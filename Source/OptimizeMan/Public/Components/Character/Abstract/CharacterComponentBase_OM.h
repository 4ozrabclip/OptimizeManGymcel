// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Utils/Structs/PlayerData.h"
#include "CharacterComponentBase_OM.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract )
class OPTIMIZEMAN_API UCharacterComponentBase_OM : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCharacterComponentBase_OM();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void AddFocus(const float InFocus);
	virtual void ManageSideEffects(ETemporaryEmotionalStates InState) {};

	UPROPERTY()
	class UTodoManagementSubsystem* TodoManager;

	UPROPERTY()
	class UGameInstance_OM* GameInstance;

	UPROPERTY()
	class APlayerCharacter_OM* Player;

	UPROPERTY()
	class UPlayerCharacterAnimInstance_OM* AnimInstance;


};
