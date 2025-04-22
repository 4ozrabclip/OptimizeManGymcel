// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Audio/GameAudio_OM.h"
#include "PlayerVoiceAudio_OM.generated.h"

enum EPlayerEmotionalStates : uint8;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API UPlayerVoiceAudio_OM : public UGameAudio_OM
{
	GENERATED_BODY()

public:
	UPlayerVoiceAudio_OM();

	virtual void BeginPlay() override;
	
	
	void InjurySoundEffects(const EExerciseType CurrentExerciseType);

	void MinorInjurySoundEffects(const EExerciseType CurrentExerciseType);

	void WorkoutGruntSoundEffects(const EExerciseType CurrentExerciseType);
	void UpsetSoundEffects();
	void GrumpySoundEffects();

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
