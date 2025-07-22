// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
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

	
	UFUNCTION()
	void PlaySplatSound();
	UFUNCTION()
	void PlayWritingSound();
	UFUNCTION()
	void PlayCrossingOutSound();
	UFUNCTION()
	void PlayTodoCompletedSound();


private:
	UPROPERTY()
	APlayerCharacter_OM* Player;
	UPROPERTY(EditAnywhere, Category = "NotifcationSounds")
	USoundBase* TodoWritingSound;
	UPROPERTY(EditAnywhere, Category = "NotifcationSounds")
	USoundBase* TodoCrossingOutSound;

	UPROPERTY(EditAnywhere, Category = "NotificationSounds")
	USoundBase* TodoCompletedSound;

	UPROPERTY(EditAnywhere, Category = "NotificationSounds")
	USoundBase* SplatSound;
	
};
