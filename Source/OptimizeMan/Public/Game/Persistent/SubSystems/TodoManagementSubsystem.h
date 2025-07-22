// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Utils/Structs/TodoData.h"
#include "SubSystems/GameInstanceSubsystem.h"
#include "TodoManagementSubsystem.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnPointsChanged);
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
	void SetCurrentTodos(const FString& Todo1 = "", const FString& Todo2 = "", const FString& Todo3 = "");
	void AddToCurrentTodos(const FString& InTodo, const bool bClearCurrentTodo = false);
	void RemoveFromCurrentTodos(const FString& InTodo);
	void AddToPotentialTodos(ETodoArrayList InTodo);
	

	void CompleteTodo(const FGameplayTag TodoCompletedTags);
	void UpdateTodoList();
	//Helpers
	bool CurrentTodoListContainsName(const FString& InName, bool InIsComplete = false);
	bool CurrentTodoListContainsLayer(const FString& InLayer, bool InIsComplete = false);
	void DelayForPlayerAchievements(TArray<FGameplayTag> TodoCompletedTags, float TimeTilCheck = 3.f);


	
	//UFUNCS
	UFUNCTION()
	void ProcessPotentialTodos();
	void ProcessTodoHelper(bool bTodoCondition, ETodoArrayList InTodo);

	//DELEGATES
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTodoComplete OnTodoComplete;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTodoComplete OnPointsChanged;


	//Getters and Setters
	TArray<FTodoItem>& GetPotentialTodos() { return PotentialTodos;}
	TArray<FTodoItem>& GetCurrentTodoArray() { return CurrentTodoArray;}
	FString GetTodoName(const int TodoIndex);
	


private:
	//UPROPERTYS
	UPROPERTY()
	TArray<FTodoItem> TodoArray;
	UPROPERTY()
	TArray<FTodoItem> PotentialTodos;
	UPROPERTY()
	TArray<FTodoItem> CurrentTodoArray;

	//Pointer Objects
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	UPROPERTY()
	class APlayerCharacter_OM* Player;
	UPROPERTY()
	class UNotificationAudio_OM* NotificationAudio;

	//Timers
	FTimerHandle InitializeVariablesHandle;
	FTimerHandle DelayForPlayerAchievementsHandle;
};
