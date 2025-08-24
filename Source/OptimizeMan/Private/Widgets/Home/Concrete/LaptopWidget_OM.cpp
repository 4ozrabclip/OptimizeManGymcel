// Copyright © 2025 4ozStudio. All rights reserved.

#include "Widgets/Home/Concrete/LaptopWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Other/Bedroom/Concrete/Laptop_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"


void ULaptopWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	Laptop = Cast<ALaptop_OM>(Player->GetCurrentInteractedActor());
	if (!Laptop)
	{
		UE_LOG(LogTemp, Error, TEXT("Laptop is null"));
		return;
	}
	
	InitButtons();

	UpdateBank();

	OpenPage(EWebsites::Bank, BankLayers);

	SetForSkanState();
	SetForSkanText();
	SetForSkanImage();
}

void ULaptopWidget_OM::InitButtons()
{
	if (!OneMansTrashPostersButton || !OneMansTrashMusicButton || !OneMansTrashSupplyButton)
	{
		UE_LOG(LogTemp, Error, TEXT("Buttons null in Home screen for laptop"));
		return;
	}
	/*OpenBlessedFlesh_Button->OnClicked.RemoveAll(this);
	OpenBlessedFlesh_Button->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);
	BankButton->OnClicked.RemoveAll(this);
	BankButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
	ForSkanForumButton->OnClicked.RemoveAll(this);
	ForSkanForumButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
	BulkMythologyButton->OnClicked.RemoveAll(this);
	BulkMythologyButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);
	TheNattyLieButton->OnClicked.RemoveAll(this);
	TheNattyLieButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);
	OneMansTrashButton->OnClicked.RemoveAll(this);
	OneMansTrashButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashButtonClicked);*/
	OneMansTrashMusicButton->OnClicked.RemoveAll(this);
	OneMansTrashMusicButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::MusicStoreButtonClicked);
	OneMansTrashSupplyButton->OnClicked.RemoveAll(this);
	OneMansTrashSupplyButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplyStoreButtonClicked);
	OneMansTrashPostersButton->OnClicked.RemoveAll(this);
	OneMansTrashPostersButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PosterStoreButtonClicked);
	

	if (!ForSkanBackButton ||
		!BulkMythologyBackButton || !TheNattyLieBackButton || !BuyDickPumpBackButton ||
		!OneMansTrashBackButton || !MusicStoreBackButton || !SupplyStoreBackButton ||
		!PosterStoreBackButton)
	{
		UE_LOG(LogTemp, Error, TEXT("One or more back buttons are null"));
		return;
	}
	
    BlessedFleshBack_Button->OnClicked.RemoveAll(this);
    BlessedFleshBack_Button->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
    ForSkanBackButton->OnClicked.RemoveAll(this);
    ForSkanBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
    BulkMythologyBackButton->OnClicked.RemoveAll(this);
    BulkMythologyBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
    TheNattyLieBackButton->OnClicked.RemoveAll(this);
    TheNattyLieBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
    BuyDickPumpBackButton->OnClicked.RemoveAll(this);
    BuyDickPumpBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);
	
    OneMansTrashBackButton->OnClicked.RemoveAll(this);
    OneMansTrashBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
	MusicStoreBackButton->OnClicked.RemoveAll(this);
	MusicStoreBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashChildBackButtonClicked);
	SupplyStoreBackButton->OnClicked.RemoveAll(this);
	SupplyStoreBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashChildBackButtonClicked);
	PosterStoreBackButton->OnClicked.RemoveAll(this);
	PosterStoreBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashChildBackButtonClicked);


	if (!BuySteroidsButton || !BuyBabyCrackButton || !JawSurgeryButton ||
		!LegLengtheningSurgeryButton)
	{
		UE_LOG(LogTemp, Error, TEXT("One or more BUY Buttons is null"));
		return;
	}
	
	BuySteroidsButton->OnClicked.RemoveAll(this);
	BuySteroidsButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BuySteroidsButtonClicked);
    BuyBabyCrackButton->OnClicked.RemoveAll(this);
	BuyBabyCrackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BuyBabyCrackButtonClicked);
	JawSurgeryButton->OnClicked.RemoveAll(this);
	JawSurgeryButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BuyJawSurgeryButtonClicked);
	LegLengtheningSurgeryButton->OnClicked.RemoveAll(this);
	LegLengtheningSurgeryButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BuyLegLengtheningSurgeryButtonClicked);
	ChadPosterBuyButton->OnClicked.RemoveAll(this);
	ChadPosterBuyButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ChadPosterBuyButtonClicked);
	AnimeGirlPosterBuyButton->OnClicked.RemoveAll(this);
	AnimeGirlPosterBuyButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::WaifuPosterBuyButtonClicked);
}
void ULaptopWidget_OM::OpenPage(const EWebsites InWebsite, UOverlay* PageToOpenOverlay, UGridPanel* PageToOpenGrid, bool bLog)
{
	OpenPageHelper(InWebsite, PageToOpenOverlay, PageToOpenGrid);
	if (InWebsite == EWebsites::Bank)
	{
		WebsiteHistoryLog.Empty();
	}
	if (InWebsite != EWebsites::SupplyStore && InWebsite != EWebsites::PosterStore && InWebsite != EWebsites::MusicStore && bLog)
	{
		WebsiteHistoryLog.Add(InWebsite);
	}
}
void ULaptopWidget_OM::OpenPageHelper(const EWebsites InWebsite, UOverlay* PageToOpenOverlay,
	UGridPanel* PageToOpenGrid)
{
	if (!PageToOpenOverlay && !PageToOpenGrid) return;
	
	PlasticSurgeryLayers->SetVisibility(ESlateVisibility::Hidden);
	BankLayers->SetVisibility(ESlateVisibility::Hidden);
	ForSkanLayers->SetVisibility(ESlateVisibility::Hidden);
	BulkMythologyLayers->SetVisibility(ESlateVisibility::Hidden);
	TheNattyLieLayers->SetVisibility(ESlateVisibility::Hidden);
	TheNattyLieHomeGrid->SetVisibility(ESlateVisibility::Hidden);
	BuyDickPumpGrid->SetVisibility(ESlateVisibility::Hidden);
	OneMansTrashLayers->SetVisibility(ESlateVisibility::Hidden);
	OneMansTrashHomeGrid->SetVisibility(ESlateVisibility::Hidden);
	SupplyStoreGrid->SetVisibility(ESlateVisibility::Hidden);
	MusicStoreGrid->SetVisibility(ESlateVisibility::Hidden);
	PosterStoreGrid->SetVisibility(ESlateVisibility::Hidden);
	
	SetCurrentWebsite(InWebsite);
	

		
	if (PageToOpenOverlay)
		PageToOpenOverlay->SetVisibility(ESlateVisibility::Visible);
	
	if (PageToOpenGrid)
		PageToOpenGrid->SetVisibility(ESlateVisibility::Visible);
	
	SetAdvertisementsForCurrentPage();

}

