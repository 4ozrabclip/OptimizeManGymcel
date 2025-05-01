// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/Player/Components/Exercise_OM.h"
#include "Components/AudioComponent.h"
#include "GameAudio_OM.generated.h"

enum class EAudioTypes : uint8;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API UGameAudio_OM : public UAudioComponent
{
	GENERATED_BODY()

public:
	UGameAudio_OM();
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateAudioSettings(const float InMasterVolume, const float InVoiceVolume, const float InMusicVolume, const float InNotificationVolume, const float InSfxVolume);

	UFUNCTION()
	void SetAudioType(const EAudioTypes InType) { AudioType = InType; }

	UPROPERTY()
	float CurrentVolumeMultiplier;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio", meta=(AllowPrivateAccess="true"))
	EAudioTypes AudioType;

	
	
	
};

