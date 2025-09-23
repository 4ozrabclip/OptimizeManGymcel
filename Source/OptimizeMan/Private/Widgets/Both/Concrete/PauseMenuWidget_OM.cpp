// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/PauseMenuWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerControllerBase_OM.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Components/Character/Concrete/PlayerDeformationsComponent_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"


void UPauseMenuWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (ToggleLightDarkButton)
	{
		ToggleLightDarkButton->OnClicked.RemoveAll(this);
		ToggleLightDarkButton->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OnClickToggleLightDark);
	}
	if (MoreSettingsButton)
	{
		MoreSettingsButton->OnClicked.RemoveAll(this);
		MoreSettingsButton->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OpenMoreOptions);
	}
	if (QuitToTitleScreenButton)
	{
		QuitToTitleScreenButton->OnClicked.RemoveAll(this);
		QuitToTitleScreenButton->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OnClickQuitToTitleScreen);
	}
	if (BackFromMoreOptionsButton)
	{
		BackFromMoreOptionsButton->OnClicked.RemoveAll(this);
		BackFromMoreOptionsButton->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OpenBase);
	}
	if (BackFromChangeStats_Button)
	{
		BackFromChangeStats_Button->OnClicked.RemoveAll(this);
		BackFromChangeStats_Button->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OpenMoreOptions);
	}
	if (ChangeStatsButton)
	{
		ChangeStatsButton->OnClicked.RemoveAll(this);
		ChangeStatsButton->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OpenChangeStats);
	}
	if (AcceptStats_Button)
	{
		AcceptStats_Button->OnClicked.RemoveAll(this);
		AcceptStats_Button->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::UpdatePlayerStats);
	}
	if (AcceptSettings_Button)
	{
		AcceptSettings_Button->OnClicked.RemoveAll(this);
		AcceptSettings_Button->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::UpdateGameSettings);
	}
	if (SettingsAudioButton)
	{
		SettingsAudioButton->OnClicked.RemoveAll(this);
		SettingsAudioButton->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OpenSettings);
	}
	if (BackFromSettings_Button)
	{
		BackFromSettings_Button->OnClicked.RemoveAll(this);
		BackFromSettings_Button->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OpenMoreOptions);
	}
	if (BackToBaseButton)
	{
		BackToBaseButton->OnClicked.RemoveAll(this);
		BackToBaseButton->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OpenBase);
	}
	if (OpenQuitScreenButton)
	{
		OpenQuitScreenButton->OnClicked.RemoveAll(this);
		OpenQuitScreenButton->OnClicked.AddDynamic(this, &UPauseMenuWidget_OM::OpenQuitScreen);
	}
	
	
	OpenBase();

	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
}

void UPauseMenuWidget_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ChangeStats_Grid->GetVisibility() == ESlateVisibility::Visible)
	{
		constexpr float ChadThreshold = 0.7f;
		constexpr float GrindsetThreshold = 0.35f;
		constexpr float DoomerThreshold = -0.3f;
		constexpr float GoblinThreshold = -0.6f;

		const float Ego = EgoStat_Slider->GetValue();
		const float SexAppeal = SexAppealStat_Slider->GetValue();
		const float Social = SocialStat_Slider->GetValue();

		
	
		if (Ego >= ChadThreshold && SexAppeal >= ChadThreshold)
		{
			NewEmotionalState = EPlayerEmotionalStates::Gigachad;
		}
		else if (Ego >= GrindsetThreshold && (Social >= GrindsetThreshold || SexAppeal >= GrindsetThreshold))
		{
			NewEmotionalState = EPlayerEmotionalStates::Grindset;
		}
		else if (SexAppeal <= GoblinThreshold && Social <= GoblinThreshold && Ego >= GrindsetThreshold)
		{
			NewEmotionalState = EPlayerEmotionalStates::GoblinMode;
		}
		else if (Ego <= DoomerThreshold && (Social <= DoomerThreshold || SexAppeal <= DoomerThreshold))
		{
			NewEmotionalState = EPlayerEmotionalStates::Doomer;
		}
		else
		{
			NewEmotionalState = EPlayerEmotionalStates::Cope;
		}

		if (CurrentEmotionalState != NewEmotionalState)
		{
			if (UTexture2D* Image = EmotionalState_Wojak.FindRef(NewEmotionalState))
			{
				WojakState_Image->SetBrushFromTexture(Image);
			}
		}
	}
}