void ULaptopWidget_OM::OpenPageFromBackButton(const EWebsites InWebsite, UOverlay* PageToOpenOverlay,
	UGridPanel* PageToOpenGrid)
{
	OpenPageHelper(InWebsite, PageToOpenOverlay, PageToOpenGrid);
	if (InWebsite == EWebsites::Bank)
	{
		WebsiteHistoryLog.Empty();
	}
	else
	{
		if (!WebsiteHistoryLog.IsValidIndex(WebsiteHistoryLog.Num() - 1))
		{
			UE_LOG(LogTemp, Error, TEXT("not valid website index"));
			OnExitButtonClicked();
			return;
		}
		WebsiteHistoryLog.RemoveAt(WebsiteHistoryLog.Num() - 1);
	}
	
}

void ULaptopWidget_OM::BackButtonClicked()
{
	int PreviousWebsiteIndex = WebsiteHistoryLog.Num() - 2;

	if (!WebsiteHistoryLog.IsValidIndex(PreviousWebsiteIndex))
	{
		OpenPage(EWebsites::Bank, BankLayers);
		return;
	}
	EWebsites PreviousWebsite = WebsiteHistoryLog[PreviousWebsiteIndex];

	switch (PreviousWebsite)
	{
	case EWebsites::Bank:
		{
			OpenPage(EWebsites::Bank, BankLayers);
			break;
		}
	case EWebsites::OneMansTrash:
		{
			OpenPageFromBackButton(EWebsites::OneMansTrash, OneMansTrashLayers, OneMansTrashHomeGrid);
			break;
		}
	case EWebsites::TheNattyLie:
		{
			OpenPageFromBackButton(EWebsites::TheNattyLie, TheNattyLieLayers, TheNattyLieHomeGrid);
			break;
		}
	case EWebsites::BulkMythology:
		{
			OpenPageFromBackButton(EWebsites::BulkMythology, BulkMythologyLayers);
			break;
		}
	case EWebsites::ForSkanForum:
		{
			OpenPageFromBackButton(EWebsites::ForSkanForum, ForSkanLayers);
			break;
		}
	case EWebsites::BlessedFlesh:
		{
			OpenPageFromBackButton(EWebsites::BlessedFlesh, PlasticSurgeryLayers);
			break;
		}
	default:
		return;
	}
}

