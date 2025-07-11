// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Bedroom/Concrete/Speaker_OM.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "SpeakerWidget_OM.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API USpeakerWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;
	UPROPERTY(meta = (BindWidget))
	UButton* StopButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;


	UPROPERTY()
	ASpeaker_OM* Speaker;

	UFUNCTION()
	void InitSpeaker(const TSoftObjectPtr<ASpeaker_OM>& InSpeaker) { Speaker = InSpeaker.Get(); }
	
};
