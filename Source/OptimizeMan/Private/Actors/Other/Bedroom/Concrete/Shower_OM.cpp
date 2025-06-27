// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Bedroom/Concrete/Shower_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/WidgetComponent.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/Structs/AudioTypes.h"
#include "Widgets/Home/Concrete/ShowerWidget_OM.h"

AShower_OM::AShower_OM()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComp->SetupAttachment(RootComponent);
	WidgetComp->SetVisibility(false);

	AudioComp = CreateDefaultSubobject<UGameAudio_OM>(TEXT("AudioComponent"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->SetAudioType(EAudioTypes::SfxAudio);
}

void AShower_OM::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) return;

	Player = Cast<APlayerCharacter_OM>(PlayerController->GetPawn());
	if (!Player) return;
	
	if (UShowerWidget_OM* Widg = Cast<UShowerWidget_OM>(WidgetComp->GetWidget()))
		Widg->InitShower(this);
	
}

void AShower_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	PlayerController->ToggleInteractWidgetFromViewport(true);
	WidgetComp->SetVisibility(true);
	InteractableInterfaceProperties.bIsInteractable = false;
	Player->SetToUIMode(true, true);
	
}

void AShower_OM::TakeShower(bool bCold)
{
	//Play Shower Sequence

	/*
	 * Probably want to add something here that stops input during shower sequence.  
	 * --- Will do that after i get the sequence ready
	 */
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	if (!GameInstance) return;

	auto* TodoMan = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoMan) return;
	
	if (bCold)
	{
		TodoMan->CompleteTodo(FGameplayTag::RequestGameplayTag("Todos.Bedroom.TakeColdShower"));

		const int RandIndex = FMath::RandRange(0, ColdShowerSounds.Num() - 1);
		if (ColdShowerSounds.IsValidIndex(RandIndex))
		{
			AudioComp->SetSound(ColdShowerSounds[RandIndex]);
			AudioComp->Play();
		}
	}
	else
	{
		const int RandIndex = FMath::RandRange(0, HotShowerSounds.Num() - 1);
		if (HotShowerSounds.IsValidIndex(RandIndex))
		{
			AudioComp->SetSound(HotShowerSounds[RandIndex]);
			AudioComp->Play();
		}
	}
}

void AShower_OM::CloseWidget()
{
	WidgetComp->SetVisibility(false);
	InteractableInterfaceProperties.bIsInteractable = true;
	Player->SetToUIMode(false);
	PlayerController->ToggleInteractWidgetFromViewport(false);
	SetActorTickEnabled(false);
}
