// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"

#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "Actors/Other/Gym/Concrete/GymSpeaker_OM.h"
#include "Components/AudioComponent.h"
#include "Components/Character/Concrete/NPCBodyDeformationsComponent_OM.h"
#include "AI/Controllers/NPC_AIController_OM.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utils/Structs/AudioTypes.h"
#include "NiagaraFunctionLibrary.h"

ANpcBase_OM::ANpcBase_OM()
{
	PrimaryActorTick.bCanEverTick = true;
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	CurrentState = ENpcState::Idle;
	CurrentLookState = ENpcLookStates::Idle;
	CurrentMood = ENpcMood::Neutral;
	CurrentExerciseType = EExerciseType::None;
	bCanInteract = true;
	bIsInDialogue = false;
	
	AuraLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AuraLight"));
	AuraLight->SetupAttachment(RootComponent);
	AuraLight->SetVisibility(true);
	AuraLight->SetCastShadows(false);
	AuraLight->SetAttenuationRadius(100.f);
	AuraLight->SetIntensityUnits(ELightUnits::Candelas);
	AuraLight->SetIntensity(6.f);

	DeformationComponent = CreateDefaultSubobject<UNPCBodyDeformationsComponent_OM>(TEXT("DeformationComponent"));
	DeformationComponent->SetAutoActivate(true);

	TalkingAudioComponent = CreateDefaultSubobject<UGameAudio_OM>(TEXT("TalkingAudioComponent"));
	TalkingAudioComponent->SetupAttachment(RootComponent);
	TalkingAudioComponent->SetAudioType(EAudioTypes::VoiceAudio);
	MaxPlayerLookAtRange = 1600.f;

	ParticleSpawnLoc = CreateDefaultSubobject<USceneComponent>(TEXT("ParticleSpawnLoc"));
	ParticleSpawnLoc->SetupAttachment(RootComponent);

	bHasMogFace = false;

	WalkSpeed = 100.f;
}

void ANpcBase_OM::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);

	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found in npc class beginplay"));
		return;
	}


	AnimInstance = Cast<UNpcBaseAnimInstance_OM>(GetMesh()->GetAnimInstance());
	if (AnimInstance.IsValid())
	{
		AnimInstance->SetPlayer(Player);
	}
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("player controller not found in npc beginplay"))
		return;
	}
	GameInstance = Cast<UGameInstance_OM>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("game instance not found in npc beginplay"))
		return;
	}
	
	GameInstance->OnDarkModeToggled.AddDynamic(this, &ANpcBase_OM::DarkModeToggle);

	DarkModeToggle(GameInstance->GetDarkMode());
	

	InteractableInterfaceProperties.InteractableText = InteractableText;
	InteractableInterfaceProperties.InteractableWidget = InteractableWidget;
}

void ANpcBase_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (GameInstance)
	{
		GameInstance->OnDarkModeToggled.RemoveDynamic(this, &ANpcBase_OM::DarkModeToggle);
	}
	if (TalkingAudioComponent && TalkingAudioComponent->IsPlaying())
	{
		TalkingAudioComponent->Stop();
	}
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
	


}


void ANpcBase_OM::Interact_Implementation()
{
	if (!bCanInteract) return;
	
	if (bIsInDialogue) return;
	
	
	StartDialogue();
	
}
void ANpcBase_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ToggleNpcLookStates();

	if (!Player) return;
	if (bIsInDialogue)
	{

		DistanceFromPlayerVector = Player->GetActorLocation() - GetActorLocation();
		if (GymSpeaker && GetFriendshipLevel() < -0.8 && CurrentMusicPitch > -2.f)
		{
			CurrentMusicPitch -= DeltaTime * 0.2f;
			CurrentMusicPitch = FMath::Clamp(CurrentMusicPitch, -1.f, 1.f);
			GymSpeaker->ChangePitch(CurrentMusicPitch);
		}
	}
}

