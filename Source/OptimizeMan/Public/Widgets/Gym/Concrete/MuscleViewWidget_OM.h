// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "MuscleViewWidget_OM.generated.h"

class UBorder;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UMuscleViewWidget_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void DarkModeToggle(const bool bIsDarkMode) override;
	void UpdateStats() const;


public: //UFUNCTIONS
	UFUNCTION()
	void PumpUp();

protected: //UObjects
	UPROPERTY(meta = (BindWidget))
	UButton* PumpUpButton;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* LeftArm_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* RightArm_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* LeftThigh_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* RightThigh_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* LeftCalve_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* RightCalve_PBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LeftArmText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RightArmText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LeftShoulderText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RightShoulderText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LeftThighText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RightThighText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LeftCalveText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RightCalveText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LeftSideText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RightSideText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FlexButtonText;

	UPROPERTY(meta = (BindWidget))
	UBorder* LeftArmBorder;
	UPROPERTY(meta = (BindWidget))
	UBorder* RightArmBorder;
	UPROPERTY(meta = (BindWidget))
	UBorder* LeftShoulderBorder;
	UPROPERTY(meta = (BindWidget))
	UBorder* RightShoulderBorder;
	UPROPERTY(meta = (BindWidget))
	UBorder* LeftThighBorder;
	UPROPERTY(meta = (BindWidget))
	UBorder* RightThighBorder;
	UPROPERTY(meta = (BindWidget))
	UBorder* LeftCalveBorder;
	UPROPERTY(meta = (BindWidget))
	UBorder* RightCalveBorder;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dark/Light Mode")
	UMaterial* BlackBorder;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dark/Light Mode")
	UMaterial* WhiteBorder;

};
