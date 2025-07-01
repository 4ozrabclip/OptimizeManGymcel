// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Structs/TodoData.h"
#include "SubSystems/GameInstanceSubsystem.h"
#include "TodoManagementSubsystem.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnPointsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTodoComplete);
UCLASS(Abstract)
class OPTIMIZEMAN_API UTodoManagementSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	/** Initialize **/
	virtual void Initialize(FSubsystemCollectionBase& Collection) override {};
	virtual void InitializeTodos() {};
	
	/** Processing **/
	UFUNCTION()
	virtual void ProcessPotentialTodos() {};

	virtual void CompleteTodo(const FGameplayTag TodoCompletedTag) {};
	void UpdateTodoList();
	void ProcessTodoHelper(bool bTodoCondition, FName InTodo);
	void DelayForPlayerAchievements(TArray<FGameplayTag> TodoCompletedTags, float TimeTilCheck = 3.f);

	/** Setters/Adders **/
	void SetCurrentTodos(const FString& Todo1 = "", const FString& Todo2 = "", const FString& Todo3 = "");
	void AddToCurrentTodos(const FString& InTodo, const bool bClearCurrentTodo = false);
	void AddToPotentialTodos(FName InTodo);
	




	/** Delegates **/
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTodoComplete OnTodoComplete;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTodoComplete OnPointsChanged;


protected:
	/** Arrays **/
	UPROPERTY()
	TArray<FTodoItem> TodoArray;
	UPROPERTY()
	TArray<FTodoItem> PotentialTodos;
	UPROPERTY()
	TArray<FTodoItem> CurrentTodoArray;
	
	
private:
	/** Class Cache **/
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	UPROPERTY()
	class APlayerCharacterBase_OM* Player;
	UPROPERTY()
	class UNotificationAudio_OM* NotificationAudio;

	/** Timer Handles **/
	FTimerHandle InitializeVariablesHandle;
	FTimerHandle DelayForPlayerAchievementsHandle;

public:
	/** Getters/Checkers **/
	bool CurrentTodoListContainsName(const FString& InName, bool InIsComplete = false);
	bool CurrentTodoListContainsLayer(const FString& InLayer, bool InIsComplete = false);
	TArray<FTodoItem>& GetPotentialTodos() { return PotentialTodos;}
	TArray<FTodoItem>& GetCurrentTodoArray() { return CurrentTodoArray;}
	FString GetTodoName(const int TodoIndex);
};