void ANpcBase_OM::ToggleNpcLookStates()
{
	ENpcLookStates NewState = ENpcLookStates::LookingAtPlayer;
	if (!Player)
	{
		CurrentLookState = ENpcLookStates::Idle;
		return;
	}
	DistanceFromPlayerValue = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	
	
	if (!Player || DistanceFromPlayerValue > MaxPlayerLookAtRange)
	{
		NewState = ENpcLookStates::Idle;
	}
	else if (CurrentState == ENpcState::WorkingOut)
	{
		if (GetCharacterMovement()->GetGroundMovementMode() != EMovementMode::MOVE_None)
		{
			NewState = ENpcLookStates::LookingAtItem;
		}
	}
	else if (CurrentState == ENpcState::TalkingWithNpc && CurrentInteractedNpc)
	{
		NewState = ENpcLookStates::LookingAtNpc;
	}
	else if (GetFriendshipLevel() < -0.6f && GetFriendshipLevel() > -1.f)
	{
		NewState = ENpcLookStates::IgnoringPlayer;
	}
	if (NewState != CurrentLookState)
		CurrentLookState = NewState;
	
}

FVector ANpcBase_OM::LookAtLocation(const float DeltaTime)
{
	if (!Player || !Player->GetMesh()) 
	{
		return GetActorLocation() + DefaultLookAtOffset;
	}

	FVector PlayersHeadLocation = Player->GetMesh()->GetSocketLocation("Head");
	
	FVector TargetLookAtLocation;

	switch (CurrentLookState)
	{
		case ENpcLookStates::Idle:
			TargetLookAtLocation = GetActorLocation() + DefaultLookAtOffset;
			break;

		case ENpcLookStates::LookingAtPlayer:
			TargetLookAtLocation = PlayersHeadLocation;
			break;

		case ENpcLookStates::IgnoringPlayer:
		{
			FVector AwayDirection = GetActorLocation() - PlayersHeadLocation;
			AwayDirection.Normalize();
			TargetLookAtLocation = GetActorLocation() + (AwayDirection * 200.0f);
			break;
		}
		case ENpcLookStates::LookingAtItem:
			if (CurrentInteractedItem)
				TargetLookAtLocation = CurrentInteractedItem->GetActorLocation();
			break;
		case ENpcLookStates::LookingAtNpc:
			if (CurrentInteractedNpc)
				TargetLookAtLocation = CurrentInteractedNpc->GetActorLocation();
			break;
		default:
			TargetLookAtLocation = GetActorLocation() + DefaultLookAtOffset;
			break;
	}
	
	float InterpSpeed = GetFriendshipLevel() <= -0.8f ? 2.f : 10.f;

	
	SmoothedLookAtLocation = FMath::VInterpTo(SmoothedLookAtLocation, TargetLookAtLocation, DeltaTime, InterpSpeed);

	return SmoothedLookAtLocation;
}

void ANpcBase_OM::SpawnParticles(const FName& InName)
{
	if (UNiagaraSystem* ParticleToSpawn = GetParticleSystem(InName))
	{
		constexpr float SpawnOffset = 20.f;
		const FVector SpawnLocation = ParticleSpawnLoc->GetComponentLocation();

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ParticleToSpawn, SpawnLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find particles to spawn in Particles array on: %s "), *GetName());
	}
}

