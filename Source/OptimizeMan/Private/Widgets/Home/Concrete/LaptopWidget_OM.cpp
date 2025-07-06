// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Home/Concrete/LaptopWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Other/Bedroom/Concrete/Laptop_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Utils/UtilityHelpers_OMG.h"


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
	if (!PlasticSurgeryButton || !BankButton || !ForSkanForumButton ||
		!SupplementsShopButton || !YourHeavenXButton || !GeneralStoreButton ||
		!GeneralStorePostersButton || !GeneralStoreMusicButton || !GeneralStoreSupplyButton)
	{
		UE_LOG(LogTemp, Error, TEXT("Buttons null in Home screen for laptop"));
		return;
	}
	/*PlasticSurgeryButton->OnClicked.RemoveAll(this);
	PlasticSurgeryButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);
	BankButton->OnClicked.RemoveAll(this);
	BankButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
	ForSkanForumButton->OnClicked.RemoveAll(this);
	ForSkanForumButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
	SupplementsShopButton->OnClicked.RemoveAll(this);
	SupplementsShopButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);
	YourHeavenXButton->OnClicked.RemoveAll(this);
	YourHeavenXButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);
	GeneralStoreButton->OnClicked.RemoveAll(this);
	GeneralStoreButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreButtonClicked);*/
	GeneralStoreMusicButton->OnClicked.RemoveAll(this);
	GeneralStoreMusicButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::MusicStoreButtonClicked);
	GeneralStoreSupplyButton->OnClicked.RemoveAll(this);
	GeneralStoreSupplyButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplyStoreButtonClicked);
	GeneralStorePostersButton->OnClicked.RemoveAll(this);
	GeneralStorePostersButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PosterStoreButtonClicked);
	

	if (!PlasticSurgeryButton || !ForSkanBackButton ||
		!SupplementsShopBackButton || !YourHeavenXBackButton || !BuyDickPumpBackButton ||
		!GeneralStoreBackButton || !MusicStoreBackButton || !SupplyStoreBackButton ||
		!PosterStoreBackButton)
	{
		UE_LOG(LogTemp, Error, TEXT("One or more back buttons are null"));
		return;
	}
	
    PlasticSurgeryBackButton->OnClicked.RemoveAll(this);
    PlasticSurgeryBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
    ForSkanBackButton->OnClicked.RemoveAll(this);
    ForSkanBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
    SupplementsShopBackButton->OnClicked.RemoveAll(this);
    SupplementsShopBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
    YourHeavenXBackButton->OnClicked.RemoveAll(this);
    YourHeavenXBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
    BuyDickPumpBackButton->OnClicked.RemoveAll(this);
    BuyDickPumpBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);
	
    GeneralStoreBackButton->OnClicked.RemoveAll(this);
    GeneralStoreBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BackButtonClicked);
	MusicStoreBackButton->OnClicked.RemoveAll(this);
	MusicStoreBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreChildBackButtonClicked);
	SupplyStoreBackButton->OnClicked.RemoveAll(this);
	SupplyStoreBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreChildBackButtonClicked);
	PosterStoreBackButton->OnClicked.RemoveAll(this);
	PosterStoreBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreChildBackButtonClicked);


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
	
	HomePageLayers->SetVisibility(ESlateVisibility::Hidden);
	PlasticSurgeryLayers->SetVisibility(ESlateVisibility::Hidden);
	BankLayers->SetVisibility(ESlateVisibility::Hidden);
	ForSkanLayers->SetVisibility(ESlateVisibility::Hidden);
	SupplementsShopLayers->SetVisibility(ESlateVisibility::Hidden);
	YourHeavenXLayers->SetVisibility(ESlateVisibility::Hidden);
	YourHeavenXHomeGrid->SetVisibility(ESlateVisibility::Hidden);
	BuyDickPumpGrid->SetVisibility(ESlateVisibility::Hidden);
	GeneralStoreLayers->SetVisibility(ESlateVisibility::Hidden);
	GeneralStoreHomeGrid->SetVisibility(ESlateVisibility::Hidden);
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
	case EWebsites::GeneralStore:
		{
			OpenPageFromBackButton(EWebsites::GeneralStore, GeneralStoreLayers, GeneralStoreHomeGrid);
			break;
		}
	case EWebsites::CornSite:
		{
			OpenPageFromBackButton(EWebsites::CornSite, YourHeavenXLayers, YourHeavenXHomeGrid);
			break;
		}
	case EWebsites::SupplementsShop:
		{
			OpenPageFromBackButton(EWebsites::SupplementsShop, SupplementsShopLayers);
			break;
		}
	case EWebsites::ForSkanForum:
		{
			OpenPageFromBackButton(EWebsites::ForSkanForum, ForSkanLayers);
			break;
		}
	case EWebsites::PlasticSurgeryShop:
		{
			OpenPageFromBackButton(EWebsites::PlasticSurgeryShop, PlasticSurgeryLayers);
			break;
		}
	default:
		return;
	}
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
			/*GeneralStoreBackButton->OnClicked.RemoveAll(this);
			GeneralStoreBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			PlasticSurgeryBackButton->OnClicked.RemoveAll(this);
			PlasticSurgeryBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);*/
			BankAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreButtonClicked);
			BankAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);
			BankAdv_H_Text->SetText(FText::FromString("General Store"));
			BankAdv_V_Text->SetText(FText::FromString("Plastic Surgery"));
		}
		else
		{
/*			PlasticSurgeryBackButton->OnClicked.RemoveAll(this);
			PlasticSurgeryBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			YourHeavenXBackButton->OnClicked.RemoveAll(this);
			YourHeavenXBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);*/
			BankAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);
			BankAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);
			BankAdv_H_Text->SetText(FText::FromString("Plastic Surgery"));
			BankAdv_V_Text->SetText(FText::FromString("Brainrot Advertisement"));
		}
		break;
	}
	case EWebsites::GeneralStore:
	{
		GenrAdv_H->OnClicked.RemoveAll(this);
		GenrAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*YourHeavenXBackButton->OnClicked.RemoveAll(this);
			YourHeavenXBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreButtonClicked);
			SupplementsShopBackButton->OnClicked.RemoveAll(this);
			SupplementsShopBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreButtonClicked);*/
			GenrAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);
			GenrAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);
			GenrAdv_H_Text->SetText(FText::FromString("Brainrot Advertisement"));
			GenrAdv_V_Text->SetText(FText::FromString("Supplements"));
			UE_LOG(LogTemp, Error, TEXT("General Store Open1"));
		}
		else
		{
			/*SupplementsShopBackButton->OnClicked.RemoveAll(this);
			SupplementsShopBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreButtonClicked);*/
			//SupplementsShopBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::GeneralStoreButtonClicked);
			GenrAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			GenrAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);
			GenrAdv_H_Text->SetText(FText::FromString("Bank"));
			GenrAdv_V_Text->SetText(FText::FromString("Supplements"));
			UE_LOG(LogTemp, Error, TEXT("General Store Open2"));
		}

		break;
	}
	case EWebsites::SupplementsShop:
	{
		SuppAdv_H->OnClicked.RemoveAll(this);
		SuppAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*YourHeavenXBackButton->OnClicked.RemoveAll(this);
			YourHeavenXBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);
			ForSkanBackButton->OnClicked.RemoveAll(this);
			ForSkanBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);*/
			SuppAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);
			SuppAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			SuppAdv_H_Text->SetText(FText::FromString("Brainrot Advertisement"));
			SuppAdv_V_Text->SetText(FText::FromString("ForSkan"));
		}
		else
		{
			/*PlasticSurgeryBackButton->OnClicked.RemoveAll(this);
			PlasticSurgeryBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);*/
			SuppAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);
			SuppAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			SuppAdv_H_Text->SetText(FText::FromString("Plastic Surgery"));
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
			/*PlasticSurgeryBackButton->OnClicked.RemoveAll(this);
			PlasticSurgeryBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			YourHeavenXBackButton->OnClicked.RemoveAll(this);
			YourHeavenXBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);*/
			ForsAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);
			ForsAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);
			ForsAdv_H_Text->SetText(FText::FromString("Plastic Surgery"));
			ForsAdv_V_Text->SetText(FText::FromString("Brainrot Advertisement"));
		}
		else
		{
			/*SupplementsShopBackButton->OnClicked.RemoveAll(this);
			SupplementsShopBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			PlasticSurgeryBackButton->OnClicked.RemoveAll(this);
			PlasticSurgeryBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);*/
			ForsAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);
			ForsAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);
			ForsAdv_H_Text->SetText(FText::FromString("Supplements"));
			ForsAdv_V_Text->SetText(FText::FromString("PlasticSurgery"));
		}
		break;
	}
	case EWebsites::PlasticSurgeryShop:
	{
		PlastAdv_H->OnClicked.RemoveAll(this);
		PlastAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*YourHeavenXBackButton->OnClicked.RemoveAll(this);
			YourHeavenXBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);*/
			PlastAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			PlastAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);
			PlastAdv_H_Text->SetText(FText::FromString("Bank"));
			PlastAdv_V_Text->SetText(FText::FromString("Brainrot Advertisement"));
		}
		else
		{
			/*SupplementsShopBackButton->OnClicked.RemoveAll(this);
			SupplementsShopBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);*/
			PlastAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);
			PlastAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			PlastAdv_H_Text->SetText(FText::FromString("Supplements"));
			PlastAdv_V_Text->SetText(FText::FromString("Bank"));
		}
		break;
	}
	case EWebsites::CornSite:
	{
		CornAdv_H->OnClicked.RemoveAll(this);
		CornAdv_V->OnClicked.RemoveAll(this);
		if (GodsJudgement)
		{
			/*ForSkanBackButton->OnClicked.RemoveAll(this);
			ForSkanBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);
			PlasticSurgeryBackButton->OnClicked.RemoveAll(this);
			PlasticSurgeryBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);*/
			CornAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::ForSkanButtonClicked);
			CornAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::PlasticSurgeryButtonClicked);
			CornAdv_H_Text->SetText(FText::FromString("ForsKan"));
			CornAdv_V_Text->SetText(FText::FromString("Plastic Surgery"));
			UE_LOG(LogTemp, Error, TEXT("Corn Open 1"));
		}
		else
		{
			/*SupplementsShopBackButton->OnClicked.RemoveAll(this);
			SupplementsShopBackButton->OnClicked.AddDynamic(this, &ULaptopWidget_OM::YourHeavenXButtonClicked);*/
			CornAdv_H->OnClicked.AddDynamic(this, &ULaptopWidget_OM::SupplementsShopButtonClicked);
			CornAdv_V->OnClicked.AddDynamic(this, &ULaptopWidget_OM::BankButtonClicked);
			CornAdv_H_Text->SetText(FText::FromString("Supplements"));
			CornAdv_V_Text->SetText(FText::FromString("Bank"));
			UE_LOG(LogTemp, Error, TEXT("Corn Open 2"));
		}
		break;
	}
	default:
		return;
	}
}
void ULaptopWidget_OM::UpdateBank()
{
	const FString MoneyStringNumeral = FString::FromInt(GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetMoney());
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
	case EPlayerEmotionalStates::Bad:
		CurrentForSkanState = EForSkanType::Bad;
		UE_LOG(LogTemp, Display, TEXT("Doomer"));
		break;
	case EPlayerEmotionalStates::Normal:
		CurrentForSkanState = EForSkanType::Mixed;
		UE_LOG(LogTemp, Display, TEXT("Cope"));
		break;
	case EPlayerEmotionalStates::Good:
		CurrentForSkanState = EForSkanType::Good;
		UE_LOG(LogTemp, Display, TEXT("Grindset"));
		break;
	case EPlayerEmotionalStates::VeryGood:
		CurrentForSkanState = EForSkanType::Good;
		UE_LOG(LogTemp, Display, TEXT("Gigachad"));
		break;
	case EPlayerEmotionalStates::VeryBad:
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
