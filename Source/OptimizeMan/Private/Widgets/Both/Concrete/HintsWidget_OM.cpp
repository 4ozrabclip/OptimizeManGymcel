// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Both/Concrete/HintsWidget_OM.h"

#include "Components/TextBlock.h"
#include "Game/GameInstance_OM.h"

void UHintsWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UHintsWidget_OM::ShowHint(const FText& HintTextString, float DisplayTime)
{
	if (!HintText)
	{
		UE_LOG(LogTemp, Error, TEXT("HintText TextBlock is NULL"));
		return;
	}
	if (GameInstance->GetDarkMode())
	{
		HintText->SetColorAndOpacity(White);
	}
	else
	{
		HintText->SetColorAndOpacity(Black);
	}


	HintText->SetText(HintTextString);
	SetVisibility(ESlateVisibility::HitTestInvisible);

	if (DisplayTime > 0)
	{

		GetWorld()->GetTimerManager().ClearTimer(HintTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(
		HintTimerHandle,
		this,
		&UHintsWidget_OM::HideHint,
		DisplayTime, 
		false 
		);
	}
}

void UHintsWidget_OM::HideHint()
{
	SetVisibility(ESlateVisibility::Hidden);
}