void ANpcBase_OM::SpawnParticlesOnMood()
{
	if (UNiagaraSystem* ParticleToSpawn = GetParticleSystem(CurrentMood))
	{
		constexpr float SpawnOffset = 20.f;
		const FVector SpawnLocation = ParticleSpawnLoc->GetComponentLocation();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ParticleToSpawn, SpawnLocation);
		UE_LOG(LogTemp, Display, TEXT("Spawning Particles on mood"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find particles to spawn in Particles array on: %s "), *GetName());
	}
}
UNiagaraSystem* ANpcBase_OM::GetParticleSystem(const ENpcMood& InMood)
{
	if (Particles.Num() == 0) return nullptr;
	
	FName PName;
	switch (InMood)
	{
	case ENpcMood::Angry: PName = FName("Angry"); break;
	case ENpcMood::Disgusted: PName = FName("Disgusted"); break;
	case ENpcMood::Happy: PName = FName("Happy"); break;
	case ENpcMood::Randy: PName = FName("Randy"); break;
	case ENpcMood::Uncomfortable: PName = FName("Uncomfortable"); break;
	default: return nullptr;
	}

	for (size_t Index = 0; Index < Particles.Num(); ++Index)
	{
		if (Particles[Index].Name == PName && Particles[Index].ParticleSystem != nullptr) return Particles[Index].ParticleSystem;
	}

	return nullptr;
}

UNiagaraSystem* ANpcBase_OM::GetParticleSystem(const FName& InName)
{
	if (Particles.Num() == 0) return nullptr;

	for (size_t Index = 0; Index < Particles.Num(); ++Index)
	{
		if (Particles[Index].Name == InName && Particles[Index].ParticleSystem != nullptr) return Particles[Index].ParticleSystem;
	}

	return nullptr;
}

ENpcRelationshipState ANpcBase_OM::GetCurrentRelationshipState()
{
	if (!PlayerRelationship.bHasMetPlayer)
		return ENpcRelationshipState::Neutral;
	
	PlayerRelationship.UpdateRelationshipState();

	return PlayerRelationship.RelationshipState;
}

void ANpcBase_OM::StartDialogue()
{
	if (!bIsInDialogue)
	{
		bIsInDialogue = true;
		SetCurrentState(ENpcState::Talking);
		ActiveTags.AddTag(FGameplayTag::RequestGameplayTag(FName("NPC.States.InConversation")));
	}
	UE_LOG(LogTemp, Warning, TEXT("START DIALOGUE"));
	
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("player null in start dialogue"));
		return;
	}
	Player->TogglePlayMode(EPlayModes::SocialMode, Player->bInteractableOpen, nullptr, this);
	//Player->SetCurrentPlayMode(EPlayModes::SocialMode, nullptr, this);
}

void ANpcBase_OM::EndDialog()
{
	if (bIsInDialogue)
	{
		bIsInDialogue = false;
		SetCurrentState(ExitDialogueState);
		if (auto* Cont = Cast<ANPC_AIController_OM>(GetController()))
		{
			Cont->GetBlackboardComponent()->ClearValue(FName("TargetRotation"));

		}
		
		ActiveTags.RemoveTag(FGameplayTag::RequestGameplayTag(FName("NPC.States.InConversation")));
	}
	if (!PlayerRelationship.bHasMetPlayer)
	{
		SetHasMetPlayer(true);
	}
	//SetActorTickEnabled(false);
}

void ANpcBase_OM::DarkModeToggle(const bool bIsDarkMode)
{
	if (bIsDarkMode)
	{
		AuraLight->SetAttenuationRadius(35.f);
	}
	else
	{
		AuraLight->SetAttenuationRadius(100.f);
	}
}


void ANpcBase_OM::SetFriendshipLevel(const float InAmount, const bool bReset)
{
	if (bReset)
	{
		PlayerRelationship.FriendshipLevel = FMath::Clamp(InAmount, -1.f, 1.f);
	}
	else
	{
		PlayerRelationship.FriendshipLevel = FMath::Clamp(PlayerRelationship.FriendshipLevel + InAmount, -1.f, 1.f);
	}

}

void ANpcBase_OM::SetCurrentInteractedNpc(ANpcBase_OM* InNpc)
{
	CurrentInteractedNpc = InNpc;

	if (auto* AICont = Cast<ANPC_AIController_OM>(GetController()))
	{
		if (UBlackboardComponent* BB = AICont->GetBlackboardComponent())
		{
			BB->SetValueAsObject(FName("Current Interacted Npc"), CurrentInteractedNpc.Get());

			FVector TargetLocation = FVector(
								static_cast<int16>(CurrentInteractedNpc->GetActorLocation().X),
								static_cast<int16>(CurrentInteractedNpc->GetActorLocation().Y),
								9.65f);
			
			BB->SetValueAsVector(FName("Target Location"), TargetLocation);
		}
	}
}

