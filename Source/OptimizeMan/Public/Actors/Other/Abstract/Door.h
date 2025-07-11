// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor_OM.h"
#include "Door.generated.h"

UCLASS(Abstract)
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
