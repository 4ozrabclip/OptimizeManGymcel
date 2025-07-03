// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "NotificationAudio_OM.generated.h"

class APlayerCharacterBase_OM;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMANCORE_API UNotificationAudio_OM : public UGameAudio_OM
{
	GENERATED_BODY()

public:
	UNotificationAudio_OM();
	virtual void BeginPlay() override;

	
	UFUNCTION()
	void PlaySplatSound();
	UFUNCTION()
	void PlayWritingSound();
	UFUNCTION()
	void PlayTodoCompletedSound();


protected:
	/** Class Cache **/
	UPROPERTY()
	APlayerCharacterBase_OM* Player;


	/** Sounds **/
	UPROPERTY(EditAnywhere, Category = "NotifcationSounds")
	USoundBase* TodoWritingSound;

	UPROPERTY(EditAnywhere, Category = "NotificationSounds")
	USoundBase* TodoCompletedSound;

	UPROPERTY(EditAnywhere, Category = "NotificationSounds")
	USoundBase* SplatSound;
	
};
