// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Abstract/InteractableActor_OM.h"
#include "Bed_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API ABed_OM : public AInteractableActor_OM
{
	GENERATED_BODY()

public:
	ABed_OM();
	
	virtual void Interact_Implementation() override;
	void SleepDelay(const float FadeDuration);

	virtual void BeginPlay() override;

	virtual void DarkModeToggle(const bool bIsDarkMode) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* ExtraCollider;

	void SetIsSleeping(const bool InIsSleeping);
	bool GetIsSleeping() const;

private:
	bool bIsSleeping;

	UPROPERTY()
	class ABedroomGameModeBase_OM* GameMode;

protected:
	FTimerHandle SleepTimerHandle;
};
