// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget_OM.h"

#include "Audio/GameAudio_OM.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Structs/AudioTypes.h"

void UMainMenuWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	OpenWindow(MainMenuBox);
	
	InitButtons();
	
	UpdateImagesForDarkMode();

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
	NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::PlayGameNow);
	LoadGameButton->OnClicked.RemoveAll(this);
	LoadGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget_OM::PlayGameNow); // load game not working yet
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


void UMainMenuWidget_OM::UpdateImagesForDarkMode()
{
	if (GameInstance->GetDarkMode())
	{
		FButtonStyle AudioQualityDarkModeStyle;
		AudioQualityDarkModeStyle.Normal.SetResourceObject(AudioQualityWhite);
		AudioQualityDarkModeStyle.Hovered.SetResourceObject(AudioQualityWhiteHover);
		AudioQualityDarkModeStyle.Pressed.SetResourceObject(AudioQualityWhite);
		
		FButtonStyle PlayDarkModeStyle;
		PlayDarkModeStyle.Normal.SetResourceObject(PlayButtonWhite);
		PlayDarkModeStyle.Hovered.SetResourceObject(PlayButtonWhiteHover);
		PlayDarkModeStyle.Pressed.SetResourceObject(PlayButtonWhite);

		FButtonStyle SettingsDarkModeStyle;
		SettingsDarkModeStyle.Normal.SetResourceObject(SettingsButtonWhite);
		SettingsDarkModeStyle.Hovered.SetResourceObject(SettingsButtonWhiteHover);
		SettingsDarkModeStyle.Pressed.SetResourceObject(SettingsButtonWhite);
		
		FButtonStyle QuitDarkModeStyle;
		QuitDarkModeStyle.Normal.SetResourceObject(QuitButtonWhite);
		QuitDarkModeStyle.Hovered.SetResourceObject(QuitButtonWhiteHover);
		QuitDarkModeStyle.Pressed.SetResourceObject(QuitButtonWhite);

		FButtonStyle BackButtonDarkModeStyle;
		BackButtonDarkModeStyle.Normal.SetResourceObject(BackButtonWhite);
		BackButtonDarkModeStyle.Hovered.SetResourceObject(BackButtonWhiteHover);
		BackButtonDarkModeStyle.Pressed.SetResourceObject(BackButtonWhite);

		FButtonStyle NewGameDarkModeStyle;
		NewGameDarkModeStyle.Normal.SetResourceObject(NewGameButtonWhite);
		NewGameDarkModeStyle.Hovered.SetResourceObject(NewGameButtonWhiteHover);
		NewGameDarkModeStyle.Pressed.SetResourceObject(NewGameButtonWhite);

		FButtonStyle LoadGameDarkModeStyle;
		LoadGameDarkModeStyle.Normal.SetResourceObject(LoadGameButtonWhite);
		LoadGameDarkModeStyle.Hovered.SetResourceObject(LoadGameButtonWhiteHover);
		LoadGameDarkModeStyle.Pressed.SetResourceObject(LoadGameButtonWhite);

		FButtonStyle ToggleDarkModeStyle;
		ToggleDarkModeStyle.Normal.SetResourceObject(ToggleDarkModeWhite);
		ToggleDarkModeStyle.Hovered.SetResourceObject(ToggleDarkModeWhiteHover);
		ToggleDarkModeStyle.Pressed.SetResourceObject(ToggleDarkModeWhite);

		
		
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
	}
	else
	{
		FButtonStyle AudioQualityLightModeStyle;
		AudioQualityLightModeStyle.Normal.SetResourceObject(AudioQualityBlack);
		AudioQualityLightModeStyle.Hovered.SetResourceObject(AudioQualityBlackHover);
		AudioQualityLightModeStyle.Pressed.SetResourceObject(AudioQualityBlack);
		
		FButtonStyle PlayLightModeStyle;
		PlayLightModeStyle.Normal.SetResourceObject(PlayButtonBlack);
		PlayLightModeStyle.Hovered.SetResourceObject(PlayButtonBlackHover);
		PlayLightModeStyle.Pressed.SetResourceObject(PlayButtonBlack);
		FButtonStyle SettingsLightModeStyle;
		SettingsLightModeStyle.Normal.SetResourceObject(SettingsButtonBlack);
		SettingsLightModeStyle.Hovered.SetResourceObject(SettingsButtonBlackHover);
		SettingsLightModeStyle.Pressed.SetResourceObject(SettingsButtonBlack);
		FButtonStyle QuitLightModeStyle;
		QuitLightModeStyle.Normal.SetResourceObject(QuitButtonBlack);
		QuitLightModeStyle.Hovered.SetResourceObject(QuitButtonBlackHover);
		QuitLightModeStyle.Pressed.SetResourceObject(QuitButtonBlack);
		FButtonStyle BackButtonLightModeStyle;
		BackButtonLightModeStyle.Normal.SetResourceObject(BackButtonBlack);
		BackButtonLightModeStyle.Hovered.SetResourceObject(BackButtonBlackHover);
		BackButtonLightModeStyle.Pressed.SetResourceObject(BackButtonBlack);
		FButtonStyle NewGameLightModeStyle;
		NewGameLightModeStyle.Normal.SetResourceObject(NewGameButtonBlack);
		NewGameLightModeStyle.Hovered.SetResourceObject(NewGameButtonBlackHover);
		NewGameLightModeStyle.Pressed.SetResourceObject(NewGameButtonBlack);
		FButtonStyle LoadGameLightModeStyle;
		LoadGameLightModeStyle.Normal.SetResourceObject(LoadGameButtonBlack);
		LoadGameLightModeStyle.Hovered.SetResourceObject(LoadGameButtonBlackHover);
		LoadGameLightModeStyle.Pressed.SetResourceObject(LoadGameButtonBlack);
		FButtonStyle ToggleDarkModeStyle;
		ToggleDarkModeStyle.Normal.SetResourceObject(ToggleDarkModeBlack);
		ToggleDarkModeStyle.Hovered.SetResourceObject(ToggleDarkModeBlackHover);
		ToggleDarkModeStyle.Pressed.SetResourceObject(ToggleDarkModeBlack);
		
		Title->SetBrushResourceObject(LogoBlack);
		PlayButton->SetStyle(PlayLightModeStyle);
		SettingsButton->SetStyle(SettingsLightModeStyle);
		QuitButton->SetStyle(QuitLightModeStyle);
		PlayGameBackButton->SetStyle(BackButtonLightModeStyle);
		SettingsBackButton->SetStyle(BackButtonLightModeStyle);
		NewGameButton->SetStyle(NewGameLightModeStyle);
		LoadGameButton->SetStyle(LoadGameLightModeStyle);
		ToggleDarkMode->SetStyle(ToggleDarkModeStyle);
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

	UpdateImagesForDarkMode();
}

void UMainMenuWidget_OM::PlayGameNow() 
{
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
