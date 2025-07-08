// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Other/Bedroom/Concrete/Laptop_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Other/Bedroom/Concrete/Poster_OM.h"
#include "Actors/Other/Bedroom/Concrete/Shelf_OM.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Game/Persistent/Subsystems/TodoManagementSubsystem.h"
#include "Utils/Structs/AudioTypes.h"

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
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
		UE_LOG(LogTemp, Error, TEXT("RECAST GAME INSTANCE IN LAPTOP"));
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to recast in laptop"));
		return;
	}
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		UE_LOG(LogTemp, Error, TEXT("RECAST PLAYER IN LAPTOP"));
	}
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to recast in laptop"));
		return;
	}
		
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
	DarkModeToggle(GameInstance->GetDarkMode());
}

void ALaptop_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	if (bIsDarkMode)
	{
		AuraLight->SetAttenuationRadius(50.f);
	}
	else
	{
		AuraLight->SetAttenuationRadius(100.f);
	}
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
	Player->TogglePlayMode(EPlayModes::LaptopMode, Player->bInteractableOpen, this);
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
	if (!TodoManager)
	{
		TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	}
	
	FInventoryData& InventoryData = GameInstance->GetInventoryData();
	FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();


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
	
	FBodyPartData* Jaw = GameInstance->FindBodyPart(EBodyPart::Jaw, Center);
	switch (CurrentShopAndBook)
	{
	case EShopAndBook::JawSurgery:
		if ((GameInstance->GetMoney() >= JawSurgeryPrice) && (Jaw->Strength <= 1.f - JawSurgeryIncrease))
		{
			GameInstance->SetMoney(-JawSurgeryPrice);
			GameInstance->AddStat(Jaw->Strength, JawSurgeryIncrease);
			GameInstance->SetPossesion(BodyStatus.bHasJawSurgery, true);

			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			
			PlaySound(BuySound);
		}
		break;
	case EShopAndBook::Steroids:
		if ((GameInstance->GetMoney() >= SteroidsPrice) && (!InventoryData.bOwnsSteroids))
		{
			UE_LOG(LogTemp, Warning, TEXT("Buy steroids"));
			constexpr float SteroidsEgoIncrease = 0.9f;
			constexpr float SteroidsSexIncrease = 0.9f;
			GameInstance->SetMoney(-SteroidsPrice);
			GameInstance->SetPossesion(InventoryData.bOwnsSteroids,true);

			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySteroids"));
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			
			PlaySound(BuySound);
		}
		break;
	case EShopAndBook::PreWorkout:
		if ((GameInstance->GetMoney() >= PreWorkoutPrice) && (!InventoryData.bOwnsPreWorkout))
		{
			GameInstance->SetMoney(-PreWorkoutPrice);
			GameInstance->SetPossesion(InventoryData.bOwnsPreWorkout, true);

			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			PlaySound(BuySound);
		}
		break;
	case EShopAndBook::ChadPoster:
		if ((GameInstance->GetMoney() < ChadPosterPrice)) return;
		DoesOwnPosterArray.Empty();
		DoesOwnPosterArray = GameInstance->GetOwnedChadPosters();
		if (BuyPoster(DoesOwnPosterArray, ChadPosterType_String))
		{
			GameInstance->SetMoney(-ChadPosterPrice);
			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			PlaySound(BuySound);
		}
		break;
	case EShopAndBook::WaifuPoster:
		if ((GameInstance->GetMoney() < WaifuPosterPrice)) return;
		DoesOwnPosterArray.Empty();
		DoesOwnPosterArray = GameInstance->GetOwnedWaifuPosters();
		if (BuyPoster(DoesOwnPosterArray, WaifuPosterType_String))
		{
			GameInstance->SetMoney(-WaifuPosterPrice);
			CompletedTodosCheckList.Empty();
			CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Bedroom.BuySomething"));
			PlaySound(BuySound);
		}
		break;
	default:
		CompletedTodosCheckList.Empty();
		break;
	}
	TodoManager->DelayForPlayerAchievements(CompletedTodosCheckList);

	Shelf->UpdateShelfItems();
	
}
bool ALaptop_OM::BuyPoster(TArray<bool>& InPosterArray, const FString& PosterType)
{
	for (size_t PosterIndex = 0; PosterIndex < InPosterArray.Num(); PosterIndex++)
	{
		if (!InPosterArray[PosterIndex])
		{
			GameInstance->SetPosterAsOwned(PosterIndex, PosterType);
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

