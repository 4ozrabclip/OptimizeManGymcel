// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Items/InteractableMirrorBase_OM.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Utils/GameInstance_OM.h"

AInteractableMirrorBase_OM::AInteractableMirrorBase_OM()
{
	MirrorGlassPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorGlassPlane"));
	MirrorGlassPlane->SetupAttachment(RootComponent);
	MirrorGlassPlane->SetCollisionProfileName(TEXT("Default"));

	MirrorSceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MirrorSceneCapture"));
	MirrorSceneCapture->SetupAttachment(RootComponent);
}

void AInteractableMirrorBase_OM::CheckAndSetDarkMode()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	if (GameInstance->GetDarkMode())
	{
		MirrorSceneCapture->PostProcessSettings = DarkPostProcess;
	}
	else
	{
		MirrorSceneCapture->PostProcessSettings = LightPostProcess;
	}
}
