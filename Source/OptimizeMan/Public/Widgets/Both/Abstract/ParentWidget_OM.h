// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "ParentWidget_OM.generated.h"

class UButton;
/**
 * 
 */

UCLASS(Abstract)
class OPTIMIZEMAN_API UParentWidget_OM : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


	UFUNCTION()
	virtual void DarkModeToggle(const bool bIsDarkMode) {}
	
	UFUNCTION()
	virtual void FadeIn();

protected:
	
	FTimerHandle FadeInTimerHandle;
	bool bIsFadingIn = false;

	
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	
	FGameSettings GameSettings;

	UPROPERTY()
	FSlateColor Black;
	UPROPERTY()
	FSlateColor White;
	
};
