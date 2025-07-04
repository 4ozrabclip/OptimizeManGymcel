// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/ParentWidget_OM.h"
#include "HintsWidget_OM.generated.h"

/**
 * 
 */

UCLASS()
class OPTIMIZEMAN_API UHintsWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void ShowHint(const FText& HintTextString, float DisplayTime = 0.f);
	void HideHint();


protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HintText;

	FTimerHandle HintTimerHandle;
	
};

