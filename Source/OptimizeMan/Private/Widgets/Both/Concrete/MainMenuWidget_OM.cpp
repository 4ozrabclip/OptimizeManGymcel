// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/MainMenuWidget_OM.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Structs/AudioTypes.h"

void UMainMenuWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	OpenWindow(MainMenuBox);
	
	InitButtons();

	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}

	if (GameInstance)
	{
		MenuMusic = NewObject<UGameAudio_OM>(GameInstance);
		MenuMusic->RegisterComponentWithWorld(GetWorld());
		MenuMusic->SetSound(MenuSong);
		MenuMusic->SetAudioType(EAudioTypes::MusicAudio);
		MenuMusic->bIsUISound = true;
		MenuMusic->Play();

		NotificationAudio = NewObject<UGameAudio_OM>(GameInstance);
		NotificationAudio->RegisterComponentWithWorld(GetWorld());
		NotificationAudio->SetSound(SplatSound);
		NotificationAudio->SetAudioType(EAudioTypes::NotificationAudio);
		NotificationAudio->bIsUISound = true;
	}

}

void UMainMenuWidget_OM::OpenWindow(UVerticalBox* InWindow, UBorder* InBorder) const
{
	if (!InWindow && !InBorder) return;
	if (!MainMenuBox || !PlayGameBox || !SettingsBox)
	{
		UE_LOG(LogTemp, Error, TEXT("No window in MainMenuWidget OpenWindow"));
		return;
	}
	
	MainMenuBox->SetVisibility(ESlateVisibility::Hidden);
	PlayGameBox->SetVisibility(ESlateVisibility::Hidden);
	SettingsBox->SetVisibility(ESlateVisibility::Hidden);
	AudioQualitySettings_Layer->SetVisibility(ESlateVisibility::Hidden);

	if (InWindow)
		InWindow->SetVisibility(ESlateVisibility::Visible);
	if (InBorder)
		InBorder->SetVisibility(ESlateVisibility::Visible);
}


void UMainMenuWidget_OM::InitButtons()
{
	if (!PlayButton || !QuitButton || !ToggleDarkMode || !SettingsButton ||
		!NewGameButton || !LoadGameButton)
	{
		UE_LOG(LogTemp, Error, TEXT("No buttons in MainMenuWidget"));
		return;
	}

	PlayButton->OnClicked.RemoveAll(this);
	PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::PlayButtonClicked);
	SettingsButton->OnClicked.RemoveAll(this);
	SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::SettingsButtonClicked);
	QuitButton->OnClicked.RemoveAll(this);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::QuitGameNow);

	NewGameButton->OnClicked.RemoveAll(this);
	NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::StartNewGame);
	LoadGameButton->OnClicked.RemoveAll(this);
	LoadGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::StartNewGame); // load game not working yet
	PlayGameBackButton->OnClicked.RemoveAll(this);
	PlayGameBackButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::BackButtonClicked);
	
	ToggleDarkMode->OnClicked.RemoveAll(this);
	ToggleDarkMode->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::ToggleDarkModeFunction);
	SettingsBackButton->OnClicked.RemoveAll(this);
	SettingsBackButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::BackButtonClicked);

	AudioQualitySettingsButton->OnClicked.RemoveAll(this);
	AudioQualitySettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::AudioQualitySettingsButtonClicked);
	BackFromSettings_Button->OnClicked.RemoveAll(this);
	BackFromSettings_Button->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::SettingsButtonClicked);
	AcceptSettings_Button->OnClicked.RemoveAll(this);
	AcceptSettings_Button->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::UpdateGameSettings);
	
	

}

void UMainMenuWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);

	if (!BorderWhite || !BorderBlack || !BorderWhite2 || !BorderBlack2 ||
		!BorderWhite_Hover || !BorderBlack_Hover || !BorderWhite_Hover2 || !BorderBlack_Hover2) return;

	if (bIsDarkMode)
	{
		FButtonStyle AudioQualityDarkModeStyle;
		AudioQualityDarkModeStyle.Normal.SetResourceObject(BorderWhite);
		AudioQualityDarkModeStyle.Hovered.SetResourceObject(BorderWhite_Hover);
		AudioQualityDarkModeStyle.Pressed.SetResourceObject(BorderWhite);
		
		FButtonStyle PlayDarkModeStyle;
		PlayDarkModeStyle.Normal.SetResourceObject(BorderWhite);
		PlayDarkModeStyle.Hovered.SetResourceObject(BorderWhite_Hover2);
		PlayDarkModeStyle.Pressed.SetResourceObject(BorderWhite);

		FButtonStyle SettingsDarkModeStyle;
		SettingsDarkModeStyle.Normal.SetResourceObject(BorderWhite2);
		SettingsDarkModeStyle.Hovered.SetResourceObject(BorderWhite_Hover);
		SettingsDarkModeStyle.Pressed.SetResourceObject(BorderWhite);
		
		FButtonStyle QuitDarkModeStyle;
		QuitDarkModeStyle.Normal.SetResourceObject(BorderWhite);
		QuitDarkModeStyle.Hovered.SetResourceObject(BorderWhite_Hover2);
		QuitDarkModeStyle.Pressed.SetResourceObject(BorderWhite);

		FButtonStyle BackButtonDarkModeStyle;
		BackButtonDarkModeStyle.Normal.SetResourceObject(BorderWhite);
		BackButtonDarkModeStyle.Hovered.SetResourceObject(BorderWhite_Hover);
		BackButtonDarkModeStyle.Pressed.SetResourceObject(BorderWhite);

		FButtonStyle NewGameDarkModeStyle;
		NewGameDarkModeStyle.Normal.SetResourceObject(BorderWhite2);
		NewGameDarkModeStyle.Hovered.SetResourceObject(BorderWhite_Hover2);
		NewGameDarkModeStyle.Pressed.SetResourceObject(BorderWhite);

		FButtonStyle LoadGameDarkModeStyle;
		LoadGameDarkModeStyle.Normal.SetResourceObject(BorderWhite2);
		LoadGameDarkModeStyle.Hovered.SetResourceObject(BorderWhite_Hover);
		LoadGameDarkModeStyle.Pressed.SetResourceObject(BorderWhite);

		FButtonStyle ToggleDarkModeStyle;
		ToggleDarkModeStyle.Normal.SetResourceObject(BorderWhite);
		ToggleDarkModeStyle.Hovered.SetResourceObject(BorderWhite_Hover2);
		ToggleDarkModeStyle.Pressed.SetResourceObject(BorderWhite2);

		
		
		Title->SetBrushResourceObject(LogoWhite);
		PlayButton->SetStyle(PlayDarkModeStyle);
		SettingsButton->SetStyle(SettingsDarkModeStyle);
		QuitButton->SetStyle(QuitDarkModeStyle);
		PlayGameBackButton->SetStyle(BackButtonDarkModeStyle);
		SettingsBackButton->SetStyle(BackButtonDarkModeStyle);
		NewGameButton->SetStyle(NewGameDarkModeStyle);
		LoadGameButton->SetStyle(LoadGameDarkModeStyle);
		ToggleDarkMode->SetStyle(ToggleDarkModeStyle);
		AudioQualitySettingsButton->SetStyle(AudioQualityDarkModeStyle);

		// Text
		Play_Text->SetColorAndOpacity(White);
		Settings_Text->SetColorAndOpacity(White);
		Quit_Text->SetColorAndOpacity(White);
		NewGame_Text->SetColorAndOpacity(White);
		LoadGame_Text->SetColorAndOpacity(White);
		PlayGameBack_Text->SetColorAndOpacity(White);
		ToggleDarkMode_Text->SetColorAndOpacity(White);
		AudioQualitySettings_Text->SetColorAndOpacity(White);
		SettingsBack_Text->SetColorAndOpacity(White);
		
	}
	else
	{
		FButtonStyle AudioQualityLightModeStyle;
		AudioQualityLightModeStyle.Normal.SetResourceObject(BorderBlack);
		AudioQualityLightModeStyle.Hovered.SetResourceObject(BorderBlack_Hover);
		AudioQualityLightModeStyle.Pressed.SetResourceObject(BorderBlack2);
		
		FButtonStyle PlayLightModeStyle;
		PlayLightModeStyle.Normal.SetResourceObject(BorderBlack2);
		PlayLightModeStyle.Hovered.SetResourceObject(BorderBlack_Hover2);
		PlayLightModeStyle.Pressed.SetResourceObject(BorderBlack);
		
		FButtonStyle SettingsLightModeStyle;
		SettingsLightModeStyle.Normal.SetResourceObject(BorderBlack);
		SettingsLightModeStyle.Hovered.SetResourceObject(BorderBlack_Hover);
		SettingsLightModeStyle.Pressed.SetResourceObject(BorderBlack);
		FButtonStyle QuitLightModeStyle;
		QuitLightModeStyle.Normal.SetResourceObject(BorderBlack2);
		QuitLightModeStyle.Hovered.SetResourceObject(BorderBlack_Hover2);
		QuitLightModeStyle.Pressed.SetResourceObject(BorderBlack);
		FButtonStyle BackButtonLightModeStyle;
		BackButtonLightModeStyle.Normal.SetResourceObject(BorderBlack);
		BackButtonLightModeStyle.Hovered.SetResourceObject(BorderBlack_Hover);
		BackButtonLightModeStyle.Pressed.SetResourceObject(BorderBlack);
		FButtonStyle NewGameLightModeStyle;
		NewGameLightModeStyle.Normal.SetResourceObject(BorderBlack2);
		NewGameLightModeStyle.Hovered.SetResourceObject(BorderBlack_Hover2);
		NewGameLightModeStyle.Pressed.SetResourceObject(BorderBlack);
		FButtonStyle LoadGameLightModeStyle;
		LoadGameLightModeStyle.Normal.SetResourceObject(BorderBlack);
		LoadGameLightModeStyle.Hovered.SetResourceObject(BorderBlack_Hover);
		LoadGameLightModeStyle.Pressed.SetResourceObject(BorderBlack2);
		FButtonStyle ToggleDarkModeStyle;
		ToggleDarkModeStyle.Normal.SetResourceObject(BorderBlack2);
		ToggleDarkModeStyle.Hovered.SetResourceObject(BorderBlack_Hover2);
		ToggleDarkModeStyle.Pressed.SetResourceObject(BorderBlack);
		
		Title->SetBrushResourceObject(LogoBlack);
		PlayButton->SetStyle(PlayLightModeStyle);
		SettingsButton->SetStyle(SettingsLightModeStyle);
		QuitButton->SetStyle(QuitLightModeStyle);
		PlayGameBackButton->SetStyle(BackButtonLightModeStyle);
		SettingsBackButton->SetStyle(BackButtonLightModeStyle);
		NewGameButton->SetStyle(NewGameLightModeStyle);
		LoadGameButton->SetStyle(LoadGameLightModeStyle);
		ToggleDarkMode->SetStyle(ToggleDarkModeStyle);
		AudioQualitySettingsButton->SetStyle(AudioQualityLightModeStyle);

		// Text
		Play_Text->SetColorAndOpacity(Black);
		Settings_Text->SetColorAndOpacity(Black);
		Quit_Text->SetColorAndOpacity(Black);
		NewGame_Text->SetColorAndOpacity(Black);
		LoadGame_Text->SetColorAndOpacity(Black);
		PlayGameBack_Text->SetColorAndOpacity(Black);
		ToggleDarkMode_Text->SetColorAndOpacity(Black);
		AudioQualitySettings_Text->SetColorAndOpacity(Black);
		SettingsBack_Text->SetColorAndOpacity(Black);
	}
}

