// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Bedroom/Concrete/Laptop_OM.h"
#include "Utils/Structs/ForSkanData.h"
#include "Utils/Structs/LaptopData.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "LaptopWidget_OM.generated.h"

class UImage;
class UTextBlock;
class UOverlay;
class UGridPanel;
class UUniformGridPanel;
class UPanelWidget;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ULaptopWidget_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InitButtons();

private:
	void OpenPage(const EWebsites InWebsite, UOverlay* PageToOpenOverlay = nullptr, UGridPanel* PageToOpenGrid = nullptr, bool bLog = true);
	void OpenPageHelper(EWebsites InWebsite, UOverlay* PageToOpenOverlay, UGridPanel* PageToOpenGrid);
	void OpenPageFromBackButton(const EWebsites InWebsite, UOverlay* PageToOpenOverlay = nullptr, UGridPanel* PageToOpenGrid = nullptr);


	void BuyItem(const EShopAndBook InBuyItem);
	void UpdateBank();
	void SetAdvertisementsForCurrentPage();
	void SetCurrentWebsite(const EWebsites InWebsite) { CurrentWebsite = InWebsite; }
	EWebsites GetCurrentWebsite() const { return CurrentWebsite; }
	
	//------------- ForSkan Functions
	void SetForSkanText();
	void SetForSkanState();
	void SetForSkanImage();
	void SetImagesRandomly(const TArray<UTexture2D*>& InImageArray) const;
	// -----------------------------

protected: //UFUNCS
	UFUNCTION()
	void BackButtonClicked();
	UFUNCTION()
	void OpenBlessedFlesh_ButtonClicked() { OpenPage(EWebsites::BlessedFlesh, PlasticSurgeryLayers); }
	UFUNCTION()
	void BankButtonClicked() { OpenPage(EWebsites::Bank, BankLayers); }
	UFUNCTION()
	void ForSkanButtonClicked() { OpenPage(EWebsites::ForSkanForum, ForSkanLayers); }
	UFUNCTION()
	void BulkMythologyButtonClicked() { OpenPage(EWebsites::BulkMythology, BulkMythologyLayers); }
	UFUNCTION()
	void TheNattyLieButtonClicked() { OpenPage(EWebsites::TheNattyLie, TheNattyLieLayers, TheNattyLieHomeGrid); }
	UFUNCTION()
	void DickPumpSiteButtonClicked() { OpenPage(EWebsites::TheNattyLie, TheNattyLieLayers, BuyDickPumpGrid); }
	UFUNCTION()
	void OneMansTrashChildBackButtonClicked() { OpenPage(EWebsites::OneMansTrash, OneMansTrashLayers, OneMansTrashHomeGrid, false);}
    UFUNCTION()
    void OneMansTrashButtonClicked() { OpenPage(EWebsites::OneMansTrash, OneMansTrashLayers, OneMansTrashHomeGrid); }
    UFUNCTION()
    void MusicStoreButtonClicked() {  OpenPage(EWebsites::MusicStore, OneMansTrashLayers, MusicStoreGrid); }
    UFUNCTION()
    void PosterStoreButtonClicked() {  OpenPage(EWebsites::PosterStore, OneMansTrashLayers, PosterStoreGrid); }
    UFUNCTION()
    void SupplyStoreButtonClicked() {  OpenPage(EWebsites::SupplyStore, OneMansTrashLayers, SupplyStoreGrid); }
    UFUNCTION()
    void BuySteroidsButtonClicked() { BuyItem(EShopAndBook::Steroids); }
    UFUNCTION()
    void BuyBabyCrackButtonClicked() { BuyItem(EShopAndBook::PreWorkout); }
    UFUNCTION()
    void BuyJawSurgeryButtonClicked() { BuyItem(EShopAndBook::JawSurgery); }
    UFUNCTION()
    void BuyLegLengtheningSurgeryButtonClicked() { BuyItem(EShopAndBook::LegLengtheningSurgery); }
    UFUNCTION()
    void ChadPosterBuyButtonClicked() { BuyItem(EShopAndBook::ChadPoster); }
    UFUNCTION()
    void WaifuPosterBuyButtonClicked() { BuyItem(EShopAndBook::WaifuPoster); }

