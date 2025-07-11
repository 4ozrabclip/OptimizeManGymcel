// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Other/Concrete/PosterComponent_OM.h"

#include "Components/RectLightComponent.h"
#include "Game/Persistent/GameInstance_OM.h"
/*
ChadPoster1Light = CreateDefaultSubobject<URectLightComponent>(TEXT("ChadPoster1Light"));
ChadPoster1Light->SetupAttachment(ChadPoster1);
ChadPoster1Light->SetCastShadows(false);
ChadPoster1Light->SetBarnDoorAngle(0.f);
ChadPoster1Light->SetBarnDoorLength(20.f);
ChadPoster1Light->SetIntensityUnits(ELightUnits::Candelas);
ChadPoster1Light->SetIntensity(4.f);*/


UPosterComponent_OM::UPosterComponent_OM()
{
	Light = nullptr;
	DarkModeImage = nullptr;
	LightModeImage = nullptr;
	GameInstance = nullptr;

}
void UPosterComponent_OM::OnRegister()
{
	Super::OnRegister();

	if (!Light)
	{
		FName LightName = *FString::Printf(TEXT("Light_%p"), this);
		Light = NewObject<URectLightComponent>(this, LightName);
		Light->SetupAttachment(this);
		Light->RegisterComponent();
		Light->SetUsingAbsoluteLocation(false);
		Light->SetUsingAbsoluteRotation(false);
		Light->SetCastShadows(true);
		Light->SetBarnDoorAngle(0.f);
		Light->SetBarnDoorLength(20.f);
		Light->SetIntensityUnits(ELightUnits::Candelas);
		Light->SetIntensity(4.f);
	}
}



void UPosterComponent_OM::BeginPlay()
{
	Super::BeginPlay();

	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());


	GameInstance->OnDarkModeToggled.AddDynamic(this, &UPosterComponent_OM::DarkModeToggle);

	DarkModeToggle(GameInstance->GetDarkMode());
}
void UPosterComponent_OM::DarkModeToggle(const bool bIsDarkMode)
{
	if (bIsDarkMode)
	{
		SetMaterial(0, DarkModeImage);
		Light->SetIntensity(0.2f);
	}
	else
	{
		SetMaterial(1, LightModeImage);
		Light->SetIntensity(5.f);
	}
}