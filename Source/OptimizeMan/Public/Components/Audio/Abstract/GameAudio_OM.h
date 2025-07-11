// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Components/AudioComponent.h"
#include "GameAudio_OM.generated.h"

enum class EAudioTypes : uint8;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OPTIMIZEMAN_API UGameAudio_OM : public UAudioComponent
{
	GENERATED_BODY()
public:
	UGameAudio_OM();
protected:
	virtual void BeginPlay() override;
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void GetAndSetVolume();

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

