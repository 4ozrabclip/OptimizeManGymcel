// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Both/Concrete/InfoSign_OM.h"
#include "Widgets/Both/Abstract/PlayModeBaseWidget_OM.h"
#include "TutorialWidget_OM.generated.h"

class AInfoSign_OM;
class UCheckBox;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UTutorialWidget_OM : public UPlayModeBaseWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void OnExitButtonClicked() override;

	void InitInfoSign(const TSoftObjectPtr<AInfoSign_OM>& InInfoSign) { InfoSign = InInfoSign.Get(); }
	
protected:
	UPROPERTY(meta = (BindWidget))
	UCheckBox* TurnTutorialsOff_CheckBox;


private:
	UPROPERTY()
	AInfoSign_OM* InfoSign;
};
