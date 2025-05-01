// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Audio/GameAudio_OM.h"
#include "NotificationAudio_OM.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API UNotificationAudio_OM : public UGameAudio_OM
{
	GENERATED_BODY()

public:
	UNotificationAudio_OM();

	virtual void BeginPlay() override;
	
	
	void PlayWritingSound();
	void PlaySplatSound();

	void PlayTodoCompletedSound();
protected:
	UPROPERTY()
	APlayerCharacter_OM* Player;

private:
	UPROPERTY(EditAnywhere, Category = "NotifcationSounds")
	USoundBase* TodoWritingSound;

	UPROPERTY(EditAnywhere, Category = "NotificationSounds")
	USoundBase* TodoCompletedSound;

	UPROPERTY(EditAnywhere, Category = "NotificationSounds")
	USoundBase* SplatSound;
	
};
