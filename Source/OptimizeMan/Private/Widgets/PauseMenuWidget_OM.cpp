// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseMenuWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/Components/NotificationAudio_OM.h"
#include "Actors/Characters/Player/Components/PlayerDeformationsComponent_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/BlueprintTypeConversions.h"
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
	CurrentEmotionalState = Player->GetCurrentEmotionalState();
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
			NewEmotionalState = Gigachad;
		}
		else if (Ego >= GrindsetThreshold && (Social >= GrindsetThreshold || SexAppeal >= GrindsetThreshold))
		{
			NewEmotionalState = Grindset;
		}
		else if (SexAppeal <= GoblinThreshold && Social <= GoblinThreshold && Ego >= GrindsetThreshold)
		{
			NewEmotionalState = GoblinMode;
		}
		else if (Ego <= DoomerThreshold && (Social <= DoomerThreshold || SexAppeal <= DoomerThreshold))
		{
			NewEmotionalState = Doomer;
		}
		else
		{
			NewEmotionalState = Cope;
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
	SetWidgetUIDarkLightMode();
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

	float NewMasterVolume = GameSettings.MasterVolume;
	float NewMusicVolume = GameSettings.MusicVolume;
	float NewVoiceVolume = GameSettings.VoiceVolume;
	float NewNotificationVolume = GameSettings.NotificationVolume;
	float NewSfxVolume = GameSettings.SfxVolume;

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

	FPlayerData& PlayerData = GameInstance->GetPlayerData();

	const float JawValue = JawStat_Slider->GetValue();
	const float LeftArmValue = LeftArmStat_Slider->GetValue();
	const float RightArmValue = RightArmStat_Slider->GetValue();
	const float ThighsValue = ThighsStat_Slider->GetValue();
	const float CalvesValue = CalvesStat_Slider->GetValue();
	const float SocialValue = SocialStat_Slider->GetValue();
	const float EgoValue = EgoStat_Slider->GetValue();
	const float SexAppealValue = SexAppealStat_Slider->GetValue();

	PlayerData.SetStat(PlayerData.Jaw, JawValue);
	PlayerData.SetStat(PlayerData.LeftArm, LeftArmValue);
	PlayerData.SetStat(PlayerData.RightArm, RightArmValue);
	PlayerData.SetStat(PlayerData.LowerBody, ThighsValue);
	PlayerData.SetStat(PlayerData.Calves, CalvesValue);
	PlayerData.SetStat(PlayerData.Social, SocialValue);
	PlayerData.SetStat(PlayerData.Ego, EgoValue);
	PlayerData.SetStat(PlayerData.SexAppeal, SexAppealValue);



	if (Player->GetCurrentEmotionalState() != NewEmotionalState)
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

	OpenLayer(nullptr, Settings_Grid);
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

	FPlayerData& PlayerData = GameInstance->GetPlayerData();

	JawStat_Slider->SetValue(PlayerData.Jaw);
	LeftArmStat_Slider->SetValue(PlayerData.LeftArm);
	RightArmStat_Slider->SetValue(PlayerData.RightArm);
	ThighsStat_Slider->SetValue(PlayerData.LowerBody);
	CalvesStat_Slider->SetValue(PlayerData.Calves);
	SocialStat_Slider->SetValue(PlayerData.Social);
	EgoStat_Slider->SetValue(PlayerData.Ego);
	SexAppealStat_Slider->SetValue(PlayerData.SexAppeal);

	if (UTexture2D* Image = EmotionalState_Wojak.FindRef(CurrentEmotionalState))
	{
		WojakState_Image->SetBrushFromTexture(Image);
	}
	OpenLayer(nullptr, ChangeStats_Grid);

	
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

void UPauseMenuWidget_OM::OpenLayer(UVerticalBox* InVbox, UGridPanel* InGridPanel)
{
	if (!InVbox && !InGridPanel) return;

	Base_VBox->SetVisibility(ESlateVisibility::Hidden);
	MoreOptions_VBox->SetVisibility(ESlateVisibility::Hidden);
	ChangeStats_Grid->SetVisibility(ESlateVisibility::Hidden);
	Settings_Grid->SetVisibility(ESlateVisibility::Hidden);
	AreYouSure_Grid->SetVisibility(ESlateVisibility::Hidden);

	if (InVbox) InVbox->SetVisibility(ESlateVisibility::Visible);
	if (InGridPanel) InGridPanel->SetVisibility(ESlateVisibility::Visible);
}
