// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor_OM.h"
#include "Utils/Structs/ConsumableData.h"
#include "Consumable_OM.generated.h"


class UAbilitySystemComponent_OM;
class UGameplayEffect;
class UConsumablesSubsystem;
class UBoxComponent;
class UGameAudio_OM;

UCLASS(Abstract)
class OPTIMIZEMAN_API AConsumable_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
public:
	AConsumable_OM();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Interact_Implementation() override;

	void PlayConsumeSound();
	UFUNCTION()
	void DestroyConsumable() { Destroy(); }
	FConsumableType& GetConsumableType() { return ConsumableType; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable Type")
	FConsumableType ConsumableType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UGameAudio_OM* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TArray<USoundBase*> ConsumeSounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<UGameplayEffect> EffectToApply;


	
	
	UPROPERTY()
	UAbilitySystemComponent_OM* AbSysComp;


	FTimerHandle TimerTilInteractableHandle;
	
};
