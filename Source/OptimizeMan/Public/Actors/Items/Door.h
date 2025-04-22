// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptimizeMan/Public/Actors/InteractableActor_OM.h"
#include "Door.generated.h"

UCLASS()
class OPTIMIZEMAN_API ADoor : public AInteractableActor_OM
{
	GENERATED_BODY()
	
public:
	ADoor();

	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation() override;
	virtual void ClearTimers();

	virtual void OpenDoor();

	virtual void DoorOpenDelay(FName LevelToChangeTo, const float FadeDuration, TFunction<void()> Cleanup);

	bool GetHasOpenedDoor() const;
	void SetHasOpenedDoor(const bool InhasOpenedDoor);

	/*UFUNCTION();
	void SetTurnsOffMusic(const bool InTurnsOffMusic) { bTurnsOffMusic = InTurnsOffMusic; };*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bTurnsOffMusic = false;

protected:
	UPROPERTY(EditAnywhere)
	FString LevelToLoad;
	
	FTimerHandle TimerHandle;


	bool bWantsToContinue = false;

private:
	bool bHasOpenedDoor;


};
