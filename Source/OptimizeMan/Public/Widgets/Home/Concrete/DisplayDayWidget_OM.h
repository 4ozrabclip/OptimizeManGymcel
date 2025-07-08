// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "DisplayDayWidget_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UDisplayDayWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void DarkModeToggle(const bool bIsDarkMode) override;

	UFUNCTION(BlueprintSetter)
	void SetText(const FString& InText);

	UFUNCTION(BlueprintGetter)
	FString GetText();

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayDayText;
	
private:
	FString WidgetTextString;
};