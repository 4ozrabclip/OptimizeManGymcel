// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Utils/Structs/ConsumableData.h"
#include "ConsumablesSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConsumableAdded, FConsumableType, InConsumable);
UCLASS()
class OPTIMIZEMAN_API UConsumablesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;


	UPROPERTY(BlueprintReadOnly, Category = Events)
	FOnConsumableAdded OnConsumableAdded;

private:
	TArray<FConsumableType> CurrentConsumables;
public:
	TArray<FConsumableType> GetCurrentConsumables() const { return CurrentConsumables; }
	void AddConsumable(const FConsumableType& InConsumable);
	void RemoveConsumable(const FConsumableType& InConsumable);
	void ClearConsumables() { CurrentConsumables.Empty(); }
	
};
