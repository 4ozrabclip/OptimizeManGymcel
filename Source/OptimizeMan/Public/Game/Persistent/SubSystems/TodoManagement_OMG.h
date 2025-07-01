// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/SubSystems/TodoManagementSubsystem.h"
#include "TodoManagement_OMG.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UTodoManagement_OMG : public UTodoManagementSubsystem
{
	GENERATED_BODY()
public:
	/** Inits **/
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void InitializeTodos() override;
	virtual void ProcessPotentialTodos() override;

	/** Processing **/
	virtual void CompleteTodo(const FGameplayTag TodoCompletedTag) override;
	
	/** Helpers **/
	void TimerToTryCasts();
	void TryCasts();

private:
	/** Class Cache **/
	UPROPERTY()
	class UGameInstance_OMG* GameInstance;
	UPROPERTY()
	class APlayerCharacter_OM* Player;
	UPROPERTY()
	class UNotificationAudio_OM* NotificationAudio;


	/** Timer Handles **/
	FTimerHandle InitializeVariablesHandle;
	FTimerHandle DelayForPlayerAchievementsHandle;
};