FButtonStyle ULaptopWidget_OM::GetRandomAdvertisementStyleFromArray(const TArray<UTexture2D*>& InAdvertisements)
{

	FButtonStyle OutStyle;
	
	if (InAdvertisements.Num() <= 0) return OutStyle;

	const int RandIndex = FMath::RandRange(0, InAdvertisements.Num() - 1);

	if (UTexture2D* Image = InAdvertisements[RandIndex])
	{
		OutStyle.Normal.SetResourceObject(Image);
		OutStyle.Normal.TintColor = FLinearColor::White;
		OutStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
		OutStyle.Disabled.SetResourceObject(Image);
		OutStyle.Disabled.TintColor = FLinearColor::White;
		OutStyle.Disabled.DrawAs = ESlateBrushDrawType::Image;
		OutStyle.Hovered.SetResourceObject(Image);
		OutStyle.Hovered.TintColor = FLinearColor::White;
		OutStyle.Hovered.DrawAs = ESlateBrushDrawType::Image;
		OutStyle.Pressed.SetResourceObject(Image);
		OutStyle.Pressed.TintColor = FLinearColor::White;
		OutStyle.Pressed.DrawAs = ESlateBrushDrawType::Image;
	}
	
	return OutStyle;
	
}

void ULaptopWidget_OM::SetAdvertisementsForCurrentPage()
{
	const bool GodsJudgement = FMath::RandRange(0, 1) == 1;
	
	switch (CurrentWebsite)
	{
	case EWebsites::Bank:
	{
		BankAdv_H->OnClicked.RemoveAll(this);
		BankAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*OneMansTrashBackButton->OnClicked.RemoveAll(this);
			OneMansTrashBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			BlessedFleshBack_Button->OnClicked.RemoveAll(this);
			BlessedFleshBack_Button->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);*/
			BankAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashButtonClicked);
			BankAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);
			BankAdv_V->SetStyle(GetRandomAdvertisementStyleFromArray(BlessedFleshAdvertisements_V));
			BankAdv_H_Text->SetText(FText::FromString("General Store"));
		}
		else
		{
/*			BlessedFleshBack_Button->OnClicked.RemoveAll(this);
			BlessedFleshBack_Button->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			TheNattyLieBackButton->OnClicked.RemoveAll(this);
			TheNattyLieBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);*/
			BankAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);
			BankAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);
			BankAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(BlessedFleshAdvertisements_H));
			BankAdv_V_Text->SetText(FText::FromString("The Natty lie"));
		}
		break;
	}
	case EWebsites::OneMansTrash:
	{
		GenrAdv_H->OnClicked.RemoveAll(this);
		GenrAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*TheNattyLieBackButton->OnClicked.RemoveAll(this);
			TheNattyLieBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashButtonClicked);
			BulkMythologyBackButton->OnClicked.RemoveAll(this);
			BulkMythologyBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashButtonClicked);*/
			GenrAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);
			GenrAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);
			GenrAdv_V_Text->SetText(FText::FromString("Brainrot Advertisement"));
			GenrAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(BulkMythologyAdvertisements_H));
			UE_LOG(LogTemp, Error, TEXT("General Store Open1"));
		}
		else
		{
			/*BulkMythologyBackButton->OnClicked.RemoveAll(this);
			BulkMythologyBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashButtonClicked);*/
			//BulkMythologyBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OneMansTrashButtonClicked);
			GenrAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			GenrAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);
			GenrAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(SexyBankAdvertisements_H));
			GenrAdv_V->SetStyle(GetRandomAdvertisementStyleFromArray(BulkMythologyAdvertisements_V));
		}
		break;
	}
	case EWebsites::BulkMythology:
	{
		SuppAdv_H->OnClicked.RemoveAll(this);
		SuppAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*TheNattyLieBackButton->OnClicked.RemoveAll(this);
			TheNattyLieBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);
			ForSkanBackButton->OnClicked.RemoveAll(this);
			ForSkanBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);*/
			SuppAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);
			SuppAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			SuppAdv_V->SetStyle(GetRandomAdvertisementStyleFromArray(ForSkanAdvertisements_V));
			SuppAdv_H_Text->SetText(FText::FromString("Brainrot Advertisement"));
		}
		else
		{
			/*BlessedFleshBack_Button->OnClicked.RemoveAll(this);
			BlessedFleshBack_Button->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);*/
			SuppAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);
			SuppAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			SuppAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(BlessedFleshAdvertisements_H));
			SuppAdv_V_Text->SetText(FText::FromString("Bank"));
		}
		break;
	}
	case EWebsites::ForSkanForum:
	{
		ForsAdv_H->OnClicked.RemoveAll(this);
		ForsAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*BlessedFleshBack_Button->OnClicked.RemoveAll(this);
			BlessedFleshBack_Button->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			TheNattyLieBackButton->OnClicked.RemoveAll(this);
			TheNattyLieBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);*/
			ForsAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);
			ForsAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);
			ForsAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(BlessedFleshAdvertisements_H));
			ForsAdv_V->SetStyle(GetRandomAdvertisementStyleFromArray(BulkMythologyAdvertisements_V));
		}
		else
		{
			/*BulkMythologyBackButton->OnClicked.RemoveAll(this);
			BulkMythologyBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			BlessedFleshBack_Button->OnClicked.RemoveAll(this);
			BlessedFleshBack_Button->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);*/
			ForsAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);
			ForsAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);
			ForsAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(BulkMythologyAdvertisements_H));
			ForsAdv_V->SetStyle(GetRandomAdvertisementStyleFromArray(BlessedFleshAdvertisements_V));
		}
		break;
	}
	case EWebsites::BlessedFlesh:
	{
		PlastAdv_H->OnClicked.RemoveAll(this);
		PlastAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*TheNattyLieBackButton->OnClicked.RemoveAll(this);
			TheNattyLieBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);*/
			PlastAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			PlastAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);
			PlastAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(SexyBankAdvertisements_H));
			PlastAdv_V_Text->SetText(FText::FromString("Brainrot Advertisement"));
		}
		else
		{
			/*BulkMythologyBackButton->OnClicked.RemoveAll(this);
			BulkMythologyBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);*/
			PlastAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);
			PlastAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			PlastAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(BulkMythologyAdvertisements_H));
			PlastAdv_V->SetStyle(GetRandomAdvertisementStyleFromArray(ForSkanAdvertisements_V));
		}
		break;
	}
	case EWebsites::TheNattyLie:
	{
		CornAdv_H->OnClicked.RemoveAll(this);
		CornAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*ForSkanBackButton->OnClicked.RemoveAll(this);
			ForSkanBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);
			BlessedFleshBack_Button->OnClicked.RemoveAll(this);
			BlessedFleshBack_Button->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);*/
			CornAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			CornAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::OpenBlessedFlesh_ButtonClicked);
			CornAdv_H_Text->SetText(FText::FromString("ForsKan"));
			CornAdv_V->SetStyle(GetRandomAdvertisementStyleFromArray(BlessedFleshAdvertisements_V));
		}
		else
		{
			/*BulkMythologyBackButton->OnClicked.RemoveAll(this);
			BulkMythologyBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::TheNattyLieButtonClicked);*/
			CornAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BulkMythologyButtonClicked);
			CornAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			CornAdv_H->SetStyle(GetRandomAdvertisementStyleFromArray(BulkMythologyAdvertisements_H));
			CornAdv_V_Text->SetText(FText::FromString("Bank"));
		}
		break;
	}
	default:
		return;
	}
}
void ULaptopWidget_OM::UpdateBank()
{
	const FString MoneyStringNumeral = FString::FromInt(GameInstance->GetMoney());
	const FString MoneyString = FString::Format(TEXT("${0}"), {MoneyStringNumeral});

	MoneyTextBlock->SetText(FText::FromString(MoneyString));
	
}

