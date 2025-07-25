// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "PlayerAmbience_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UPlayerAmbience_OM : public UGameAudio_OM
{
	GENERATED_BODY()

public:
	UPlayerAmbience_OM();
	void PlayAmbience(bool bKeepPlaying = true);

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnAmbienceSongFinished();

protected:
	UPROPERTY()
	APlayerCharacter_OM* Player;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionAmbience")
	TArray<USoundBase*> DoomerEmotionAmbiences;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Songs")
	TArray<USoundBase*> GrindsetEmotionAmbiences;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Songs")
	TArray<USoundBase*> GoblinEmotionAmbiences;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Songs")
	TArray<USoundBase*> GigaChadEmotionAmbiences;
	
};

