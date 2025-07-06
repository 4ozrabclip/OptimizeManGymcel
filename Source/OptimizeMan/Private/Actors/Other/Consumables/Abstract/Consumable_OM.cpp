// Copyright © 2025 4ozStudio. All rights reserved.



#include "Actors/Other/Consumables/Abstract/Consumable_OM.h"

#include "GameplayEffect.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/BoxComponent.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Components/Management/AbilitySystemComponent_OM.h"
#include "Game/GameInstance_OM.h"

AConsumable_OM::AConsumable_OM()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAudioType(EAudioTypes::SfxAudio);
	AudioComponent->bAutoActivate = true;


	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemMesh->SetSimulatePhysics(false);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	HitBox->SetupAttachment(RootComponent);
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	InteractableInterfaceProperties.bIsInteractable = false;
	
}

void AConsumable_OM::BeginPlay()
{
	Super::BeginPlay();

	ItemMesh->SetSimulatePhysics(true);

	AbSysComp = Player->FindComponentByClass<UAbilitySystemComponent_OM>();
	if (!AbSysComp) return;

	AudioComponent->OnAudioFinished.Clear();
	AudioComponent->OnAudioFinished.AddDynamic(this, &AConsumable_OM::DestroyConsumable);

	GetWorld()->GetTimerManager().ClearTimer(TimerTilInteractableHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerTilInteractableHandle,[this]()
	{
		InteractableInterfaceProperties.bIsInteractable = true;
	}, 2.f, false);
	
}

void AConsumable_OM::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	//if (!ConsumableManager)
	//	ConsumableManager = Cast<UConsumablesSubsystem>(GameInstance->GetSubsystem<UConsumablesSubsystem>());
	
	//if (ConsumableManager)
	//	ConsumableManager->AddConsumable(ConsumableType);

	if (EffectToApply)
	{
		FGameplayEffectContextHandle Context = AbSysComp->MakeEffectContext();
		Context.AddSourceObject(this);

		const FGameplayEffectSpecHandle SpecHandle = AbSysComp->MakeOutgoingSpec(EffectToApply, 1.f, Context);
		if (SpecHandle.IsValid())
		{
			AbSysComp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
	
	PlayConsumeSound();
}
void AConsumable_OM::PlayConsumeSound()
{
	if (!AudioComponent) return;
	if (ConsumeSounds.Num() <= 0) return;

	const int RandIndex = FMath::RandRange(0, ConsumeSounds.Num() - 1);

	AudioComponent->SetSound(ConsumeSounds[RandIndex]);

	AudioComponent->Play();
	
}