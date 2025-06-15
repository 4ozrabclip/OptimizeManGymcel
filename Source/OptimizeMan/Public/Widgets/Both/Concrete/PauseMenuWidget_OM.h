// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "PauseMenuWidget_OM.generated.h"

class UImage;
class USlider;
class UTextBlock;
class UGridPanel;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UPauseMenuWidget_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void OnClickToggleLightDark();
	UFUNCTION()
	void UpdateGameSettings();
	UFUNCTION()
	void UpdatePlayerStats();
	UFUNCTION()
	void OpenSettings();

	UFUNCTION()
	void OpenMoreOptions() { OpenLayer(MoreOptions_VBox); }
	UFUNCTION()
	void OpenBase() { OpenLayer(Base_VBox); }
	UFUNCTION()
	void OpenQuitScreen() { OpenLayer(nullptr, AreYouSure_Grid); }
	UFUNCTION()
	void OpenChangeStats();

	UFUNCTION()
	void OnClickQuitToTitleScreen();

	void OpenLayer(UVerticalBox* InVbox = nullptr, UGridPanel* InGridPanel = nullptr);

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* Base_VBox;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MoreOptions_VBox;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* ChangeStats_Grid;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* Settings_Grid;

	// Base
	UPROPERTY(meta = (BindWidget))
	UButton* ToggleLightDarkButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MoreSettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* OpenQuitScreenButton;


	// MoreOptions
	UPROPERTY(meta = (BindWidget))
	UGridPanel* AreYouSure_Grid;
	UPROPERTY(meta = (BindWidget))
	UButton* ChangeStatsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsAudioButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromMoreOptionsButton;

	// Are You Sure Quit
	UPROPERTY(meta = (BindWidget))
	UButton* BackToBaseButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitToTitleScreenButton;

	// Settings
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MasterVolume_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MusicVolume_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* VoiceVolume_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NotificationVolume_Text;
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
	UButton* AcceptSettings_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromSettings_Button;
	
	
	// Change Stats Testing
	UPROPERTY(meta = (BindWidget))
	UImage* WojakState_Image;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MentalStatsTitle;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PhysicalStatsTitle;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SocialStat_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EgoStat_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SexAppealStat_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* JawStat_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LeftArmStat_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RightArmStat_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ThighsStat_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CalvesStat_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* JumpStrengthStat_Text;
	UPROPERTY(meta = (BindWidget))
	USlider* SocialStat_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* SexAppealStat_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* EgoStat_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* JawStat_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* LeftArmStat_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* RightArmStat_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* ThighsStat_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* CalvesStat_Slider;
	UPROPERTY(meta = (BindWidget))
	USlider* JumpStrengthStat_Slider;
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromChangeStats_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* AcceptStats_Button;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotional State")
	TMap<TEnumAsByte<EPlayerEmotionalStates>, UTexture2D*> EmotionalState_Wojak;

private:
	EPlayerEmotionalStates CurrentEmotionalState;
	EPlayerEmotionalStates NewEmotionalState;

	
	
};
