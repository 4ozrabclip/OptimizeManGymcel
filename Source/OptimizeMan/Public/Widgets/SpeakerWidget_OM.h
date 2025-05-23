// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpeakerWidget_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API USpeakerWidget_OM : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* StopButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;


	UPROPERTY()
	class ASpeaker_OM* Speaker;

	UFUNCTION()
	void InitSpeaker(ASpeaker_OM* InSpeaker) { Speaker = InSpeaker; }
	
};