void ULaptopWidget_OM::SetForSkanText()
{
	if (!ForSkan_PostTextBlock || !ForSkan_PostTextBlock_1 ||
		!ForSkan_PostTextBlock_2 || !ForSkan_PostTextBlock_3)
		return;
	if (!ForSkan_UserImage || !ForSkan_UserImage_1 || !ForSkan_UserImage_2 || !ForSkan_UserImage_3) return;
	
	const FDayInfo& DayInfo = GameInstance->GetDayInfo();

	FString DailyText;
	FString MoodText;
	FString MoodText2;
	FString MoodText3;

	TArray<FString> UserTextStrings;

	
	for (TPair<EForSkanType, TArray<FString>>& Pair : FForSkanData::ForSkanPotentialStrings)
	{
		if (Pair.Key == CurrentForSkanState)
		{
			const int SizeOfPotentialStringArray = Pair.Value.Num();
			if (constexpr int SizeOfMoodTexts = 5; SizeOfPotentialStringArray < SizeOfMoodTexts) return;
			const int RandomIndex1 = FMath::RandRange(0, SizeOfPotentialStringArray - 1);
			int RandomIndex2;
			do
			{
				RandomIndex2 = FMath::RandRange(0, SizeOfPotentialStringArray - 1);
			} while (RandomIndex2 == RandomIndex1);
			int RandomIndex3;
			do
			{
				RandomIndex3 = FMath::RandRange(0, SizeOfPotentialStringArray - 1);
			} while (RandomIndex3 == RandomIndex1 || RandomIndex3 == RandomIndex2);
			
			MoodText = Pair.Value[RandomIndex1];
			MoodText2 = Pair.Value[RandomIndex2];
			MoodText3 = Pair.Value[RandomIndex3];
			break;
		}
	}

	
	
	switch (DayInfo.CurrentDay)
	{
	case EWeekDay::Monday:
		DailyText = "ITS MONDAY BITCH";
		break;
	case EWeekDay::Tuesday:
		DailyText = "ITS TUESADY";
		break;
	case EWeekDay::Wednesday:
		DailyText = "ITS WEDNES";
		break;
	case EWeekDay::Thursday:
		DailyText = "ITS THURSDAY";
		break;
	case EWeekDay::Friday:
		DailyText = "ITS FRIDAY";
		break;
	case EWeekDay::Saturday:
		DailyText = "ITS SATURDAY";
		break;
	case EWeekDay::Sunday:
		DailyText = "ITS SUNDAY";
		break;
	default:
		DailyText = "YOU SUCK";
		break;
	}

	const int RandomNumber = FMath::RandRange(0, 100);

	if (DailyText.Len() <= 0 || MoodText.Len() <= 0 || MoodText2.Len() <= 0 || MoodText3.Len() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("One or more  of the texts (Daily,mood etc) for ForSkan are not initializing"));
		return;
	}
	

	if (RandomNumber > 75)
	{
		ForSkan_PostTextBlock->SetText(FText::FromString(DailyText));
		ForSkan_PostTextBlock_1->SetText(FText::FromString(MoodText));
		ForSkan_PostTextBlock_2->SetText(FText::FromString(MoodText2));
		ForSkan_PostTextBlock_3->SetText(FText::FromString(MoodText3));
	}
	else if (RandomNumber > 50)
	{
		ForSkan_PostTextBlock->SetText(FText::FromString(MoodText));
		ForSkan_PostTextBlock_1->SetText(FText::FromString(DailyText));
		ForSkan_PostTextBlock_2->SetText(FText::FromString(MoodText2));
		ForSkan_PostTextBlock_3->SetText(FText::FromString(MoodText3));
	}
	else if (RandomNumber > 25)
	{
		ForSkan_PostTextBlock->SetText(FText::FromString(MoodText));
		ForSkan_PostTextBlock_1->SetText(FText::FromString(MoodText2));
		ForSkan_PostTextBlock_2->SetText(FText::FromString(DailyText));
		ForSkan_PostTextBlock_3->SetText(FText::FromString(MoodText3));
	}
	else
	{
		ForSkan_PostTextBlock->SetText(FText::FromString(MoodText));
		ForSkan_PostTextBlock_1->SetText(FText::FromString(MoodText2));
		ForSkan_PostTextBlock_2->SetText(FText::FromString(MoodText3));
		ForSkan_PostTextBlock_3->SetText(FText::FromString(DailyText));
	}

}

