// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utils/GameInstance_OM.h"
#include "ParentWidget_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UParentWidget_OM : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	
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
