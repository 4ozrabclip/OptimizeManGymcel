// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/InteractiveWidgetBase_OM.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "MainMenuWidget_OM.generated.h"

class UButton_OM;
class UTextBlock;
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
class OPTIMIZEMAN_API UMainMenuWidget_OM : public UInteractiveWidgetBase_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void InitWindowsArray() override;


	void InitButtons();

	virtual void DarkModeToggle(const bool bIsDarkMode) override;

	UFUNCTION()
	void StartNewGame();
	UFUNCTION()
	void QuitGameNow();
	
	UFUNCTION()
	void PlayButtonClicked() { OpenWindow(FName("PlayGameWindow")); };

	UFUNCTION()
	void SettingsButtonClicked() { OpenWindow(FName("SettingsWindow")); };

	UFUNCTION()
	void AudioQualitySettingsButtonClicked() { OpenWindow(FName("AudioQualitySettingsWindow")); }

	UFUNCTION()
	void BackButtonClicked() { OpenWindow(FName("MainWindow")); };

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
	UTextBlock* Play_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Settings_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Quit_Text;
	
	UPROPERTY(meta = (BindWidget))
	UButton* NewGameButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NewGame_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* LoadGameButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LoadGame_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* PlayGameBackButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayGameBack_Text;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ToggleDarkMode;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ToggleDarkMode_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* AudioQualitySettingsButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AudioQualitySettings_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsBackButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingsBack_Text;

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
	UPROPERTY(EditAnywhere, Category = "Styles")
	FButtonStyle DarkModeButtonStyle;
	UPROPERTY(EditAnywhere, Category = "Styles")
	FButtonStyle LightModeButtonStyle;


	

	
	UPROPERTY(EditAnywhere, Category = "Images")
	UTexture* LogoBlack;

	UPROPERTY(EditAnywhere, Category = "Images")
	UTexture* LogoWhite;


};
