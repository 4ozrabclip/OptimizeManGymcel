// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Minigames/Abstract/MinigamesBase_OM.h"
#include "SlotsMinigame_OM.generated.h"

class USlotReel_OM;
class UButton;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API USlotsMinigame_OM : public UMinigamesBase_OM
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void PlayButton_OnClick();


private:
	UFUNCTION()
	void OnScrollFinished();
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	USlotReel_OM* SlotReel_1;
	UPROPERTY(meta = (BindWidget))
	USlotReel_OM* SlotReel_2;
	UPROPERTY(meta = (BindWidget))
	USlotReel_OM* SlotReel_3;
};
