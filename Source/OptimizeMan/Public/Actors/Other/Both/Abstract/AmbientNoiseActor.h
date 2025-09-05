// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetasoundSource.h"
#include "NonInteractableActor_OM.h"
#include "Utils/Structs/AudioTypes.h"
#include "AmbientNoiseActor.generated.h"

class UGameAudio_OM;

UCLASS(Abstract)
class OPTIMIZEMAN_API AAmbientNoiseActor : public ANonInteractableActor_OM
{
	GENERATED_BODY()
public:
	AAmbientNoiseActor();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
public:
	void ChangePitch(float InNewPitch);
	void SetBiquadFilter(EBiquadFilterType InType, const int InFrequency, const float InGain, const float InBandwidth);
	void TurnWaveShaperOnOff(bool bWaveShaperOn);
	void TurnEffectChannelOnOff(bool bEffectChannelOn);

	UFUNCTION(BlueprintCallable)
	void PlayMusic();
	UFUNCTION()
	void OnSongFinished();



protected:
	void SetSong(USoundWave* InSong) const;



//Components
	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UGameAudio_OM* MusicPlayer;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<UMetaSoundSource> MetaSound;


//Cache
	UPROPERTY()
	class APlayerCharacter_OM* Player;
	UPROPERTY()
	class UGameInstance_OM* GameInstance;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Songs")
	TArray<USoundWave*> Songs_Cope;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Songs")
	TArray<USoundWave*> Songs_Goblin;

	
	int CurrentBiquadFrequency = 20000;

	bool bMusicPlaying = false;

};