void ANpcBase_OM::SetCurrentState(const ENpcState InState)
{
	CurrentState = InState;

	if (CurrentState != ENpcState::Talking)
	{
		SetIsOpenForConversation(false);
	}
	
	if (auto* AICont = Cast<ANPC_AIController_OM>(GetController()))
	{
		if (UBlackboardComponent* BB = AICont->GetBlackboardComponent())
		{
			BB->SetValueAsEnum("NPC State", static_cast<uint8>(InState));

			BB->ClearValue(FName("TargetLocation"));
		}
	}
	//OnNpcStateChanged.Broadcast();
}


void ANpcBase_OM::Talk(USoundBase* InChatAudio) const
{
	if (!TalkingAudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("TalkingAudioComponent null"));
		return;
	}

	if (!InChatAudio)
	{
		UE_LOG(LogTemp, Error, TEXT("InChatAudio null"));
		return;
	}

	constexpr float VolumeRandomizationOffset = 0.1f;
	constexpr float PitchRandomizationOffset = 0.01f;
	const float VolumeRandomizeOffsetVal = FMath::RandRange(TalkingAudioComponent->VolumeMultiplier - VolumeRandomizationOffset, TalkingAudioComponent->VolumeMultiplier + VolumeRandomizationOffset);
	const float PitchRandomizeOffsetVal = FMath::RandRange(TalkingAudioComponent->PitchMultiplier - PitchRandomizationOffset, TalkingAudioComponent->PitchMultiplier + PitchRandomizationOffset);
	TalkingAudioComponent->SetVolumeMultiplier(VolumeRandomizeOffsetVal);
	TalkingAudioComponent->SetPitchMultiplier(PitchRandomizeOffsetVal);
	
	TalkingAudioComponent->SetSound(InChatAudio);
	TalkingAudioComponent->Play();
	
}

void ANpcBase_OM::PlayRandomTalkingAnimForMood()
{
	if (!AnimInstance.IsValid()) return;
	if (!AnimInstance->GetIsTalking()) return;

	UE_LOG(LogTemp, Warning, TEXT("Play random Talkeranim for mood called "));
	if (AnimInstance->GetIsExplaining())
	{
		PlayRandomTalkingHelper(ExplainingChats);
	}
	else if (AnimInstance->GetIsYelling())
	{
		PlayRandomTalkingHelper(AngryChats);
	}
	else if (AnimInstance->GetIsAffirming())
	{
		PlayRandomTalkingHelper(AffirmingChats);
	}
	else if (AnimInstance->GetIsDisagreeing())
	{
		PlayRandomTalkingHelper(DisagreeingChats);
	}
	else if (AnimInstance->GetIsDisgusted())
	{
		PlayRandomTalkingHelper(DisgustedChats);
	}
	else if (AnimInstance->GetIsLaughing())
	{
		PlayRandomTalkingHelper(LaughingChats);
	}
	else if (AnimInstance->GetIsConfused())
	{
		PlayRandomTalkingHelper(ConfusedChats);
	}
}
void ANpcBase_OM::PlayRandomTalkingHelper(TMap<USoundBase*, UAnimMontage*>& InChatMap)
{
	if (InChatMap.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Montage array empty"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Play random Talker Helper working 1"));


	/* Getting the random key/value combo from the Chat Map by making an iterator
	 * and generating a random integer as the final iterator element
	*/
	
	const int RandomIndex = FMath::RandRange(0, InChatMap.Num() - 1);
	TMap<USoundBase*, UAnimMontage*>::TIterator ChatMapIterator = InChatMap.CreateIterator();
	for (size_t i = 0; i < RandomIndex; i++)
	{
		++ChatMapIterator;
	}
	
	if (UAnimMontage* MontageToPlay = ChatMapIterator.Value())
	{
		if (AnimInstance.IsValid())
			AnimInstance->Montage_Play(MontageToPlay);

		CurrentTalkTime = MontageToPlay->GetPlayLength();

	}
	if (USoundBase* AudioToPlay = ChatMapIterator.Key())
	{
		Talk(AudioToPlay);
	}
}

TWeakObjectPtr<UNpcBaseAnimInstance_OM> ANpcBase_OM::GetAnimInstance()
{
	return AnimInstance;
}