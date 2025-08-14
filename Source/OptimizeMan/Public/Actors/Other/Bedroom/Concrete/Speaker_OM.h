// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Both/Abstract/InteractableActor_OM.h"

#include "Speaker_OM.generated.h"

class UGameAudio_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ASpeaker_OM : public AInteractableActor_OM
{
	GENERATED_BODY()

public:
	ASpeaker_OM();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Interact_Implementation() override;

public:
	void PlaySong();
	
	UFUNCTION()
	void PlayNextSong();
	UFUNCTION()
    void StopSong();
	UFUNCTION()
	void TurnOffWidget();
	UFUNCTION()
	virtual void OnPlayModeChanged(EPlayModes InPlayMode) override;



	void SetSongIndex(const int InIndex) {	SongIndex = InIndex; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* ExtraCollider;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	class UWidgetComponent* SpeakerWidget;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UGameAudio_OM* AudioComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<USoundBase*> Songs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundBase* ClickingSound;

	FTimerHandle SongTransitionTimerHandle;
private:
	int SongIndex;

	bool bIsPlaying = false;

	float Volume = 1.f;
};
