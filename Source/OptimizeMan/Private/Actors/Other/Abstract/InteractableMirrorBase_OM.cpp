// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Abstract/InteractableMirrorBase_OM.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Game/Persistent/GameInstance_OM.h"

AInteractableMirrorBase_OM::AInteractableMirrorBase_OM()
{
	MirrorGlassPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorGlassPlane"));
	MirrorGlassPlane->SetupAttachment(RootComponent);
	MirrorGlassPlane->SetCollisionProfileName(TEXT("Default"));

	MirrorSceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MirrorSceneCapture"));
	MirrorSceneCapture->SetupAttachment(RootComponent);
}

void AInteractableMirrorBase_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	if (bIsDarkMode)
	{
		MirrorSceneCapture->PostProcessSettings = DarkPostProcess;
	}
	else
	{
		MirrorSceneCapture->PostProcessSettings = LightPostProcess;
	}
}