// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Poster_OM.h"

#include "Actors/Items/Laptop_OM.h"
#include "Actors/Items/Components/PosterComponent_OM.h"
#include "Components/RectLightComponent.h"
#include "Utils/GameInstance_OM.h"

// Sets default values
APoster_OM::APoster_OM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ChadPoster1 = CreateDefaultSubobject<UPosterComponent_OM>(TEXT("ChadPoster1"));
	ChadPoster1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ChadPoster1->SetupAttachment(RootComponent);
	ChadPoster2 = CreateDefaultSubobject<UPosterComponent_OM>(TEXT("ChadPoster2"));
	ChadPoster2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ChadPoster2->SetupAttachment(RootComponent);
	ChadPoster3 = CreateDefaultSubobject<UPosterComponent_OM>(TEXT("ChadPoster3"));
	ChadPoster3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ChadPoster3->SetupAttachment(RootComponent);

	WaifuPoster1 = CreateDefaultSubobject<UPosterComponent_OM>(TEXT("WaifuPoster1"));
	WaifuPoster1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WaifuPoster1->SetupAttachment(RootComponent);
	WaifuPoster2 = CreateDefaultSubobject<UPosterComponent_OM>(TEXT("WaifuPoster2"));
	WaifuPoster2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WaifuPoster2->SetupAttachment(RootComponent);
	WaifuPoster3 = CreateDefaultSubobject<UPosterComponent_OM>(TEXT("WaifuPoster3"));
	WaifuPoster3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WaifuPoster3->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void APoster_OM::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Game instance null in poster"));
		return;
	}
	CheckOwnedPosters();
}

void APoster_OM::CheckOwnedPosters()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());


	OwnedChadPosters.Empty();
	
	OwnedChadPosters = GameInstance->GetOwnedChadPosters();

	OwnedWaifuPosters.Empty();
	OwnedWaifuPosters = GameInstance->GetOwnedWaifuPosters();

	if (OwnedChadPosters.Num() != NumberOfChadPosters)
	{
		UE_LOG(LogTemp, Error, TEXT("ChadPosters array size mismatch"));
		return;
	}
	if (OwnedWaifuPosters.Num() != NumberOfWaifuPosters)
	{
		UE_LOG(LogTemp, Error, TEXT("WaifuPosters Array Size MisMatch"))
		return;
	}

	CheckAndSetDarkMode();
	
	if (OwnedChadPosters.IsValidIndex(0))
		UE_LOG(LogTemp, Error, TEXT("Valid Index For ChadPoster [ 0 ]"));
		SetVisibilityOfPoster(ChadPoster1, OwnedChadPosters[0]);
	if (OwnedChadPosters.IsValidIndex(1))
		SetVisibilityOfPoster(ChadPoster2, OwnedChadPosters[1]);
	if (OwnedChadPosters.IsValidIndex(2))
		SetVisibilityOfPoster(ChadPoster3, OwnedChadPosters[2]);

	
	if (OwnedWaifuPosters.IsValidIndex(0))
		SetVisibilityOfPoster(WaifuPoster1, OwnedWaifuPosters[0]);
	if (OwnedWaifuPosters.IsValidIndex(1))
		SetVisibilityOfPoster(WaifuPoster2, OwnedWaifuPosters[1]);
	if (OwnedWaifuPosters.IsValidIndex(2))
		SetVisibilityOfPoster(WaifuPoster3, OwnedWaifuPosters[2]);
	
}

void APoster_OM::SetVisibilityOfPoster(UPosterComponent_OM* InPoster, const bool InIsOwned)
{
	if (!InPoster)
	{
		UE_LOG(LogTemp, Error, TEXT("InPoster or Inlight is null"));
	}
	if (InIsOwned)
	{
		UE_LOG(LogTemp, Error, TEXT("Is Owned"));
		
		InPoster->SetVisibility(true, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Is NotOwned"));
		InPoster->SetVisibility(false, true);
	}
}

void APoster_OM::CheckAndSetDarkMode()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	if (OwnedChadPosters.Num() != NumberOfChadPosters)
	{
		UE_LOG(LogTemp, Error, TEXT("ChadPosters array size mismatch"));
		return;
	}
	if (OwnedWaifuPosters.Num() != NumberOfWaifuPosters)
	{
		UE_LOG(LogTemp, Error, TEXT("WaifuPosters Array Size MisMatch"))
		return;
	}
	if (OwnedChadPosters.IsValidIndex(0) && OwnedChadPosters[0])
		ChadPoster1->CheckAndSetDarkMode();
	if (OwnedChadPosters.IsValidIndex(1) && OwnedChadPosters[1])
		ChadPoster2->CheckAndSetDarkMode();
	if (OwnedChadPosters.IsValidIndex(2) & OwnedChadPosters[2])
		ChadPoster3->CheckAndSetDarkMode();
	if (OwnedWaifuPosters.IsValidIndex(0) && OwnedWaifuPosters[0])
		WaifuPoster1->CheckAndSetDarkMode();
	if (OwnedWaifuPosters.IsValidIndex(1) && OwnedWaifuPosters[1])
		WaifuPoster2->CheckAndSetDarkMode();
	if (OwnedWaifuPosters.IsValidIndex(2) && OwnedWaifuPosters[2])
		WaifuPoster3->CheckAndSetDarkMode();
}
