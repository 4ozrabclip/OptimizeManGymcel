// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Audio/GameAudio_OM.h"
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
