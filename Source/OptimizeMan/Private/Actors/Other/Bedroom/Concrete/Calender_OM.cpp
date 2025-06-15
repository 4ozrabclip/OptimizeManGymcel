// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Other/Bedroom/Concrete/Calender_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/PointLightComponent.h"
#include "Components/RectLightComponent.h"
#include "Game/Persistent/GameInstance_OM.h"

ACalender_OM::ACalender_OM()
{
	JanuaryMaterial = nullptr;
	FebruaryMaterial = nullptr;
	MarchMaterial = nullptr;
	AprilMaterial = nullptr;
	MayMaterial = nullptr;
	JuneMaterial = nullptr;
	JulyMaterial = nullptr;
	AugustMaterial = nullptr;
	SeptemberMaterial = nullptr;
	OctoberMaterial = nullptr;
	NovemberMaterial = nullptr;
	DecemberMaterial = nullptr;
	
	Light = CreateDefaultSubobject<URectLightComponent>(TEXT("Light"));
	Light->SetupAttachment(RootComponent);
	Light->SetCastShadows(false);
	Light->SetBarnDoorAngle(0.f);
	Light->SetBarnDoorLength(20.f);
	Light->SetIntensityUnits(ELightUnits::Candelas);
	Light->SetIntensity(1.f);
	Light->SetVisibility(true);
	Light->SetLightColor(FLinearColor::White);
	
	AuraLight->SetActive(false);
	AuraLight->SetVisibility(false);
}

void ACalender_OM::BeginPlay()
{
	Super::BeginPlay();
	AuraLight->SetActive(false);
	AuraLight->SetVisibility(false);
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	}
	SetCalenderImage();
}
void ACalender_OM::CheckAndSetDarkMode()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	if (GameInstance->GetDarkMode())
	{
		Light->SetIntensity(0.2f);
	}
	else
	{
		Light->SetIntensity(1.f);
	}
	SetCalenderImage();
}
void ACalender_OM::SetCalenderImage()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}

	const bool bIsDarkMode = GameInstance->GetDarkMode();

	switch (GameInstance->GetCurrentMonth())
	{
		case EMonth::January:
		    if (!JanuaryMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, JanuaryMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, JanuaryMaterial);
		    break;
		case EMonth::February:
		    if (!FebruaryMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, FebruaryMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, FebruaryMaterial);
		    break;
		case EMonth::March:
		    if (!MarchMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, MarchMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, MarchMaterial);
		    break;
		case EMonth::April:
		    if (!AprilMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, AprilMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, AprilMaterial);
		    break;
		case EMonth::May:
		    if (!MayMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, MayMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, MayMaterial);
		    break;
		case EMonth::June:
		    if (!JuneMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, JuneMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, JuneMaterial);
		    break;
		case EMonth::July:
		    if (!JulyMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, JulyMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, JulyMaterial);
		    break;
		case EMonth::August:
		    if (!AugustMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, AugustMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, AugustMaterial);
		    break;
		case EMonth::September:
		    if (!SeptemberMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, SeptemberMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, SeptemberMaterial);
		    break;
		case EMonth::October:
		    if (!OctoberMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, OctoberMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, OctoberMaterial);
		    break;
		case EMonth::November:
		    if (!NovemberMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, NovemberMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, NovemberMaterial);
		    break;
		case EMonth::December:
		    if (!DecemberMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, DecemberMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, DecemberMaterial);
		    break;
		default:
		    if (!JanuaryMaterial) return;
		    if (bIsDarkMode)
		        ItemMesh->SetMaterial(0, JanuaryMaterialDarkMode);
		    else
		        ItemMesh->SetMaterial(0, JanuaryMaterial);
		    break;
	}
}
void ACalender_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	Player->TogglePlayMode(EPlayModes::CalenderMode, Player->bInteractableOpen, this);
	//Player->SetCurrentPlayMode(EPlayModes::CalenderMode, this);
}
