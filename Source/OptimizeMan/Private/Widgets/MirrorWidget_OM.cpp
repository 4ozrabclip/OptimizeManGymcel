// Fill out your copyright notice in the Description page of Project Settings.


#include "OptimizeMan/Public/Widgets/MirrorWidget_OM.h"

#include "Actors/Items/Mirror_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Utils/GameInstance_OM.h"


void UMirrorWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	CheckAndSetForDarkLightMode();
	
	UpdateStats();
	CheckAndSetWarningText();
	
}
void UMirrorWidget_OM::CheckAndSetForDarkLightMode()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}
	if (GameInstance && GameInstance->GetDarkMode())
	{
		EgoImage->SetBrushResourceObject(EgoWhiteText);
		SexAppealImage->SetBrushResourceObject(SexAppealWhiteText);
		SocialImage->SetBrushResourceObject(SocialWhiteText);
		WarningText->SetColorAndOpacity(White);
	}
	else
	{
		EgoImage->SetBrushResourceObject(EgoBlackText);
		SexAppealImage->SetBrushResourceObject(SexAppealBlackText);
		SocialImage->SetBrushResourceObject(SocialBlackText);
		WarningText->SetColorAndOpacity(Black);
	}
}

void UMirrorWidget_OM::CheckAndSetWarningText()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Game instance is null in mirror widget"));
		return;
	}

	FString WarningText_String = TEXT("");
	
	if (GameInstance->GetCurrentlyOnSteroids())
		WarningText_String = TEXT("You have gyno");

	WarningText->SetText(FText::FromString(WarningText_String));
}
void UMirrorWidget_OM::UpdateStats()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Game instance is null in mirror widget"));
		return;
	}
	
	const FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();


	
	UpdateStatBar(InnerStatus.Ego, EgoPositiveBar, EgoNegativeBar);
	UpdateStatBar(InnerStatus.Social, SocialPositiveBar, SocialNegativeBar);
	UpdateStatBar(InnerStatus.SexAppeal, SexPositiveBar, SexNegativeBar);
	
}
void UMirrorWidget_OM::UpdateStatBar(const float InTypeStat, UProgressBar* InPositiveBar, UProgressBar* InNegativeBar)
{
	if (!InPositiveBar || !InNegativeBar)
	{
		UE_LOG(LogTemp, Error, TEXT("InPositiveBar or InNegativeBar is null in mirror widget"));
		return;
	}
	if (InTypeStat < 0)
	{
		InNegativeBar->SetPercent(InTypeStat * -1.f);
		InPositiveBar->SetPercent(0.f);
	}
	else if (InTypeStat > 0)
	{
		InPositiveBar->SetPercent(InTypeStat);
		InNegativeBar->SetPercent(0.f);
	}
	else
	{
		InPositiveBar->SetPercent(0.f);
		InNegativeBar->SetPercent(0.f);
	}
	UE_LOG(LogTemp, Log, TEXT("InTypeStat: %f"), InTypeStat);
	
}