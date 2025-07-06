// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Other/Bedroom/Concrete/Laptop_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Other/Bedroom/Concrete/Poster_OM.h"
#include "Actors/Other/Bedroom/Concrete/Shelf_OM.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Game/GameInstance_OM.h"
#include "Utils/UtilityHelpers_OMG.h"


ALaptop_OM::ALaptop_OM()
{
	ExtraCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtraCollider"));
	ExtraCollider->SetCollisionProfileName(TEXT("Default"));
	ExtraCollider->SetupAttachment(RootComponent);
	AuraLight->SetIntensity(3.f);

	LaptopAudio = CreateDefaultSubobject<UGameAudio_OM>(TEXT("Audio Compnent"));
	LaptopAudio->bAutoActivate = true;
	LaptopAudio->SetAudioType(EAudioTypes::SfxAudio);
}

void ALaptop_OM::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Shelf)
	{
		UE_LOG(LogTemp, Error, TEXT("No Shelf assigned to laptop"));
		return;
	}
	if (!PostersClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No Poster class assigned to laptop"));
		return;
	}
	CheckAndSetDarkMode(GameInstance->GetDarkMode());
}


void ALaptop_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (!Player || !Player->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Player is invalid"));
		return;
	}
	//Player->SetCurrentPlayMode(EPlayModes::LaptopMode, this);
	GymcelUtils::GetPlayer_Gymcel(GetWorld())->TogglePlayMode(EPlayModes::LaptopMode, Player->GetInteractableOpen(), this);
}


void ALaptop_OM::SetShopAndBook(const EShopAndBook InShopAndBook)
{
	CurrentShopAndBook = InShopAndBook;
	UE_LOG(LogTemp, Warning, TEXT("Buy Item called"));
	BuyItem();
}

void ALaptop_OM::BuyItem()
{
	if (CurrentShopAndBook == EShopAndBook::None) return;
	if (!GameInstance) return;

	
	FInventoryData& InventoryData = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetInventoryData();
	FBodyStatus& BodyStatus = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetBodyStatus();


	constexpr int JawSurgeryPrice = 20;
	constexpr int SteroidsPrice = 5;
	constexpr int PreWorkoutPrice = 5;
	constexpr int ChadPosterPrice = 10;
	constexpr int WaifuPosterPrice = 15;
	constexpr float JawSurgeryIncrease = 0.9f;


	TArray<FGameplayTag> CompletedTodosCheckList;

	TArray<bool> DoesOwnPosterArray;

	const FString ChadPosterType_String = "Chad";
	const FString WaifuPosterType_String = "Waifu";
	
	FBodyPartData* Jaw = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->FindBodyPart(EBodyPart::Jaw, EBodyPartSide::Center);
	switch (CurrentShopAndBook)
	{
	case EShopAndBook::JawSurgery:
		if ((GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetMoney() >= JawSurgeryPrice) && (Jaw->Strength <= 1.f - JawSurgeryIncrease))
		{
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetMoney(-JawSurgeryPrice);
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->AddStat(Jaw->Strength, JawSurgeryIncrease);
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetPossesion(BodyStatus.bHasJawSurgery, true);

			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			
			PlaySound(BuySound);
		}
		break;
	case EShopAndBook::Steroids:
		if ((GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetMoney() >= SteroidsPrice) && (!InventoryData.bOwnsSteroids))
		{
			UE_LOG(LogTemp, Warning, TEXT("Buy steroids"));
			constexpr float SteroidsEgoIncrease = 0.9f;
			constexpr float SteroidsSexIncrease = 0.9f;
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetMoney(-SteroidsPrice);
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetPossesion(InventoryData.bOwnsSteroids,true);

			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySteroids"));
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			
			PlaySound(BuySound);
		}
		break;
	case EShopAndBook::PreWorkout:
		if ((GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetMoney() >= PreWorkoutPrice) && (!InventoryData.bOwnsPreWorkout))
		{
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetMoney(-PreWorkoutPrice);
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetPossesion(InventoryData.bOwnsPreWorkout, true);

			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			PlaySound(BuySound);
		}
		break;
	case EShopAndBook::ChadPoster:
		if ((GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetMoney() < ChadPosterPrice)) return;
		DoesOwnPosterArray.Empty();
		DoesOwnPosterArray = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetOwnedChadPosters();
		if (BuyPoster(DoesOwnPosterArray, ChadPosterType_String))
		{
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetMoney(-ChadPosterPrice);
			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			PlaySound(BuySound);
		}
		break;
	case EShopAndBook::WaifuPoster:
		if ((GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetMoney() < WaifuPosterPrice)) return;
		DoesOwnPosterArray.Empty();
		DoesOwnPosterArray = GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetOwnedWaifuPosters();
		if (BuyPoster(DoesOwnPosterArray, WaifuPosterType_String))
		{
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetMoney(-WaifuPosterPrice);
			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			PlaySound(BuySound);
		}
		break;
	default:
		CompletedTodosCheckList.Empty();
		break;
	}
	if (auto* TodoManager = Cast<UTodoManagement_OMG>(GymcelUtils::GetGameInstance_Gymcel(GetWorld())->GetSubsystem<UTodoManagement_OMG>()))
	{
		TodoManager->DelayForPlayerAchievements(CompletedTodosCheckList);
	}


	Shelf->UpdateShelfItems();
	
}
bool ALaptop_OM::BuyPoster(TArray<bool>& InPosterArray, const FString& PosterType)
{
	for (size_t PosterIndex = 0; PosterIndex < InPosterArray.Num(); PosterIndex++)
	{
		if (!InPosterArray[PosterIndex])
		{
			GymcelUtils::GetGameInstance_Gymcel(GetWorld())->SetPosterAsOwned(PosterIndex, PosterType);
			if (PostersClass)
				PostersClass->CheckOwnedPosters();
			return true;
		}
	}
	return false;
}
void ALaptop_OM::PlaySound(USoundBase* InSound)
{
	if (!InSound)
	{
		UE_LOG(LogTemp, Error, TEXT("No In Sound"));
		return;
	}
	LaptopAudio->SetSound(InSound);
	LaptopAudio->Play();
}

void ALaptop_OM::CheckAndSetDarkMode(bool bIsDarkMode)
{
	Super::CheckAndSetDarkMode(bIsDarkMode);
	if (bIsDarkMode)
	{
		AuraLight->SetAttenuationRadius(50.f);
	}
	else
	{
		AuraLight->SetAttenuationRadius(100.f);
	}
}
