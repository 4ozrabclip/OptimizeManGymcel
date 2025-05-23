// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetasoundSource.h"
#include "GymSpeaker_OM.generated.h"

class UGameAudio_OM;

enum class EBiquadFilterType : int32
{
	LowPass = 0,
	HighPass = 1,
	BandPass = 2,
	BandStop = 3,
	AllPass = 4,
	LowShelf = 5,
	HighShelf = 6,
	PeakingEQ = 7
};
UCLASS()
class OPTIMIZEMAN_API AGymSpeaker_OM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGymSpeaker_OM();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void PlayGymMusic();


	UFUNCTION()
	void OnGymSongFinished();

	void SetSong(USoundWave* InSong) const;


public:
	void ChangePitch(float InNewPitch);
	void SetBiquadFilter(EBiquadFilterType InType, const int InFrequency, const float InGain, const float InBandwidth);
	void TurnWaveShaperOnOff(bool bWaveShaperOn);
	void TurnEffectChannelOnOff(bool bEffectChannelOn);


private:
	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UGameAudio_OM* MusicPlayer;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<UMetaSoundSource> MetaSound;
	UPROPERTY()
	class APlayerCharacter_OM* Player;
	UPROPERTY()
	class UGameInstance_OM* GameInstance;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Songs")
	TArray<USoundWave*> GymSongs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Songs")
	TArray<USoundWave*> GymSongs_Goblin;


private:
	int CurrentBiquadFrequency = 20000;

	bool bMusicPlaying = false;

};

