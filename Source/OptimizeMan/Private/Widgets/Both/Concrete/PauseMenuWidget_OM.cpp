// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Both/Concrete/PauseMenuWidget_OM.h"

#include "VREditorBaseActor.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Components/Character/Concrete/PlayerDeformationsComponent_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Game/GameInstance_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/UtilityHelpers_OMG.h"


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
			NewEmotionalState = EPlayerEmotionalStates::VeryGood;
		}
		else if (Ego >= GrindsetThreshold && (Social >= GrindsetThreshold || SexAppeal >= GrindsetThreshold))
		{
			NewEmotionalState = EPlayerEmotionalStates::Good;
		}
		else if (SexAppeal <= GoblinThreshold && Social <= GoblinThreshold && Ego >= GrindsetThreshold)
		{
			NewEmotionalState = EPlayerEmotionalStates::VeryBad;
		}
		else if (Ego <= DoomerThreshold && (Social <= DoomerThreshold || SexAppeal <= DoomerThreshold))
		{
			NewEmotionalState = EPlayerEmotionalStates::Bad;
		}
		else
		{
			NewEmotionalState = EPlayerEmotionalStates::Normal;
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
	
	GameInstance->DarkModeToggle();
	CheckAndSetDarkMode(GameInstance->GetDarkMode());
}
void UPauseMenuWidget_OM::UpdateGameSettings()
{

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

	float NewMasterVolume = GameSettings.AudioSettings.MasterVolume;
	float NewMusicVolume = GameSettings.AudioSettings.MusicVolume;
	float NewVoiceVolume = GameSettings.AudioSettings.VoiceVolume;
	float NewNotificationVolume = GameSettings.AudioSettings.NotificationVolume;
	float NewSfxVolume = GameSettings.AudioSettings.SfxVolume;

	if (MasterVolumeValue != GameSettings.AudioSettings.MasterVolume)
	{
		bChangeAudioSettings = true;
		NewMasterVolume = MasterVolumeValue;
	}
	if (MusicVolumeValue != GameSettings.AudioSettings.MusicVolume)
	{
		bChangeAudioSettings = true;
		NewMusicVolume = MusicVolumeValue;
	} 
	if (VoiceVolumeValue != GameSettings.AudioSettings.VoiceVolume)
	{
		bChangeAudioSettings = true;
		NewVoiceVolume = VoiceVolumeValue;
	} 
	if (NotificationVolumeValue != GameSettings.AudioSettings.NotificationVolume)
	{
		bChangeAudioSettings = true;
		NewNotificationVolume = NotificationVolumeValue;
	}
	if (SfxVolumeValue != GameSettings.AudioSettings.SfxVolume)
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

	FInnerStatus& InnerStatus = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetInnerStatus();

	
	const float JawValue = JawStat_Slider->GetValue();
	const float LeftArmValue = LeftArmStat_Slider->GetValue();
	const float RightArmValue = RightArmStat_Slider->GetValue();
	const float ThighsValue = ThighsStat_Slider->GetValue();
	const float CalvesValue = CalvesStat_Slider->GetValue();
	const float SocialValue = SocialStat_Slider->GetValue();
	const float EgoValue = EgoStat_Slider->GetValue();
	const float SexAppealValue = SexAppealStat_Slider->GetValue();

	float* JawStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthPtr(Jaw, Center);
	float* LeftArmStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthPtr(Arm, Left);
	float* RightArmStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthPtr(Arm, Right);
	float* LeftThighStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthPtr(Thigh, Left);
	float* RightThighStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthPtr(Thigh, Right);
	float* LeftCalveStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthPtr(Calve, Left);
	float* RightCalveStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthPtr(Calve, Right);

	GameInstance->SetStat(*JawStrength, JawValue);
	GameInstance->SetStat(*LeftArmStrength, LeftArmValue);
	GameInstance->SetStat(*RightArmStrength, RightArmValue);
	GameInstance->SetStat(*LeftThighStrength, ThighsValue);
	GameInstance->SetStat(*RightThighStrength, ThighsValue);
	GameInstance->SetStat(*LeftCalveStrength, CalvesValue);
	GameInstance->SetStat(*RightCalveStrength, CalvesValue);

	
	GameInstance->SetStat(InnerStatus.Social, SocialValue);
	GameInstance->SetStat(InnerStatus.Ego, EgoValue);
	GameInstance->SetStat(InnerStatus.SexAppeal, SexAppealValue);

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

	MasterVolume_Slider->SetValue(GameSettings.AudioSettings.MasterVolume);
	MusicVolume_Slider->SetValue(GameSettings.AudioSettings.MusicVolume);
	VoiceVolume_Slider->SetValue(GameSettings.AudioSettings.VoiceVolume);
	NotificationVolume_Slider->SetValue(GameSettings.AudioSettings.NotificationVolume);

	OpenLayer(nullptr, Settings_Grid);
}
void UPauseMenuWidget_OM::OpenChangeStats()
{

	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	FBodyStatus& BodyStatus = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyStatus();
	FInnerStatus& InnerStatus = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetInnerStatus();

	const float JawStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthValue(Jaw, Center);
	const float LeftArmStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthValue(Arm, Left);
	const float RightArmStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartStrengthValue(Arm, Right);
	const float ThighsStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartLeftRightCombinedStrengthValue(Thigh);
	const float CalvesStrength = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyPartLeftRightCombinedStrengthValue(Calve);

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
	OpenLayer(nullptr, ChangeStats_Grid);

	
}

void UPauseMenuWidget_OM::OnClickQuitToTitleScreen()
{
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
