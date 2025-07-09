// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "FootstepAudio_OM.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API UFootstepAudio_OM : public UGameAudio_OM
{
	GENERATED_BODY()

public:
	UFootstepAudio_OM();

	virtual void BeginPlay() override;
	
	void Footsteps(float DeltaTime);
	
	void PlayFootstepSound();

protected:
	UPROPERTY()
	APlayerCharacter_OM* Player;
private:
	UPROPERTY(EditAnywhere, Category = "FootstepsSounds")
	TArray<USoundBase*> FootstepSounds;

	bool bInitialFootstep = false;
	int FootstepIndex = 0;
	float FootstepInterval = 0.8f;
	float TimeSinceLastFootstep = 0.f;
};