void ULaptopWidget_OM::SetForSkanState()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	switch (GameInstance->GetCurrentEmotionalState())
	{
	case EPlayerEmotionalStates::Doomer:
		CurrentForSkanState = EForSkanType::Bad;
		UE_LOG(LogTemp, Display, TEXT("Doomer"));
		break;
	case EPlayerEmotionalStates::Cope:
		CurrentForSkanState = EForSkanType::Mixed;
		UE_LOG(LogTemp, Display, TEXT("Cope"));
		break;
	case EPlayerEmotionalStates::Grindset:
		CurrentForSkanState = EForSkanType::Good;
		UE_LOG(LogTemp, Display, TEXT("Grindset"));
		break;
	case EPlayerEmotionalStates::Gigachad:
		CurrentForSkanState = EForSkanType::Good;
		UE_LOG(LogTemp, Display, TEXT("Gigachad"));
		break;
	case EPlayerEmotionalStates::GoblinMode:
		CurrentForSkanState = EForSkanType::Crazy;
		UE_LOG(LogTemp, Display, TEXT("GoblinMode"));
		break;
	default:
		CurrentForSkanState = EForSkanType::Mixed;
		UE_LOG(LogTemp, Display, TEXT("WASAFASFASFASFASFASFS"));
		break;
	}
}

