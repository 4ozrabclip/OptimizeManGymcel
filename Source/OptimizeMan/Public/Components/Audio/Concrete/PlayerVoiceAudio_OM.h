// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "PlayerVoiceAudio_OM.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBreathingIntensity : uint8
{
	Soft = 0,
	Normal = 1,
	Intense = 2,
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBreathTaken, EBreathingIntensity, Intensity);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API UPlayerVoiceAudio_OM : public UGameAudio_OM
{
	GENERATED_BODY()

public:
	UPlayerVoiceAudio_OM();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	
	void InjurySoundEffects(const EExerciseType CurrentExerciseType);

	void MinorInjurySoundEffects(const EExerciseType CurrentExerciseType);

	void WorkoutGruntSoundEffects(const EExerciseType CurrentExerciseType);
	void UpsetSoundEffects();
	void GrumpySoundEffects();


public:
	UFUNCTION()
	void PlayBreathingInterval();
	
	void PlayBreathingSound();


	/** Setters/Adders **/
	void SetBreathingTimerInterval(const float InInterval) { BreathingTimerInterval = InInterval; }
	void SetBreathingIntensity(const EBreathingIntensity InIntensity) { CurrentBreathingIntensity = InIntensity; } 
	
	
	/** Getters/Finders **/
	



	/** Events / Delegates  **/
	UPROPERTY(EditDefaultsOnly, Category = Events)
	FOnBreathTaken OnBreathTaken;
	
private:
	/** Timer Handles **/
	FTimerHandle BreathingTimerHandle;

	/** Private Paramaters **/
	float BreathingTimerInterval = 6.f;
	EBreathingIntensity CurrentBreathingIntensity = EBreathingIntensity::Soft;




protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sfx")
	TArray<USoundBase*> BreathingSounds_Soft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sfx")
	TArray<USoundBase*> BreathingSounds_Normal;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sfx")
	TArray<USoundBase*> BreathingSounds_Intense;

	
protected:
	UPROPERTY()
	APlayerCharacter_OM* Player;
private:
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> MajorInjurySounds;
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> MajorInjurySounds_Intense;
	

	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> MinorInjurySounds;
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> MinorInjurySounds_Intense;
	
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> FunnyGruntSounds;
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> FunnyGruntSounds_Intense;

	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> UpsetSounds;
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> UpsetSounds_Doomer;
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> UpsetSounds_Goblin;
	
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> GrumpySounds;
	UPROPERTY(EditAnywhere, Category = "PlayerVoiceSounds")
	TArray<USoundBase*> GrumpySounds_Intense;

	
};
