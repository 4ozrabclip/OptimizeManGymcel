// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentWidget_OM.h"
#include "InteractWidget_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMANCORE_API UInteractWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void SetText(const FString& InText);
	void CheckAndSetTextColour();

	FString GetText();

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock;
	
private:
	FString WidgetTextString;
	
};
