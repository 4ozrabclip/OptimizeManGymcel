// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "CalenderWidget_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UCalenderWidget_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InitDayOverlayArray();
	void SetCalenderText();
	void SetCompletedDays();
	void ClearOverlaysForNewMonth();


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentMonthTextBlock;

	TArray<class UImage*> DayOverlays;
	
	virtual void SetWidgetUIDarkLightMode() override;

	UPROPERTY(meta = (BindWidget))
	class UBorder* CalenderBorder;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light")
	UMaterial* CalenderBackgroundDark;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light")
	UMaterial* CalenderBackgroundLight;






	
protected:
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_1;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_2;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_3;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_4;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_5;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_6;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_7;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_8;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_9;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_10;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_11;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_12;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_13;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_14;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_15;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_16;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_17;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_18;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_19;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_20;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_21;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_22;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_23;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_24;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_25;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_26;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_27;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_28;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_29;
	UPROPERTY(meta = (BindWidget))
	UImage* DayOverlay_30;
	
};
