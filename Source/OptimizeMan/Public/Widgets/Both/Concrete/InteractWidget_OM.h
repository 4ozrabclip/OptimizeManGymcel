// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "InteractWidget_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UInteractWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void SetText(const FString& InText);

	virtual void DarkModeToggle(const bool bIsDarkMode) override;

	FString GetText();

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock;
	
private:
	FString WidgetTextString;
	
};
