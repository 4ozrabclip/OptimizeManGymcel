// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget_OM.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	OpenWindow(MainMenuBox);
	
	InitButtons();
	
	UpdateImagesForDarkMode();
}

void UMainMenuWidget_OM::OpenWindow(UVerticalBox* InWindow) const
{
	if (!InWindow || !MainMenuBox || !PlayGameBox || !SettingsBox)
	{
		UE_LOG(LogTemp, Error, TEXT("No window in MainMenuWidget OpenWindow"));
		return;
	}
	
	MainMenuBox->SetVisibility(ESlateVisibility::Hidden);
	PlayGameBox->SetVisibility(ESlateVisibility::Hidden);
	SettingsBox->SetVisibility(ESlateVisibility::Hidden);

	
	InWindow->SetVisibility(ESlateVisibility::Visible);
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
	

}


void UMainMenuWidget_OM::UpdateImagesForDarkMode()
{
	if (GameInstance->GetDarkMode())
	{
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
	}
	else
	{
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


