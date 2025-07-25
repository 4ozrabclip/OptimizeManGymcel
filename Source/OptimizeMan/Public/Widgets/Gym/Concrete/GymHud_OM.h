// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/Concrete/AbilitySystemComponent_OM.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "GymHud_OM.generated.h"

class UTextBlock;
class UGymSpecificStats_OM;
class APlayerCharacter_OM;
class APlayerController_OM;
class UProgressBar;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UGymHud_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void DarkModeToggle(const bool bIsDarkMode) override;
	void UpdateProgressBars() const;

private:
	//Priv Functions
	void PlayGymHudTutorial();
	
	
	//Properties
	UPROPERTY()
	APlayerController_OM* PlayerController;
	UPROPERTY()
	APlayerCharacter_OM* Player;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent_OM> AbSysComp;
	UPROPERTY()
	const UGymSpecificStats_OM* GymStats;
	
	bool bRetrievedGymStats = false;



	
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Energy_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Focus_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Bladder_PBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Energy_TextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Focus_TextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Bladder_TextBlock;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* GymHudTutorial;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Images")
	UMaterial* EnergyBorder_Black;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Images")
	UMaterial* EnergyBorder_White;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Images")
	UMaterial* FocusBorder_Black;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Images")
	UMaterial* FocusBorder_White;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Images")
	UMaterial* BladderBorder_Black;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Images")
	UMaterial* BladderBorder_White;
};
