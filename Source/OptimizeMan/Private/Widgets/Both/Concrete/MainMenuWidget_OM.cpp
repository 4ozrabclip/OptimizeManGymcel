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
	
	InitButtons();
	
	OpenWindow(FName("MainWindow"));
	


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


void UMainMenuWidget_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UMainMenuWidget_OM::InitWindowsArray()
{
	Super::InitWindowsArray();

	

	FUserInterfaceWindow MainWindow;
	MainWindow.WindowName = FName("MainWindow");
	MainWindow.Window = MainMenuBox;
	MainWindow.FocusableContent.Add(MakeButton(PlayButton, PlayButton->GetStyle()));
	MainWindow.FocusableContent.Add(MakeButton(SettingsButton, SettingsButton->GetStyle()));
	MainWindow.FocusableContent.Add(MakeButton(QuitButton, QuitButton->GetStyle()));
	Windows.Add(MainWindow);
	
	FUserInterfaceWindow SettingsWindow;
	SettingsWindow.WindowName = FName("SettingsWindow");
	SettingsWindow.Window = SettingsBox;
	SettingsWindow.FocusableContent.Add(MakeButton(ToggleDarkMode, ToggleDarkMode->GetStyle()));
	SettingsWindow.FocusableContent.Add(MakeButton(AudioQualitySettingsButton, AudioQualitySettingsButton->GetStyle()));
	SettingsWindow.FocusableContent.Add(MakeButton(SettingsBackButton, SettingsBackButton->GetStyle()));
	Windows.Add(SettingsWindow);

	
	FUserInterfaceWindow PlayGameWindow;
	PlayGameWindow.WindowName = FName("PlayGameWindow");
	PlayGameWindow.Window = PlayGameBox;
	PlayGameWindow.FocusableContent.Add(MakeButton(NewGameButton, NewGameButton->GetStyle()));
	PlayGameWindow.FocusableContent.Add(MakeButton(LoadGameButton, LoadGameButton->GetStyle()));
	PlayGameWindow.FocusableContent.Add(MakeButton(PlayGameBackButton, PlayGameBackButton->GetStyle()));
	Windows.Add(PlayGameWindow);

	FUserInterfaceWindow AudioQualitySettingsWindow;
	AudioQualitySettingsWindow.WindowName = FName("AudioQualitySettingsWindow");
	AudioQualitySettingsWindow.Window = AudioQualitySettings_Layer;
	/*AudioQualitySettingsWindow.FocusableContent.Add(MasterVolume_Slider);
	AudioQualitySettingsWindow.FocusableContent.Add(MusicVolume_Slider);
	AudioQualitySettingsWindow.FocusableContent.Add(VoiceVolume_Slider);
	AudioQualitySettingsWindow.FocusableContent.Add(NotificationVolume_Slider);
	AudioQualitySettingsWindow.FocusableContent.Add(SfxVolume_Slider);
	AudioQualitySettingsWindow.FocusableContent.Add(BackFromSettings_Button);
	AudioQualitySettingsWindow.FocusableContent.Add(AcceptSettings_Button);*/
	Windows.Add(AudioQualitySettingsWindow);

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

	CurrentButtonStyle = bIsDarkMode ? DarkModeButtonStyle : LightModeButtonStyle;

	PlayButton->SetStyle(CurrentButtonStyle);
	SettingsButton->SetStyle(CurrentButtonStyle);
	QuitButton->SetStyle(CurrentButtonStyle);
	PlayGameBackButton->SetStyle(CurrentButtonStyle);
	SettingsBackButton->SetStyle(CurrentButtonStyle);
	NewGameButton->SetStyle(CurrentButtonStyle);
	LoadGameButton->SetStyle(CurrentButtonStyle);
	ToggleDarkMode->SetStyle(CurrentButtonStyle);
	AudioQualitySettingsButton->SetStyle(CurrentButtonStyle);

	Play_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	Settings_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	Quit_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	NewGame_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	LoadGame_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	PlayGameBack_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	ToggleDarkMode_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	AudioQualitySettings_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	SettingsBack_Text->SetColorAndOpacity(bIsDarkMode ? White : Black);
	

	Title->SetBrushResourceObject(bIsDarkMode ? LogoWhite : LogoBlack);

		

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
