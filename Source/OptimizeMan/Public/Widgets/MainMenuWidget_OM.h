// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/ParentWidget_OM.h"
#include "MainMenuWidget_OM.generated.h"

class UVerticalBox;
class USlateBrushAsset;
class UButton;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UMainMenuWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	void OpenWindow(UVerticalBox* InWindow) const;
	void InitButtons();

	UFUNCTION()
	void PlayGameNow();
	UFUNCTION()
	void QuitGameNow();
	void UpdateImagesForDarkMode();
	
	UFUNCTION()
	void PlayButtonClicked() { OpenWindow(PlayGameBox); };

	UFUNCTION()
	void SettingsButtonClicked() { OpenWindow(SettingsBox); };

	UFUNCTION()
	void BackButtonClicked() { OpenWindow(MainMenuBox); };
	
	UFUNCTION()
	void ToggleDarkModeFunction();

protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MainMenuBox;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayGameBox;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* SettingsBox;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* NewGameButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LoadGameButton;
	UPROPERTY(meta = (BindWidget))
	UButton* PlayGameBackButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ToggleDarkMode;
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsBackButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* Title;

private:
	UPROPERTY(EditAnywhere, Category = "Images")
	UTexture* LogoBlack;

	UPROPERTY(EditAnywhere, Category = "Images")
	UTexture* LogoWhite;

	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* PlayButtonBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* PlayButtonBlackHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* PlayButtonWhite;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* PlayButtonWhiteHover;
	
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* SettingsButtonBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* SettingsButtonBlackHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* SettingsButtonWhite;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* SettingsButtonWhiteHover;

	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* QuitButtonBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* QuitButtonBlackHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* QuitButtonWhite;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* QuitButtonWhiteHover;

	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* NewGameButtonBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* NewGameButtonBlackHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* NewGameButtonWhite;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* NewGameButtonWhiteHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* LoadGameButtonBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* LoadGameButtonBlackHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* LoadGameButtonWhite;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* LoadGameButtonWhiteHover;

	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* ToggleDarkModeBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* ToggleDarkModeBlackHover;
	UPROPERTY(Editanywhere, Category = "Images")
	UMaterial* ToggleDarkModeWhite;
	UPROPERTY(Editanywhere, Category = "Images")
	UMaterial* ToggleDarkModeWhiteHover;
	
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* BackButtonBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* BackButtonBlackHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* BackButtonWhite;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* BackButtonWhiteHover;

};
