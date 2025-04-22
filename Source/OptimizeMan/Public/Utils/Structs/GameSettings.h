#pragma once

#include "CoreMinimal.h"
#include "GameSettings.generated.h"

USTRUCT(BlueprintType)
struct FGameSettings
{
	GENERATED_USTRUCT_BODY()

	FGameSettings()
	: bDarkMode(false),
	MasterVolume(1.f),
	MusicVolume(1.f),
	VoiceVolume(1.f),
	NotificationVolume(1.f),
	SfxVolume(1.f)
	{}
	
	UPROPERTY(BlueprintReadWrite)
	bool bDarkMode;  // --------- Set this to false initially, true rn just for testing

	UPROPERTY(BlueprintReadWrite)
	float MasterVolume;
	UPROPERTY(BlueprintReadWrite)
	float MusicVolume;
	UPROPERTY(BlueprintReadWrite)
	float VoiceVolume;
	UPROPERTY(BlueprintReadWrite)
	float NotificationVolume;
	UPROPERTY(BlueprintReadWrite)
	float SfxVolume;
};