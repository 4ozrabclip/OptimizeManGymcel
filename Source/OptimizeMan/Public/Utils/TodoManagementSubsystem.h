// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Structs/TodoData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TodoManagementSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTodoComplete);
UCLASS()
class OPTIMIZEMAN_API UTodoManagementSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void TimerToTryCasts();
	void TryCasts();
	void InitializeTodos();
	void AddToPotentialTodos(ETodoArrayList InTodo);

	
	void SetCurrentTodos(const FString& Todo1 = "", const FString& Todo2 = "", const FString& Todo3 = "");
	void AddToCurrentTodos(const FString& InTodo, const bool bClearCurrentTodo = false);
	
	UFUNCTION()
	void ProcessPotentialTodos();

	
	TArray<FTodoItem>& GetPotentialTodos() { return PotentialTodos;}
	TArray<FTodoItem>& GetCurrentTodoArray() { return CurrentTodoArray;}
	FString GetTodoName(const int TodoIndex);
	void DelayForPlayerAchievements(TArray<FGameplayTag> TodoCompletedTags, float TimeTilCheck = 3.f);
	void CompleteTodo(const FGameplayTag TodoCompletedTags);
	void UpdateTodoList();

	bool CurrentTodoListContainsName(const FString& InName, bool InIsComplete = false);
	bool CurrentTodoListContainsLayer(const FString& InLayer, bool InIsComplete = false);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTodoComplete OnTodoComplete;
protected:


	
	UPROPERTY()
	TArray<FTodoItem> TodoArray;
	UPROPERTY()
	TArray<FTodoItem> PotentialTodos;
	UPROPERTY()
	TArray<FTodoItem> CurrentTodoArray;

private:
	UPROPERTY()
	class UGameInstance_OM* GameInstance;

	UPROPERTY()
	class APlayerCharacter_OM* Player;
	
	UPROPERTY()
	class UNotificationAudio_OM* NotificationAudio;
	
	FTimerHandle InitializeVariablesHandle;
	FTimerHandle DelayForPlayerAchievementsHandle;
};
