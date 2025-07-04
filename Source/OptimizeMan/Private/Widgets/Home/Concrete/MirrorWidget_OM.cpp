// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Home/Concrete/MirrorWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Management/AbilitySystemComponent_OM.h"
#include "GameplayAbilitySystem/AttributeSets/Concrete/MentalHealthStats_OM.h"
#include "Utils/UtilityHelpers_OMG.h"


void UMirrorWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	CheckAndSetDarkMode(GameInstance->GetDarkMode());
	
	UpdateStats();
	CheckAndSetWarningText();
	
}


void UMirrorWidget_OM::CheckAndSetDarkMode(const bool bIsDarkMode)
{
	Super::CheckAndSetDarkMode(bIsDarkMode);
	if (bIsDarkMode)
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

	FString WarningText_String = TEXT("");


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
	
	const FInnerStatus& InnerStatus = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetInnerStatus();


	const UAbilitySystemComponent_OM* AbSysComp = Cast<UAbilitySystemComponent_OM>(Player->GetAbilitySystemComponent());
	if (!AbSysComp) return;
	if (const UMentalHealthStats_OM* Ment = AbSysComp->GetSet<UMentalHealthStats_OM>())
	{
		const float EgoValue = Ment->GetEgo();
		const float SocialValue = Ment->GetSocial();
		const float SexAppealValue = Ment->GetSexAppeal();
		UpdateStatBar(EgoValue, EgoPositiveBar, EgoNegativeBar);
		UpdateStatBar(SocialValue, SocialPositiveBar, SocialNegativeBar);
		UpdateStatBar(SexAppealValue, SexPositiveBar, SexNegativeBar);
	}
	
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
	
}