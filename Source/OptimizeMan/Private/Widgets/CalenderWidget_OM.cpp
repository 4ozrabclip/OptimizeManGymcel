// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CalenderWidget_OM.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCalenderWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}

	SetCalenderText();
	//SetCalenderUIDarkLightMode();
	InitDayOverlayArray();
	SetCompletedDays();
}

void UCalenderWidget_OM::InitDayOverlayArray()
{
	if (constexpr int16 MaxDays = 31; DayOverlays.Num() == MaxDays)
		return;
	
	DayOverlays.Empty();
	DayOverlays.Add(DayOverlay);
	DayOverlays.Add(DayOverlay_1);
	DayOverlays.Add(DayOverlay_2);
	DayOverlays.Add(DayOverlay_3);
	DayOverlays.Add(DayOverlay_4);
	DayOverlays.Add(DayOverlay_5);
	DayOverlays.Add(DayOverlay_6);
	DayOverlays.Add(DayOverlay_7);
	DayOverlays.Add(DayOverlay_8);
	DayOverlays.Add(DayOverlay_9);
	DayOverlays.Add(DayOverlay_10);
	DayOverlays.Add(DayOverlay_11);
	DayOverlays.Add(DayOverlay_12);
	DayOverlays.Add(DayOverlay_13);
	DayOverlays.Add(DayOverlay_14);
	DayOverlays.Add(DayOverlay_15);
	DayOverlays.Add(DayOverlay_16);
	DayOverlays.Add(DayOverlay_17);
	DayOverlays.Add(DayOverlay_18);
	DayOverlays.Add(DayOverlay_19);
	DayOverlays.Add(DayOverlay_20);
	DayOverlays.Add(DayOverlay_21);
	DayOverlays.Add(DayOverlay_22);
	DayOverlays.Add(DayOverlay_23);
	DayOverlays.Add(DayOverlay_24);
	DayOverlays.Add(DayOverlay_25);
	DayOverlays.Add(DayOverlay_26);
	DayOverlays.Add(DayOverlay_27);
	DayOverlays.Add(DayOverlay_28);
	DayOverlays.Add(DayOverlay_29);
	DayOverlays.Add(DayOverlay_30);
}


void UCalenderWidget_OM::SetCalenderText()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}
	if (!CurrentMonthTextBlock) return;
	if (!GameInstance) return;

	EMonth CurrentMonth = GameInstance->GetCurrentMonth();
	
	const UEnum* MonthEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMonth"), true);
	if (!MonthEnum) return;

	FString MonthNameString = MonthEnum->GetNameStringByValue(static_cast<int64>(CurrentMonth));
	
	CurrentMonthTextBlock->SetText(FText::FromString(MonthNameString));
}

void UCalenderWidget_OM::SetCompletedDays()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}
	if (!GameInstance) return;


	// Do modulus here for over 31
	int32 DayNum = GameInstance->GetDayNumber();

	int32 CurrentDay = DayNum;

	if (CurrentDay > 31)
	{
		ClearOverlaysForNewMonth();
		CurrentDay = 1;
	}
	

	for (int i = 0; i < CurrentDay - 1; i++)
	{
		DayOverlays[i]->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}
void UCalenderWidget_OM::ClearOverlaysForNewMonth()
{
	for (int32 i = 0; i < DayOverlays.Num(); i++)
	{
		DayOverlays[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCalenderWidget_OM::SetWidgetUIDarkLightMode()
{
	Super::SetWidgetUIDarkLightMode();
	if (!CalenderBorder) return;
	if (!CalenderBackgroundDark || !CalenderBackgroundLight) return;
	if (!CurrentMonthTextBlock) return;

	if (bIsDarkMode)
	{
		CalenderBorder->Background.SetResourceObject(CalenderBackgroundDark);
		CurrentMonthTextBlock->SetColorAndOpacity(White);
	}
	else
	{
		CalenderBorder->Background.SetResourceObject(CalenderBackgroundLight);
		CurrentMonthTextBlock->SetColorAndOpacity(Black);
	}

	

	
}