private:
	EWebsites CurrentWebsite;
	
	FTimerHandle FadeInTimerHandle;
	bool bIsFadingIn = false;
	EForSkanType CurrentForSkanState;

	FButtonStyle GetRandomAdvertisementStyleFromArray(const TArray<UTexture2D*>& InAdvertisements);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advertisements")
	TArray<UTexture2D*> SexyBankAdvertisements_H;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advertisements")
	TArray<UTexture2D*> ForSkanAdvertisements_V;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advertisements")
	TArray<UTexture2D*> BlessedFleshAdvertisements_V;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advertisements")
	TArray<UTexture2D*> BlessedFleshAdvertisements_H;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advertisements")
	TArray<UTexture2D*> BulkMythologyAdvertisements_V;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advertisements")
	TArray<UTexture2D*> BulkMythologyAdvertisements_H;
	

	

	// -------------------------------- PlasticSurgeryLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* PlasticSurgeryLayers;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* PlasticSurgeryGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* PlastAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlastAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* PlastAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlastAdv_V_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* BlessedFleshBack_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* JawSurgeryButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LegLengtheningSurgeryButton;

	
	// -------------------------------- BankLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* BankLayers;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* BankGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* BankAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BankAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* BankAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BankAdv_V_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoneyTextBlock;

	
	// -------------------------------- ForSkanForumLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* ForSkanLayers;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* ForSkanForumGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* ForsAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ForsAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* ForsAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ForsAdv_V_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* ForSkanBackButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ForSkan_PostTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ForSkan_PostTextBlock_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ForSkan_PostTextBlock_2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ForSkan_PostTextBlock_3;
	UPROPERTY(meta = (BindWidget))
	UImage* ForSkan_UserImage;
	UPROPERTY(meta = (BindWidget))
	UImage* ForSkan_UserImage_1;
	UPROPERTY(meta = (BindWidget))
	UImage* ForSkan_UserImage_2;
	UPROPERTY(meta = (BindWidget))
	UImage* ForSkan_UserImage_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ForSkan")
	TArray<UTexture2D*> UserPicturesGood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ForSkan")
	TArray<UTexture2D*> UserPicturesBad;
	
	
	// -------------------------------- BulkMythologyLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* BulkMythologyLayers;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* BulkMythologyGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* SuppAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SuppAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* SuppAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SuppAdv_V_Text;

	UPROPERTY(meta = (BindWidget))
	UButton* BulkMythologyBackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BuySteroidsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BuyBabyCrackButton;

	// -------------------------------- YourHeavenLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* TheNattyLieLayers;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* TheNattyLieHomeGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* CornAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CornAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* CornAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CornAdv_V_Text;
	
	UPROPERTY(meta = (BindWidget))
	UButton* TheNattyLieBackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* WatchPornButton;
	UPROPERTY(meta = (BindWidget))
	UButton* GoToDickPumpSiteButton;
	
	UPROPERTY(meta = (BindWidget))
	UGridPanel* BuyDickPumpGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* BuyDickPumpBackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BuyPumpButton;

	// -------------------------------- OneMansTrashLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* OneMansTrashLayers;
	// ----------------------------frontpage
	UPROPERTY(meta = (BindWidget))
	UGridPanel* OneMansTrashHomeGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* GenrAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GenrAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* GenrAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GenrAdv_V_Text;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OneMansTrashBackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* OneMansTrashPostersButton;
	UPROPERTY(meta = (BindWidget))
	UButton* OneMansTrashMusicButton;
	UPROPERTY(meta = (BindWidget))
	UButton* OneMansTrashSupplyButton;
	// ----------------------------poster store
	UPROPERTY(meta = (BindWidget))
	UGridPanel* PosterStoreGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* PosterStoreBackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ChadPosterBuyButton;
	UPROPERTY(meta = (BindWidget))
	UButton* AnimeGirlPosterBuyButton;
	// ---------------------------music store
	UPROPERTY(meta = (BindWidget))
	UGridPanel* MusicStoreGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* MusicStoreBackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* IndieMusicBuyButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MetalMusicBuyButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ElectroMusicBuyButton;
	UPROPERTY(meta = (BindWidget))
	UButton* RomanceMusicBuyButton;
	// ---------------------------supply store
	UPROPERTY(meta = (BindWidget))
	UGridPanel* SupplyStoreGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* SupplyStoreBackButton;

	UPROPERTY()
	ALaptop_OM* Laptop;


private:
	TArray<EWebsites> WebsiteHistoryLog;
	
};
