#pragma once

#include "CoreMinimal.h"
#include "GameSettings.generated.h"

USTRUCT(BlueprintType)
struct FGameSettings
{
	GENERATED_USTRUCT_BODY()

	FGameSettings()
	: bDarkMode(false),
	LookSensitivity(1.0f),
	MasterVolume(1.f),
	MusicVolume(1.f),
	VoiceVolume(2.f),
	NotificationVolume(1.f),
	SfxVolume(1.f)
	{}
	
	UPROPERTY(BlueprintReadWrite)
	bool bDarkMode;

	UPROPERTY(BlueprintReadWrite)
	float LookSensitivity;

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