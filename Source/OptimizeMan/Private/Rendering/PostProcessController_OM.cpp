// Copyright © 2025 4ozStudio. All rights reserved.


#include "Rendering/PostProcessController_OM.h"

#include "Chaos/Character/CharacterGroundConstraintContainer.h"
#include "Game/Persistent/GameInstance_OM.h"


APostProcessController_OM::APostProcessController_OM()
{
	PrimaryActorTick.bCanEverTick = false;
	GlobalPostProcessVolume = nullptr;
	DarkModeMaterial = nullptr;
	LightModeMaterial = nullptr;
	DarkModeMID = nullptr;
	LightModeMID = nullptr;
	GameInstance = nullptr;

}

void APostProcessController_OM::BeginPlay()
{
	Super::BeginPlay();

	if (!GlobalPostProcessVolume)
		return;

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


	GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	
	GameInstance->OnDarkModeToggled.AddDynamic(this, &APostProcessController_OM::SetDarkMode);

	CheckDarkMode();

}


void APostProcessController_OM::CheckDarkMode()
{
	SetDarkMode(GameInstance->GetDarkMode());
}

void APostProcessController_OM::SetDarkMode(bool bDarkMode) 
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

void APostProcessController_OM::StartChromaticEffects()
{
	int EndTime = FMath::RandRange(2, 20);
	ChromaticTickCounter = 0.f;
	FPostProcessSettings& Settings = GlobalPostProcessVolume->Settings;
	Settings.bOverride_SceneFringeIntensity = true;
	Settings.bOverride_ChromaticAberrationStartOffset = true;
	GetWorld()->GetTimerManager().ClearTimer(ChromaticTickHandle);
	GetWorld()->GetTimerManager().SetTimer(
		ChromaticTickHandle,
		[this, EndTime, &Settings]()
		{
			ChromaticEffectsTick(EndTime, Settings);
		},TickRate,true);
}

void APostProcessController_OM::ChromaticEffectsTick(const int EndTime, FPostProcessSettings& Settings)
{
	if (Settings.SceneFringeIntensity < MaxChromaticIntensity)
	{
		Settings.SceneFringeIntensity = FMath::FInterpConstantTo(
		Settings.SceneFringeIntensity, MaxChromaticIntensity, 0.065, 0.5);
	}
	if (bGoingUp)
	{
		if (Settings.ChromaticAberrationStartOffset >= MaxChromaticOffset) bGoingUp = false;
		Settings.ChromaticAberrationStartOffset = FMath::FInterpConstantTo(
	Settings.ChromaticAberrationStartOffset, MaxChromaticOffset, 0.065, 0.5);
	}
	else
	{
		if (Settings.ChromaticAberrationStartOffset <= MinChromaticOffset) bGoingUp = true;
		Settings.ChromaticAberrationStartOffset = FMath::FInterpConstantTo(
Settings.ChromaticAberrationStartOffset, MinChromaticOffset, 0.065, 0.5);
	}
	
	ChromaticTickCounter += TickRate;
	if (ChromaticTickCounter >= EndTime)
		GetWorld()->GetTimerManager().ClearTimer(ChromaticTickHandle);
}