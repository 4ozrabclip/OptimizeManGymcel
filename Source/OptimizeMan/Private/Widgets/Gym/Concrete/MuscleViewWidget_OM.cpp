// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/MuscleViewWidget_OM.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Game/Persistent/GameInstance_OM.h"

void UMuscleViewWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (PumpUpButton)
	{
		PumpUpButton->OnClicked.RemoveAll(this);
		PumpUpButton->OnClicked.AddDynamic(this, &UMuscleViewWidget_OM::PumpUp);
	}

	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	UpdateStats();
}

void UMuscleViewWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	
	if (!BlackBorder || !WhiteBorder) return;
	if (bIsDarkMode)
	{
		LeftArmBorder->SetBrushFromMaterial(WhiteBorder);
		RightArmBorder->SetBrushFromMaterial(WhiteBorder);
		LeftShoulderBorder->SetBrushFromMaterial(WhiteBorder);
		RightShoulderBorder->SetBrushFromMaterial(WhiteBorder);
		LeftThighBorder->SetBrushFromMaterial(WhiteBorder);
		RightThighBorder->SetBrushFromMaterial(WhiteBorder);
		LeftCalveBorder->SetBrushFromMaterial(WhiteBorder);
		RightCalveBorder->SetBrushFromMaterial(WhiteBorder);
		LeftArmText->SetColorAndOpacity(White);
		RightArmText->SetColorAndOpacity(White);
		LeftShoulderText->SetColorAndOpacity(White);
		RightShoulderText->SetColorAndOpacity(White);
		LeftThighText->SetColorAndOpacity(White);
		RightThighText->SetColorAndOpacity(White);
		LeftCalveText->SetColorAndOpacity(White);
		RightCalveText->SetColorAndOpacity(White);
		FlexButtonText->SetColorAndOpacity(White);
		LeftSideText->SetColorAndOpacity(White);
		RightSideText->SetColorAndOpacity(White);
		FSlateBrush DarkModeBrush;
		DarkModeBrush.SetResourceObject(WhiteBorder);
		FButtonStyle DarkModeButtonStyle;
		DarkModeButtonStyle.SetNormal(DarkModeBrush);
		DarkModeButtonStyle.SetPressed(DarkModeBrush);
		PumpUpButton->SetStyle(DarkModeButtonStyle);
	}
	else
	{
		LeftArmBorder->SetBrushFromMaterial(BlackBorder);
		RightArmBorder->SetBrushFromMaterial(BlackBorder);
		LeftShoulderBorder->SetBrushFromMaterial(BlackBorder);
		RightShoulderBorder->SetBrushFromMaterial(BlackBorder);
		LeftThighBorder->SetBrushFromMaterial(BlackBorder);
		RightThighBorder->SetBrushFromMaterial(BlackBorder);
		LeftCalveBorder->SetBrushFromMaterial(BlackBorder);
		RightCalveBorder->SetBrushFromMaterial(BlackBorder);
		LeftArmText->SetColorAndOpacity(Black);
		RightArmText->SetColorAndOpacity(Black);
		LeftShoulderText->SetColorAndOpacity(Black);
		RightShoulderText->SetColorAndOpacity(Black);
		LeftThighText->SetColorAndOpacity(Black);
		RightThighText->SetColorAndOpacity(Black);
		LeftCalveText->SetColorAndOpacity(Black);
		RightCalveText->SetColorAndOpacity(Black);
		FlexButtonText->SetColorAndOpacity(Black);
		LeftSideText->SetColorAndOpacity(Black);
		RightSideText->SetColorAndOpacity(Black);
		FSlateBrush LightModeBrush;
		LightModeBrush.SetResourceObject(BlackBorder);
		FButtonStyle LightModeButtonStyle;
		LightModeButtonStyle.SetNormal(LightModeBrush);
		LightModeButtonStyle.SetPressed(LightModeBrush);
		PumpUpButton->SetStyle(LightModeButtonStyle);
	}
}

void UMuscleViewWidget_OM::UpdateStats() const
{
	if (!GameInstance) return;
	
	const float LeftArmStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Arm, EBodyPartSide::Left);
	const float RightArmStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Arm, EBodyPartSide::Right);
	const float LeftThighStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Thigh, EBodyPartSide::Left);
	const float RightThighStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Thigh, EBodyPartSide::Right);
	const float LeftCalveStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Calve, EBodyPartSide::Left);
	const float RightCalveStrength = GameInstance->GetBodyPartStrengthValue(EBodyPart::Calve, EBodyPartSide::Right);

	LeftArm_PBar->SetPercent(LeftArmStrength);
	RightArm_PBar->SetPercent(RightArmStrength);

	LeftThigh_PBar->SetPercent(LeftThighStrength);
	RightThigh_PBar->SetPercent(RightThighStrength);

	LeftCalve_PBar->SetPercent(LeftCalveStrength);
	RightCalve_PBar->SetPercent(RightCalveStrength);
}

void UMuscleViewWidget_OM::PumpUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Pump Up");
}