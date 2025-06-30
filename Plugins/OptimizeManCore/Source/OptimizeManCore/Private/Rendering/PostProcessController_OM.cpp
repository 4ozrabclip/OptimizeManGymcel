// Copyright © 2025 4ozStudio. All rights reserved.


#include "Rendering/PostProcessController_OM.h"

#include "Interfaces/PersistentStateProvider_OM.h"


APostProcessControllerBase_OM::APostProcessControllerBase_OM()
{
	PrimaryActorTick.bCanEverTick = false;
	GlobalPostProcessVolume = nullptr;
	DarkModeMaterial = nullptr;
	LightModeMaterial = nullptr;
	DarkModeMID = nullptr;
	LightModeMID = nullptr;
}

void APostProcessControllerBase_OM::BeginPlay()
{
	Super::BeginPlay();


	if (!DarkModeMID && DarkModeMaterial)
	{
		DarkModeMID = UMaterialInstanceDynamic::Create(DarkModeMaterial, this);
	}
	if (!LightModeMID && LightModeMaterial)
	{
		LightModeMID = UMaterialInstanceDynamic::Create(LightModeMaterial, this);
	}
	GlobalPostProcessVolume->Settings.WeightedBlendables.Array.Empty();

	
	if (DarkModeMID)
	{
		GlobalPostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(0.f, DarkModeMID));
	}
	if (LightModeMID)
	{
		GlobalPostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(0.f, LightModeMID));
	}

	if (UGameInstance* GI = GetGameInstance())
	{
		if (GI->GetClass()->ImplementsInterface(UPersistentStateProvider_OM::StaticClass()))
		{
			Persistence = Cast<IPersistentStateProvider_OM>(GI);

			SetDarkMode(Persistence->GetIsDarkMode());
		}
	}

	//GameInstance->OnDarkModeToggled.Clear();
	//GameInstance->OnDarkModeToggled.AddDynamic(this, &APostProcessController_OM::CheckDarkMode);
}


void APostProcessControllerBase_OM::CheckDarkMode()
{
	SetDarkMode(Persistence->GetIsDarkMode());
}

void APostProcessControllerBase_OM::SetDarkMode(bool bDarkMode) const
{
	for (FWeightedBlendable& Blendable : GlobalPostProcessVolume->Settings.WeightedBlendables.Array)
	{
		if (Blendable.Object == DarkModeMID)
		{
			Blendable.Weight = bDarkMode ? 1.f : 0.f;
		}
		else if (Blendable.Object == LightModeMID)
		{
			Blendable.Weight = bDarkMode ? 0.f : 1.f;
		}
	}
}