void UMainMenuWidget_OM::ToggleDarkModeFunction()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No game instance in dark mode toggle main menu"));
		return;
	}
	GameInstance->DarkModeToggle();
}

void UMainMenuWidget_OM::StartNewGame() 
{
	GameInstance->ResetGame();

	
	const FString HomeLevelString = "/Game/Levels/Home";
	const FName LevelToChangeTo = FName(*HomeLevelString);
	UGameplayStatics::OpenLevel(this, LevelToChangeTo);
	
}



void UMainMenuWidget_OM::QuitGameNow()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
void UMainMenuWidget_OM::PlaySplat()
{
	if (SplatSound)
	{
		NotificationAudio->SetSound(SplatSound);
		NotificationAudio->Play();
	}
}

void UMainMenuWidget_OM::UpdateGameSettings()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("CaNT GET GAME INSTANCE in MAIN MENU"));
		return;
	}


	GameSettings = GameInstance->GetGameSettings();

	bool bChangeAudioSettings = false;

	const float MasterVolumeValue = MasterVolume_Slider->GetValue();
	const float MusicVolumeValue = MusicVolume_Slider->GetValue();
	const float VoiceVolumeValue = VoiceVolume_Slider->GetValue();
	const float NotificationVolumeValue = NotificationVolume_Slider->GetValue();
	const float SfxVolumeValue = SfxVolume_Slider->GetValue();

	float NewMasterVolume = GameSettings.MasterVolume;
	float NewMusicVolume = GameSettings.MusicVolume;
	float NewVoiceVolume = GameSettings.VoiceVolume;
	float NewNotificationVolume = GameSettings.NotificationVolume;
	float NewSfxVolume = GameSettings.SfxVolume;

	if (MasterVolumeValue != GameSettings.MasterVolume)
	{
		bChangeAudioSettings = true;
		NewMasterVolume = MasterVolumeValue;
		MenuMusic->SetVolumeMultiplier(NewMusicVolume * NewMasterVolume);
		NotificationAudio->SetVolumeMultiplier(NewNotificationVolume * NewMasterVolume);
	}
	if (MusicVolumeValue != GameSettings.MusicVolume)
	{
		bChangeAudioSettings = true;
		NewMusicVolume = MusicVolumeValue;
		MenuMusic->SetVolumeMultiplier(NewMusicVolume * NewMasterVolume);
	} 
	if (VoiceVolumeValue != GameSettings.VoiceVolume)
	{
		bChangeAudioSettings = true;
		NewVoiceVolume = VoiceVolumeValue;
	} 
	if (NotificationVolumeValue != GameSettings.NotificationVolume)
	{
		bChangeAudioSettings = true;
		NewNotificationVolume = NotificationVolumeValue;
		NotificationAudio->SetVolumeMultiplier(NewNotificationVolume * NewMasterVolume);
	}
	if (SfxVolumeValue != GameSettings.SfxVolume)
	{
		bChangeAudioSettings = true;
		NewSfxVolume = SfxVolumeValue;
	}

	if (bChangeAudioSettings)
	{
		GameInstance->SetAudioSettings(NewMasterVolume, NewVoiceVolume, NewMusicVolume, NewNotificationVolume, NewSfxVolume);
	}
	if (SplatSound && NotificationAudio)
	{
		NotificationAudio->SetSound(SplatSound);
		NotificationAudio->Play();
	}

}