void UPauseMenuWidget_OM::InitWindowsArray()
{
	Super::InitWindowsArray();

	FUserInterfaceWindow MainWindow;
	MainWindow.WindowName = FName("MainWindow");
	MainWindow.Window = Base_VBox;
	Windows.Add(MainWindow);

	FUserInterfaceWindow MoreOptionsWindow;
	MoreOptionsWindow.WindowName = FName("MoreOptionsWindow");
	MoreOptionsWindow.Window = MoreOptions_VBox;
	Windows.Add(MoreOptionsWindow);

	FUserInterfaceWindow ChangeStatsWindow;
	ChangeStatsWindow.WindowName = FName("ChangeStatsWindow");
	ChangeStatsWindow.Window = ChangeStats_Grid;
	Windows.Add(ChangeStatsWindow);

	FUserInterfaceWindow SettingsWindow;
	SettingsWindow.WindowName = FName("SettingsWindow");
	SettingsWindow.Window = Settings_Grid;
	Windows.Add(SettingsWindow);

	FUserInterfaceWindow AreYouSureWindow;
	AreYouSureWindow.WindowName = FName("AreYouSureWindow");
	AreYouSureWindow.Window = AreYouSure_Grid;
	Windows.Add(AreYouSureWindow);

	
}

void UPauseMenuWidget_OM::OnClickToggleLightDark()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast to game instance"));
		return;
	}
	
	GameInstance->DarkModeToggle();
}
void UPauseMenuWidget_OM::UpdateGameSettings()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	if (!GameInstance) return;

	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	GameSettings = GameInstance->GetGameSettings();

	bool bChangeAudioSettings = false;

	const float MasterVolumeValue = MasterVolume_Slider->GetValue();
	const float MusicVolumeValue = MusicVolume_Slider->GetValue();
	const float VoiceVolumeValue = VoiceVolume_Slider->GetValue();
	const float NotificationVolumeValue = NotificationVolume_Slider->GetValue();
	const float SfxVolumeValue = SfxVolume_Slider->GetValue();

	const float LookSensitivityValue = LookSensitivity_Slider->GetValue();

	float NewMasterVolume = GameSettings.MasterVolume;
	float NewMusicVolume = GameSettings.MusicVolume;
	float NewVoiceVolume = GameSettings.VoiceVolume;
	float NewNotificationVolume = GameSettings.NotificationVolume;
	float NewSfxVolume = GameSettings.SfxVolume;

	float NewLookSensitivity = GameSettings.LookSensitivity;

	if (LookSensitivityValue != GameSettings.LookSensitivity)
	{
		NewLookSensitivity = LookSensitivityValue;
		GameInstance->SetLookSensitivity(NewLookSensitivity);
	}

	if (MasterVolumeValue != GameSettings.MasterVolume)
	{
		bChangeAudioSettings = true;
		NewMasterVolume = MasterVolumeValue;
	}
	if (MusicVolumeValue != GameSettings.MusicVolume)
	{
		bChangeAudioSettings = true;
		NewMusicVolume = MusicVolumeValue;
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
	if (UNotificationAudio_OM* NotificationAudio = Player->GetComponentByClass<UNotificationAudio_OM>())
	{
		NotificationAudio->PlaySplatSound();
	}
}

