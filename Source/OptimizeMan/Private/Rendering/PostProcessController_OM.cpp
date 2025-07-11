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

void APostProcessController_OM::StartFilmGrainEffect()
{
	if (bFilmGrainOn) return;

	int EndTime = FMath::RandRange(10, 40);

	GlobalPostProcessVolume->Settings.bOverride_FilmGrainIntensity;
	GlobalPostProcessVolume->Settings.bOverride_FilmGrainTexelSize;

	FilmGrainTickCounter = 0.f;

	GetWorld()->GetTimerManager().ClearTimer(FilmGrainEffectHandle);
	GetWorld()->GetTimerManager().SetTimer(
		FilmGrainEffectHandle,
		[this, EndTime]()
		{
			FilmGrainEffectTick(EndTime);
		}, TickRate, true);
}
void APostProcessController_OM::FilmGrainEffectTick(const int EndTime)
{
	constexpr float TexelSizeMax = 4.f;
	if (GlobalPostProcessVolume->Settings.FilmGrainTexelSize < TexelSizeMax)
	{
		
		GlobalPostProcessVolume->Settings.FilmGrainTexelSize = FMath::FInterpConstantTo()
	}
	FilmGrainTickCounter += TickRate;
}
void APostProcessController_OM::StartVignetteEffect()
{
	if (bVignetteOn) return;
	FPostProcessSettings& Settings = GlobalPostProcessVolume->Settings;
	Settings.bOverride_VignetteIntensity = true;

	GetWorld()->GetTimerManager().ClearTimer(VignetteTickHandle);
	GetWorld()->GetTimerManager().SetTimer(
		VignetteTickHandle,
		[this, &Settings]()
		{
			if (!bVignetteOn) bVignetteOn = true;
			VignetteEffectTick(Settings);
		}, TickRate, true);
}

void APostProcessController_OM::RemoveVignetteEffect()
{
	if (!bVignetteOn) return;
	FPostProcessSettings& Settings = GlobalPostProcessVolume->Settings;
	Settings.bOverride_VignetteIntensity = true;
	GetWorld()->GetTimerManager().ClearTimer(VignetteTickHandle);
	GetWorld()->GetTimerManager().SetTimer(
	VignetteTickHandle,
	[this, &Settings]()
	{
		if (bVignetteOn) bVignetteOn = false;
		RemoveVignetteEffectTick(Settings);
	}, TickRate, true);
}

void APostProcessController_OM::RemoveVignetteEffectTick(FPostProcessSettings& Settings)
{
	if (FMath::IsNearlyEqual(Settings.VignetteIntensity, 0.f))
	{
		GetWorld()->GetTimerManager().ClearTimer(VignetteTickHandle);
	}
	else
	{
		Settings.VignetteIntensity = FMath::FInterpConstantTo(
			Settings.VignetteIntensity,0.f,0.065f,0.5);
	}
}

void APostProcessController_OM::VignetteEffectTick(FPostProcessSettings& Settings)
{
	if (FMath::IsNearlyEqual(Settings.VignetteIntensity, 1.f))
	{
		GetWorld()->GetTimerManager().ClearTimer(VignetteTickHandle);
	}
	else
	{
		Settings.VignetteIntensity = FMath::FInterpConstantTo(
			Settings.VignetteIntensity,1.f,0.065f,0.5);
	}
}

void APostProcessController_OM::StartChromaticEffects()
{
	if (bChromaticOn) return;
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
			if (!bChromaticOn) bChromaticOn = true;
			ChromaticEffectsTick(EndTime, Settings);
		},TickRate,true);
}
void APostProcessController_OM::RemoveChromaticEffects()
{
	if (bChromaticOn) bChromaticOn = false;
	FPostProcessSettings& Settings = GlobalPostProcessVolume->Settings;
	Settings.bOverride_SceneFringeIntensity = true;
	Settings.bOverride_ChromaticAberrationStartOffset = true;
	GetWorld()->GetTimerManager().ClearTimer(ChromaticTickHandle);
	GetWorld()->GetTimerManager().SetTimer(
		ChromaticTickHandle,
		[this, &Settings]()
		{
			RemoveChromaticEffectsTick(Settings);
		}, TickRate, true);
}
void APostProcessController_OM::RemoveChromaticEffectsTick(FPostProcessSettings& Settings)
{
	if (FMath::IsNearlyZero(Settings.SceneFringeIntensity))
	{
		GetWorld()->GetTimerManager().ClearTimer(ChromaticTickHandle);
	}
	else
	{
		Settings.SceneFringeIntensity = FMath::FInterpConstantTo(
			Settings.SceneFringeIntensity,0.f,0.065,0.5);
	}

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
	{
		bChromaticOn = false;
		GetWorld()->GetTimerManager().ClearTimer(ChromaticTickHandle);
	}

}