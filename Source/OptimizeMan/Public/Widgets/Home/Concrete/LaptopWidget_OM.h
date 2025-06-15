// Fill out your copyright notice in the Description page of Project Settings.

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
	void PlasticSurgeryButtonClicked() { OpenPage(PlasticSurgeryShop, PlasticSurgeryLayers); }
	UFUNCTION()
	void BankButtonClicked() { OpenPage(Bank, BankLayers); }
	UFUNCTION()
	void ForSkanButtonClicked() { OpenPage(ForSkanForum, ForSkanLayers); }
	UFUNCTION()
	void SupplementsShopButtonClicked() { OpenPage(SupplementsShop, SupplementsShopLayers); }
	UFUNCTION()
	void YourHeavenXButtonClicked() { OpenPage(CornSite, YourHeavenXLayers, YourHeavenXHomeGrid); }
	UFUNCTION()
	void DickPumpSiteButtonClicked() { OpenPage(CornSite, YourHeavenXLayers, BuyDickPumpGrid); }
	UFUNCTION()
	void GeneralStoreChildBackButtonClicked() { OpenPage(GeneralStore, GeneralStoreLayers, GeneralStoreHomeGrid, false);}
    UFUNCTION()
    void GeneralStoreButtonClicked() { OpenPage(GeneralStore, GeneralStoreLayers, GeneralStoreHomeGrid); }
    UFUNCTION()
    void MusicStoreButtonClicked() {  OpenPage(MusicStore, GeneralStoreLayers, MusicStoreGrid); }
    UFUNCTION()
    void PosterStoreButtonClicked() {  OpenPage(PosterStore, GeneralStoreLayers, PosterStoreGrid); }
    UFUNCTION()
    void SupplyStoreButtonClicked() {  OpenPage(SupplyStore, GeneralStoreLayers, SupplyStoreGrid); }
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
    UFUNCTION()
    void OpenHomePage() { OpenPage(Bank, HomePageLayers); }

private:
	EWebsites CurrentWebsite;
	
	FTimerHandle FadeInTimerHandle;
	bool bIsFadingIn = false;
	EForSkanType CurrentForSkanState;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advertisements")
	TMap<TEnumAsByte<EWebsites>, UTexture2D*> AdvertisementMap;
	
	// -------------------------------- HomePageLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* HomePageLayers;
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* HomePageGridLayer;
	UPROPERTY(meta = (BindWidget))
	UButton* PlasticSurgeryButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BankButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ForSkanForumButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SupplementsShopButton;
	UPROPERTY(meta = (BindWidget))
	UButton* YourHeavenXButton;
	UPROPERTY(meta = (BindWidget))
	UButton* GeneralStoreButton;

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
	UButton* PlasticSurgeryBackButton;
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
	
	
	// -------------------------------- SupplementsShopLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* SupplementsShopLayers;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* SupplementsShopGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* SuppAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SuppAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* SuppAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SuppAdv_V_Text;

	UPROPERTY(meta = (BindWidget))
	UButton* SupplementsShopBackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BuySteroidsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BuyBabyCrackButton;

	// -------------------------------- YourHeavenLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* YourHeavenXLayers;
	UPROPERTY(meta = (BindWidget))
	UGridPanel* YourHeavenXHomeGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* CornAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CornAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* CornAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CornAdv_V_Text;
	
	UPROPERTY(meta = (BindWidget))
	UButton* YourHeavenXBackButton;
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

	// -------------------------------- GeneralStoreLayer
	UPROPERTY(meta = (BindWidget))
	UOverlay* GeneralStoreLayers;
	// ----------------------------frontpage
	UPROPERTY(meta = (BindWidget))
	UGridPanel* GeneralStoreHomeGrid;
	UPROPERTY(meta = (BindWidget))
	UButton* GenrAdv_H;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GenrAdv_H_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* GenrAdv_V;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GenrAdv_V_Text;
	
	UPROPERTY(meta = (BindWidget))
	UButton* GeneralStoreBackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* GeneralStorePostersButton;
	UPROPERTY(meta = (BindWidget))
	UButton* GeneralStoreMusicButton;
	UPROPERTY(meta = (BindWidget))
	UButton* GeneralStoreSupplyButton;
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
