// Copyright © 2025 4ozStudio. All rights reserved.


#include "Rendering/PostProcessController_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Kismet/GameplayStatics.h"


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

	InitializeEffects();

	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->OnPlayModeChange.AddDynamic(this, &APostProcessController_OM::ManageEffectsOnPlayMode);
		Player->OnTempEmotionsChanged.AddDynamic(this, &APostProcessController_OM::ManageEffectsOnTempEmotion);
	}

}

void APostProcessController_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (FPostProcessEffect& Effect : Effects)
	{
		GetWorld()->GetTimerManager().ClearTimer(Effect.TimerHandle);
	}
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Super::EndPlay(EndPlayReason);
}

void APostProcessController_OM::InitializeEffects()
{
	Effects.Empty();
	FPostProcessEffect FilmGrainIntensity;
	FilmGrainIntensity.Name = FName("FilmGrainIntensity");
	FilmGrainIntensity.Min = 0.f;
	FilmGrainIntensity.Max = 1.f;
	FilmGrainIntensity.bGoingUp = false;
	FilmGrainIntensity.OverrideSetter = [&](bool bEnable) {GlobalPostProcessVolume->Settings.bOverride_FilmGrainIntensity = bEnable;};
	FilmGrainIntensity.ValueGetter = [&]() { return GlobalPostProcessVolume->Settings.FilmGrainIntensity; };
	FilmGrainIntensity.ValueSetter = [&](float Value) { GlobalPostProcessVolume->Settings.FilmGrainIntensity = Value; };
	Effects.Add(FilmGrainIntensity);
	
	FPostProcessEffect FilmGrainTexelSize;
	FilmGrainTexelSize.Name = FName("FilmGrainTexelSize");
	FilmGrainTexelSize.Min = 0.f;
	FilmGrainTexelSize.Max = 4.f;
	FilmGrainTexelSize.bGoingUp = false;
	FilmGrainTexelSize.OverrideSetter = [&](bool bEnable){ GlobalPostProcessVolume->Settings.bOverride_FilmGrainTexelSize = bEnable; };
	FilmGrainTexelSize.ValueGetter = [&]() {return GlobalPostProcessVolume->Settings.FilmGrainTexelSize; };
	FilmGrainTexelSize.ValueSetter = [&](float Value) { GlobalPostProcessVolume->Settings.FilmGrainTexelSize = Value; };
	Effects.Add(FilmGrainTexelSize);

	FPostProcessEffect ChromaticIntensity;
	ChromaticIntensity.Name = FName("ChromaticIntensity");
	ChromaticIntensity.Min = 0.f;
	ChromaticIntensity.Max = 5.f;
	ChromaticIntensity.bGoingUp = false;
	ChromaticIntensity.OverrideSetter = [&](bool bEnable) { GlobalPostProcessVolume->Settings.bOverride_SceneFringeIntensity = bEnable; };
	ChromaticIntensity.ValueGetter = [&]() {return GlobalPostProcessVolume->Settings.SceneFringeIntensity; };
	ChromaticIntensity.ValueSetter = [&](float Value) { GlobalPostProcessVolume->Settings.SceneFringeIntensity = Value; };
	Effects.Add(ChromaticIntensity);

	FPostProcessEffect ChromaticOffset;
	ChromaticOffset.Name = FName("ChromaticOffset");
	ChromaticOffset.Min = 0.f;
	ChromaticOffset.Max = 1.f;
	ChromaticOffset.bGoingUp = false;
	ChromaticOffset.OverrideSetter = [&](bool bEnable) { GlobalPostProcessVolume->Settings.bOverride_ChromaticAberrationStartOffset = bEnable; };
	ChromaticOffset.ValueGetter = [&]() { return GlobalPostProcessVolume->Settings.ChromaticAberrationStartOffset; };
	ChromaticOffset.ValueSetter = [&](float Value) { GlobalPostProcessVolume->Settings.ChromaticAberrationStartOffset = Value; };
	Effects.Add(ChromaticOffset);

	FPostProcessEffect Vignette;
	Vignette.Name = FName("Vignette");
	Vignette.Min = 0.f;
	Vignette.Max = 1.f;
	Vignette.bGoingUp = false;
	Vignette.OverrideSetter = [&](bool bEnable) { GlobalPostProcessVolume->Settings.bOverride_VignetteIntensity = bEnable; };
	Vignette.ValueGetter = [&]() { return GlobalPostProcessVolume->Settings.VignetteIntensity; };
	Vignette.ValueSetter = [&](float Value) { GlobalPostProcessVolume->Settings.VignetteIntensity = Value; };
	Effects.Add(Vignette);
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

// Eventually can remove this function and use only temp emotions
void APostProcessController_OM::ManageEffectsOnPlayMode(EPlayModes CurrentPlayMode)
{
	switch (CurrentPlayMode)
	{
	case EPlayModes::SocialMode:
		{
			if (Player)
			{
				if (auto* ExerciseComp = Player->GetComponentByClass<UExercise_OM>())
				{
					if (ExerciseComp->GetFocus() < 0.7f)
					{
						StartChromaticEffects();
					}
				}
			}
			break;
		}
	case EPlayModes::WorkoutMode:
		{
			if (Player)
			{
				if (auto* ExerciseComp = Player->GetComponentByClass<UExercise_OM>())
				{
					if (ExerciseComp->GetEnergy() < 0.7f)
						StartFilmGrainEffects();
					if (ExerciseComp->GetEnergy() < 0.5f)
						StartChromaticEffects();
				}
			}
			break;
		}
	default:
		break;
	}
}

void APostProcessController_OM::ManageEffectsOnTempEmotion(ETemporaryEmotionalStates InState)
{
	if (InState == ETemporaryEmotionalStates::Anxious)
	{
		StartVignetteEffect(EEffectTickMode::WaveEffect, 4, 10);

	}
}

void APostProcessController_OM::StartEffect(const FName InEffectName, int MinTime, int MaxTime, EEffectTickMode InEffectTickMode)
{
	int EndTime = FMath::RandRange(MinTime, MaxTime);
	FPostProcessEffect& EffectToPlay = GetEffect(InEffectName);

	const FName InvalidName = FName("Invalid");
	if (EffectToPlay.Name == InvalidName)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Effect in StartEffect: %s"), *InEffectName.ToString());
		return;
	}
	EffectToPlay.OverrideSetter(true);

	EffectToPlay.bCurrentlyOn = true;

	EffectToPlay.TickCounter = 0.f;

	GetWorld()->GetTimerManager().ClearTimer(EffectToPlay.TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(EffectToPlay.TimerHandle, [this, &EffectToPlay, EndTime, InEffectTickMode]()
	{
		if (!EffectToPlay.bCurrentlyOn)
		{
			GetWorld()->GetTimerManager().ClearTimer(EffectToPlay.TimerHandle);
		}
		switch (InEffectTickMode)
		{
			case EEffectTickMode::None:
			{
				GetWorld()->GetTimerManager().ClearTimer(EffectToPlay.TimerHandle);
				break;
			}
			case EEffectTickMode::WaveEffect:
			{
				EffectToPlay.WaveEffectTick(EndTime, TickRate);
				break;
			}
			case EEffectTickMode::FadeIn:
			{
				EffectToPlay.FadeIn();
				break;
			}
			default:
			{
				GetWorld()->GetTimerManager().ClearTimer(EffectToPlay.TimerHandle);
				break;
			}
		}
		
	}, TickRate, true);
	
}

void APostProcessController_OM::StartFilmGrainEffects()
{
	StartEffect(FName("FilmGrainIntensity"), 5, 30, EEffectTickMode::WaveEffect);
	StartEffect(FName("FilmGrainTexelSize"), 5, 30, EEffectTickMode::WaveEffect);
}
void APostProcessController_OM::StartChromaticEffects()
{
	StartEffect(FName("ChromaticIntensity"), 5, 30, EEffectTickMode::WaveEffect);
	StartEffect(FName("ChromaticOffset"), 5, 30, EEffectTickMode::WaveEffect);
}

void APostProcessController_OM::StartVignetteEffect(EEffectTickMode EffectType, int MinTime, int MaxTime)
{
	StartEffect(FName("Vignette"), MinTime, MaxTime, EffectType);
}


FPostProcessEffect& APostProcessController_OM::GetEffect(FName InName)
{
	FPostProcessEffect DefEffect;
	DefEffect.Name = FName("Invalid");
	if (Effects.Num() <= 0) return DefEffect;
	for (FPostProcessEffect& Effect : Effects)
	{
		if (Effect.Name == InName)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Effect %s"), *Effect.Name.ToString());
			return Effect;
		}
	}
	return DefEffect;
}