void UPauseMenuWidget_OM::UpdatePlayerStats()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	if (!GameInstance) return;

	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't Find player pointer in pausemenuwidget"));
		return;
	}

	FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();

	
	const float JawValue = JawStat_Slider->GetValue();
	const float LeftArmValue = LeftArmStat_Slider->GetValue();
	const float RightArmValue = RightArmStat_Slider->GetValue();
	const float ThighsValue = ThighsStat_Slider->GetValue();
	const float CalvesValue = CalvesStat_Slider->GetValue();
	const float SocialValue = SocialStat_Slider->GetValue();
	const float EgoValue = EgoStat_Slider->GetValue();
	const float SexAppealValue = SexAppealStat_Slider->GetValue();

	float* JawStrength = GameInstance->GetBodyPartStrengthPtr(EBodyPart::Jaw, EBodyPartSide::Center);
	float* LeftArmStrength = GameInstance->GetBodyPartStrengthPtr(EBodyPart::Arm, EBodyPartSide::Left);
	float* RightArmStrength = GameInstance->GetBodyPartStrengthPtr(EBodyPart::Arm, EBodyPartSide::Right);
	float* LeftThighStrength = GameInstance->GetBodyPartStrengthPtr(EBodyPart::Thigh, EBodyPartSide::Left);
	float* RightThighStrength = GameInstance->GetBodyPartStrengthPtr(EBodyPart::Thigh, EBodyPartSide::Right);
	float* LeftCalveStrength = GameInstance->GetBodyPartStrengthPtr(EBodyPart::Calve, EBodyPartSide::Left);
	float* RightCalveStrength = GameInstance->GetBodyPartStrengthPtr(EBodyPart::Calve, EBodyPartSide::Right);

	GameInstance->SetStat(*JawStrength, JawValue);
	GameInstance->SetStat(*LeftArmStrength, LeftArmValue);
	GameInstance->SetStat(*RightArmStrength, RightArmValue);
	GameInstance->SetStat(*LeftThighStrength, ThighsValue);
	GameInstance->SetStat(*RightThighStrength, ThighsValue);
	GameInstance->SetStat(*LeftCalveStrength, CalvesValue);
	GameInstance->SetStat(*RightCalveStrength, CalvesValue);

	FInnerStatus NewStatus;
	NewStatus.Ego = EgoValue;
	NewStatus.Social = SocialValue;
	NewStatus.SexAppeal = SexAppealValue;
	GameInstance->SetInnerStatus(NewStatus);


	Player->InitializeAttributes();

	
	if (GameInstance->GetCurrentEmotionalState() != NewEmotionalState)
	{
		GameInstance->SetCurrentEmotionalState(NewEmotionalState);
	}
	UPlayerDeformationsComponent_OM* Deformer = Player->GetComponentByClass<UPlayerDeformationsComponent_OM>();

	Deformer->LoadDeformations(true);

	if (UNotificationAudio_OM* NotificationAudio = Player->GetComponentByClass<UNotificationAudio_OM>())
	{
		NotificationAudio->PlaySplatSound();
	}
}

void UPauseMenuWidget_OM::OpenSettings()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	if (!GameInstance) return;
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	GameSettings = GameInstance->GetGameSettings();

	MasterVolume_Slider->SetValue(GameSettings.MasterVolume);
	MusicVolume_Slider->SetValue(GameSettings.MusicVolume);
	VoiceVolume_Slider->SetValue(GameSettings.VoiceVolume);
	NotificationVolume_Slider->SetValue(GameSettings.NotificationVolume);

	LookSensitivity_Slider->SetValue(GameSettings.LookSensitivity);

	OpenWindow(FName("SettingsWindow"));
}
void UPauseMenuWidget_OM::OpenChangeStats()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	if (!GameInstance) return;

	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();

	const float JawStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Jaw, EBodyPartSide::Center);
	const float LeftArmStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Arm, EBodyPartSide::Left);
	const float RightArmStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Arm, EBodyPartSide::Right);
	const float ThighsStrength = GameInstance->GetBodyPartLeftRightCombinedStrengthValue(EBodyPart::Thigh);
	const float CalvesStrength = GameInstance->GetBodyPartLeftRightCombinedStrengthValue(EBodyPart::Calve);

	JawStat_Slider->SetValue(JawStrength);
	LeftArmStat_Slider->SetValue(LeftArmStrength);
	RightArmStat_Slider->SetValue(RightArmStrength);
	ThighsStat_Slider->SetValue(ThighsStrength);
	CalvesStat_Slider->SetValue(CalvesStrength);
	SocialStat_Slider->SetValue(InnerStatus.Social);
	EgoStat_Slider->SetValue(InnerStatus.Ego);
	SexAppealStat_Slider->SetValue(InnerStatus.SexAppeal);

	if (UTexture2D* Image = EmotionalState_Wojak.FindRef(CurrentEmotionalState))
	{
		WojakState_Image->SetBrushFromTexture(Image);
	}
	OpenWindow(FName("ChangeStatsWindow"));

	
}

void UPauseMenuWidget_OM::OnClickQuitToTitleScreen()
{
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	if (Player)
	{
        Player->ClearTimers();
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			const FString MainMenuLevelString = "/Game/Levels/MainMenu";
			const FName LevelToChangeTo = FName(MainMenuLevelString);
			UGameplayStatics::OpenLevel(this, LevelToChangeTo);
		});
    }
}
