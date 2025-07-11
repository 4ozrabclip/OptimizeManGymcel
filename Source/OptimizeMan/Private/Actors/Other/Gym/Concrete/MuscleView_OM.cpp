// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/MuscleView_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

AMuscleView_OM::AMuscleView_OM()
{
	AuraLight->SetIntensity(1.f);
	AuraLight->SetAttenuationRadius(30.f);
	StepBackReach = 300.f;
}

void AMuscleView_OM::BeginPlay()
{
	Super::BeginPlay();
}

void AMuscleView_OM::Interact_Implementation()
{
	Super::Interact_Implementation();
	if (!Player)
	{
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	}
	PlayerFacingMirrorLocation = FVector(GetActorLocation().X, GetActorLocation().Y - StepBackReach, Player->GetActorLocation().Z);

	Player->SetActorLocation(PlayerFacingMirrorLocation);
	PlayerController->SetControlRotation(GetActorRotation().GetInverse());

	Player->TogglePlayMode(EPlayModes::MuscleViewMode, Player->bInteractableOpen, this);
}
