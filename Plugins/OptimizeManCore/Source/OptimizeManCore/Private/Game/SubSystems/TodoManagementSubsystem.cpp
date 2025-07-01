// Copyright © 2025 4ozStudio. All rights reserved.


#include "Game/SubSystems/TodoManagementSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Structs/TodoData.h"


void UTodoManagementSubsystem::AddToPotentialTodos(const FName InTodo)
{
	for (const FTodoItem& Todo : TodoArray)
	{
		if (Todo.Name == InTodo)
		{
			PotentialTodos.Add(Todo);
			return;
		}
	}
}

void UTodoManagementSubsystem::ProcessTodoHelper(bool bTodoCondition, const FName InTodo)
{
	if (bTodoCondition)
		AddToPotentialTodos(InTodo);
}

void UTodoManagementSubsystem::SetCurrentTodos(const FString& Todo1, const FString& Todo2, const FString& Todo3)
{
	CurrentTodoArray.Empty();

	// See if the todos text we entered in parameter are in our TodoArray, then add them to our CurrentTodoArray
	for (const FTodoItem& Item : TodoArray)
	{
		if (Item.Name == Todo1)
		{
			CurrentTodoArray.Add(Item);
		}
		else if (Item.Name == Todo2)
		{
			CurrentTodoArray.Add(Item);
		}
		else if (Item.Name == Todo3)
		{
			CurrentTodoArray.Add(Item);
		}
	}
}

void UTodoManagementSubsystem::AddToCurrentTodos(const FString& InTodo, const bool bClearCurrentTodo)
{
	if (bClearCurrentTodo) CurrentTodoArray.Empty();

	if (CurrentTodoArray.Num() > 3) return;

	
	for (const FTodoItem& Item : TodoArray)
	{
		if (Item.Name == InTodo)
		{
			CurrentTodoArray.Add(Item);
		}
	}
}
FString UTodoManagementSubsystem::GetTodoName(const int TodoIndex)
{
	if (CurrentTodoArray.IsValidIndex(TodoIndex))
	{
		return CurrentTodoArray[TodoIndex].Name;
	}
	return FString("");
}
void UTodoManagementSubsystem::DelayForPlayerAchievements(TArray<FGameplayTag> TodoCompletedTags, float TimeTilCheck)
{
	GetWorld()->GetTimerManager().ClearTimer(DelayForPlayerAchievementsHandle);

	short Index = 0;

	FTimerDelegate StaggerDelegate;
	StaggerDelegate.BindLambda([this, TodoCompletedTags, Index, StaggerDelegate, TimeTilCheck]() mutable
	{
		if (TodoCompletedTags.IsValidIndex(Index))
			CompleteTodo(TodoCompletedTags[Index]);
			Index++;
		
		if (Index < TodoCompletedTags.Num())
			GetWorld()->GetTimerManager().SetTimer(DelayForPlayerAchievementsHandle,StaggerDelegate, TimeTilCheck, true);
	});


	GetWorld()->GetTimerManager().SetTimer(DelayForPlayerAchievementsHandle,StaggerDelegate, TimeTilCheck, true);

}
void UTodoManagementSubsystem::UpdateTodoList()
{
	for (FTodoItem& Item : CurrentTodoArray)
	{
		if (Item.bIsCompleted)
		{
			Item.Name = Item.CompletedName;
		}
	}
}

bool UTodoManagementSubsystem::CurrentTodoListContainsName(const FString& InName, bool InIsComplete)
{
	for (FTodoItem& Item : CurrentTodoArray)
	{
		if (Item.Name == InName && Item.bIsCompleted == InIsComplete) return true;
	}
	return false;
}
bool UTodoManagementSubsystem::CurrentTodoListContainsLayer(const FString& InLayer, bool InIsComplete)
{
	for (FTodoItem& Item : CurrentTodoArray)
	{
		if (Item.Level == InLayer && Item.bIsCompleted == InIsComplete)
		{
			return true;
		}
	}
	return false;
}