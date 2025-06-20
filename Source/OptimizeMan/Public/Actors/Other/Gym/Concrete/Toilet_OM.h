// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Abstract/InteractableActor_OM.h"
#include "Toilet_OM.generated.h"

class UGameAudio_OM;

UCLASS()
class OPTIMIZEMAN_API AToilet_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
public:
	AToilet_OM();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Interact_Implementation() override;
	void ResetBladder();

	void PlaySound(USoundBase* InSound);

	int PlayPissingSound();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UGameAudio_OM* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
	TMap<int, USoundBase*> PissingSounds;

private:
	FTimerHandle ToiletTimerHandle;
	

};
