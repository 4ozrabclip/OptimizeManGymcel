// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "MainMenuWidget_OM.generated.h"

class UGameAudio_OM;
class USlider;
class UBorder;
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
public:
	virtual void NativeConstruct() override;

	void OpenWindow(UVerticalBox* InWindow = nullptr, UBorder* InBorder = nullptr) const;
	void InitButtons();

	virtual void DarkModeToggle(const bool bIsDarkMode) override;

	UFUNCTION()
	void StartNewGame();
	UFUNCTION()
	void QuitGameNow();
	
	UFUNCTION()
	void PlayButtonClicked() { OpenWindow(PlayGameBox); };

	UFUNCTION()
	void SettingsButtonClicked() { OpenWindow(SettingsBox); };

	UFUNCTION()
	void AudioQualitySettingsButtonClicked() { OpenWindow(nullptr, AudioQualitySettings_Layer); }

	UFUNCTION()
	void BackButtonClicked() { OpenWindow(MainMenuBox); };

	UFUNCTION()
	void UpdateGameSettings();
	
	UFUNCTION()
	void ToggleDarkModeFunction();

	UPROPERTY()
	UGameAudio_OM* NotificationAudio;
	UPROPERTY()
	UGameAudio_OM* MenuMusic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	USoundBase* MenuSong;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NotificationAudio")
	USoundBase* SplatSound;
		
	void PlaySplat();

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
	UButton* AudioQualitySettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsBackButton;

	UPROPERTY(meta = (BindWidget))
	UBorder* AudioQualitySettings_Layer;
	UPROPERTY(meta = (BindWidget))
	USlider* MasterVolume_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* MusicVolume_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* VoiceVolume_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* NotificationVolume_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* SfxVolume_Slider;
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromSettings_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* AcceptSettings_Button;

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
	UMaterial* AudioQualityBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* AudioQualityBlackHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* AudioQualityWhite;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* AudioQualityWhiteHover;

	
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* BackButtonBlack;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* BackButtonBlackHover;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* BackButtonWhite;
	UPROPERTY(EditAnywhere, Category = "Images")
	UMaterial* BackButtonWhiteHover;
	

};
