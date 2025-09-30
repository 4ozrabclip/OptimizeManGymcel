// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/PlayModeBaseWidget_OM.h"
#include "TodoList_OM.generated.h"

/**
 * 
 */
class UTextBlock;
class UCheckBox;
UCLASS()
class OPTIMIZEMAN_API UTodoList_OM : public UPlayModeBaseWidget_OM
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;


protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Task1;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* Task1CheckBox;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Task2;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* Task2CheckBox;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Task3;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* Task3CheckBox;


private:
	bool bHasBeenOpened;
	
	
};
