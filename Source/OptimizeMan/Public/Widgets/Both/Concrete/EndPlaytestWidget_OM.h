// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndPlaytestWidget_OM.generated.h"

class UButton;
/**
 * 
 */
UCLASS(Blueprintable)
class OPTIMIZEMAN_API UEndPlaytestWidget_OM : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnEndAnimFinished();
	UFUNCTION()
	void OnGoodbyeAnimFinished();
	UFUNCTION()
	void EndPlaytest();
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* EndAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* GoodbyeAnim;


	
};
