// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveWidgetBase_OM.h"
#include "ParentWidget_OM.h"
#include "Blueprint/UserWidget.h"
#include "MinigameBaseWidget_OM.generated.h"

class APlayerController_OM;
class APlayerCharacter_OM;
/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API UMinigameBaseWidget_OM : public UInteractiveWidgetBase_OM
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
	
	virtual void DarkModeToggle(const bool bIsDarkMode) override;
	
protected:

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
