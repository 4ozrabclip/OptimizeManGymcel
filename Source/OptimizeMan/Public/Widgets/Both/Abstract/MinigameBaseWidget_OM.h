// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentWidget_OM.h"
#include "Blueprint/UserWidget.h"
#include "MinigameBaseWidget_OM.generated.h"

class APlayerController_OM;
class APlayerCharacter_OM;
/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API UMinigameBaseWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnExitButtonClicked();

	UFUNCTION()
	void SetHasHint(const bool InHasHint) { bHasHint = InHasHint; }

	UFUNCTION()
	bool GetHasHint() const { return bHasHint; }

	UFUNCTION()
	virtual void SetWidgetUIDarkLightMode();
	
protected:
	UPROPERTY()
	bool bIsDarkMode;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY()
	APlayerCharacter_OM* Player;

	UPROPERTY()
	APlayerController_OM* PlayerController;




	UPROPERTY()
	FButtonStyle DarkExitStyle;
	UPROPERTY()
	FButtonStyle LightExitStyle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dark/Light Mode")
	UMaterial* WhiteExitButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dark/Light Mode")
	UMaterial* WhiteHoveredExitButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dark/Light Mode")
	UMaterial* BlackExitButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dark/Light Mode")
	UMaterial* BlackHoveredExitButton;
private:
	bool bHasHint = false;;
	
};