void ULaptopWidget_OM::SetForSkanImage()
{
	if (constexpr int MaxPosts = 4; UserPicturesBad.Num() < MaxPosts ||
		UserPicturesGood.Num() < MaxPosts) return;
	

	UE_LOG(LogTemp, Error, TEXT("CALLED SETUP IMAGE"));
	switch (CurrentForSkanState)
	{
	case EForSkanType::Bad:
		SetImagesRandomly(UserPicturesBad);
		break;
	case EForSkanType::Good:
		SetImagesRandomly(UserPicturesGood);
		break;
	default:
		SetImagesRandomly(UserPicturesGood);
		break;
	}
}

void ULaptopWidget_OM::SetImagesRandomly(const TArray<UTexture2D*>& InImageArray) const
{
	
	UE_LOG(LogTemp, Error, TEXT("CALLED SET IMAGES RANDOMLY"));
	const int SizeOfUserImagesArray = InImageArray.Num();
	const int RandomIndex1 = FMath::RandRange(0, SizeOfUserImagesArray - 1);
	int RandomIndex2;
	do
	{
		RandomIndex2 = FMath::RandRange(0, SizeOfUserImagesArray - 1);
	} while (RandomIndex2 == RandomIndex1);
	int RandomIndex3;
	do
	{
		RandomIndex3 = FMath::RandRange(0, SizeOfUserImagesArray - 1);
	} while (RandomIndex3 == RandomIndex1 || RandomIndex3 == RandomIndex2);
	int RandomIndex4;
	do
	{
		RandomIndex4 = FMath::RandRange(0, SizeOfUserImagesArray - 1);
	} while (RandomIndex4 == RandomIndex3 || RandomIndex4 == RandomIndex2 || RandomIndex4 == RandomIndex1);
	
	if (InImageArray.IsValidIndex(RandomIndex1))
		ForSkan_UserImage->SetBrushResourceObject(InImageArray[RandomIndex1]);
	if (InImageArray.IsValidIndex(RandomIndex2))
		ForSkan_UserImage_1->SetBrushResourceObject(InImageArray[RandomIndex2]);
	if (InImageArray.IsValidIndex(RandomIndex3))
		ForSkan_UserImage_2->SetBrushResourceObject(InImageArray[RandomIndex3]);
	if (InImageArray.IsValidIndex(RandomIndex4))
		ForSkan_UserImage_3->SetBrushResourceObject(InImageArray[RandomIndex4]);
}

void ULaptopWidget_OM::BuyItem(const EShopAndBook InBuyItem)
{
	if (!Laptop)
	{
		UE_LOG(LogTemp, Error, TEXT("Laptop pointer null in buy item"));
		return;
	}
	Laptop->SetShopAndBook(InBuyItem);
	UpdateBank();
}
