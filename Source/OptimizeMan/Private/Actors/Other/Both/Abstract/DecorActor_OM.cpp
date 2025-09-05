// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Both/Abstract/DecorActor_OM.h"

#include "Game/Persistent/GameInstance_OM.h"

ADecorActor_OM::ADecorActor_OM()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Mesh"));
	MainMesh->SetupAttachment(RootComponent);
}

void ADecorActor_OM::BeginPlay()
{
	Super::BeginPlay();

	if (auto* GI = Cast<UGameInstance_OM>(GetGameInstance()))
	{
		if (!GI->OnDarkModeToggled.IsAlreadyBound(this, &ADecorActor_OM::OnDarkModeToggled))
			GI->OnDarkModeToggled.AddDynamic(this, &ADecorActor_OM::OnDarkModeToggled);

		OnDarkModeToggled(GI->GetDarkMode());
	}
	
}

void ADecorActor_OM::OnDarkModeToggled(bool bIsDarkMode)
{
	MainMesh->SetMaterial(0, bIsDarkMode ? DarkModeMat : LightModeMat);
}

