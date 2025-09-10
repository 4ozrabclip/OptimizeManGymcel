// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "YouDiedWidget_OM.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UYouDiedWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void TryAgain();

	UFUNCTION()
	void ExitToMainMenu();

protected:

	/** **/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DaysLastedTextBlock;
	UPROPERTY(meta = (BindWidget))
	UButton* TryAgainButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;


	/** Animation **/
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* YouDiedOpenAnim;
	
};
