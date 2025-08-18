// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/Player/PlayerCharacter_OM.h"

#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Actors/Other/Both/Abstract/InteractableActor_OM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/Other/Gym/Concrete/Barbell_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Character/Concrete/PlayerDeformationsComponent_OM.h"
#include "OptimizeMan/Public/Game/GMB/BedroomGameModeBase_OM.h"
#include "OptimizeMan/Public/Game/GMB/GymGameModeBase_OM.h"
#include "Components/Character/Concrete/Exercise_OM.h"
#include "Components/Audio/Concrete/FootstepAudio_OM.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Components/Audio/Concrete/PlayerVoiceAudio_OM.h"
#include "Components/Character/Concrete/SocialInteractionSystem_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Camera/CameraActor.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/Audio/Concrete/PlayerAmbience_OM.h"
#include "Components/Character/Concrete/AbilitySystemComponent_OM.h"
#include "Components/Character/Concrete/CameraComponent_OM.h"
#include "Components/Character/Concrete/PlayerAmbienceControlComponent.h"
#include "Components/Character/Concrete/SpringArmComponent_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"
#include "GameplayAbilitySystem/GameplayEffects/Gym/Concrete/FocusTick_OM.h"

APlayerCharacter_OM::APlayerCharacter_OM()
{
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent_OM>(TEXT("CameraDrift"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(0, 0, 0));
	SpringArmComponent->SetRelativeLocation(FVector(0, 0, 0));
	SpringArmComponent->SocketOffset = FVector(20, 0, 80);
	SpringArmComponent->bEnableCameraLag = false;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->TargetArmLength = 10.f;
	SpringArmComponent->TargetOffset = FVector(0, 0, 0);
	
	Camera = CreateDefaultSubobject<UCameraComponent_OM>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(SpringArmComponent);
	Camera->SetRelativeLocation(FVector(0, 0, 0));
	Camera->bUsePawnControlRotation = true;
	

	PlayerAudioComponent = CreateDefaultSubobject<UPlayerVoiceAudio_OM>(TEXT("AudioComponent"));
	PlayerAudioComponent->bAutoActivate = true;
	PlayerAudioComponent->SetVolumeMultiplier(1.f);

	FootstepAudioComponent = CreateDefaultSubobject<UFootstepAudio_OM>(TEXT("FootstepAudio"));
	FootstepAudioComponent->bAutoActivate = true;
	FootstepAudioComponent->SetVolumeMultiplier(0.6f);

	NotificationAudioComponent = CreateDefaultSubobject<UNotificationAudio_OM>(TEXT("NotificationAudioComponent"));
	NotificationAudioComponent->bAutoActivate = true;
	NotificationAudioComponent->SetVolumeMultiplier(1.f);
	
	ExerciseComponent = CreateDefaultSubobject<UExercise_OM>(TEXT("ExerciseComponent"));
	ExerciseComponent->bAutoActivate = true;

	SocialComponent = CreateDefaultSubobject<USocialInteractionSystem_OM>(TEXT("SocialInteractionComponent"));
	SocialComponent->bAutoActivate = true;

	BodyDeformerComponent = CreateDefaultSubobject<UPlayerDeformationsComponent_OM>(TEXT("BodyDeformer"));
	BodyDeformerComponent->bAutoActivate = true;

	AbSysComp = CreateDefaultSubobject<UAbilitySystemComponent_OM>(TEXT("AbilitySystemComponent"));
	//MentalHealthStats = CreateDefaultSubobject<UMentalHealthStats_OM>(TEXT("Mental Health Attributes"));
	//GymSpecificStats = CreateDefaultSubobject<UGymSpecificStats_OM>(TEXT("Gym Stats"));


	AmbienceControlComponent = CreateDefaultSubobject<UPlayerAmbienceControlComponent>(TEXT("Ambience Visual"));
	AmbienceControlComponent->bAutoActivate = true;

	

	SelfieCameraLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SelfieCameraLocation"));
	SelfieCameraLocation->SetupAttachment(RootComponent);
	SelfieCameraLocation->SetVisibility(false);

	
	SetMinimumMovementThreshold(0.5f);
	SetIsWalking(false);
	TimeSinceLastFootstep = 0.f;

	CurrentPlayMode = EPlayModes::RegularMode;
	
	bTodoOpen = false;
	bPauseMenuOpen = false;
	bInteractableOpen = false;

	PlayerFacingMuscleViewLocation = FVector(240, 2102, 90);

	DefaultSkeletalMesh = nullptr;
	
}
void APlayerCharacter_OM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (FootstepAudioComponent && FootstepAudioComponent->IsPlaying())
		FootstepAudioComponent->Stop();

	if (NotificationAudioComponent && NotificationAudioComponent->IsPlaying())
		NotificationAudioComponent->Stop();

	if (PlayerAudioComponent && PlayerAudioComponent->IsPlaying())
		PlayerAudioComponent->Stop();

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}
void APlayerCharacter_OM::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AbSysComp->AddSet<UMentalHealthStats_OM>();
	AbSysComp->AddSet<UGymSpecificStats_OM>();

	//InitializeEffects();
	InitializeConstantEffects();
}


void APlayerCharacter_OM::BeginPlay()
{
	Super::BeginPlay();

	InitPlayModes();
	PlayerController = Cast<APlayerController_OM>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	LastPosition = GetActorLocation();
	
	if (UCharacterMovementComponent* PlayerMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement()))
		SetOriginalMovementSpeed(PlayerMovement->MaxWalkSpeed);
	
	
	GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoManager) return;

	
	if (USkeletalMeshComponent* SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>())
	{
		DefaultSkeletalMesh = SkeletalMeshComponent->GetSkeletalMeshAsset();
		CachedAnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(SkeletalMeshComponent->GetAnimInstance());

		if (!CachedAnimInstance.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to cache anim instance!"));
			return;
		}
	}
	
	


	HeadPosition = GetMesh()->GetBoneLocation("Head");
	SetCurrentPlayMode(EPlayModes::RegularMode);
	SetEmotionalState();
	
	InitializeAttributes();
	InitializeConstantEffects();

}



void APlayerCharacter_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovementState();
	if (FootstepAudioComponent)
		FootstepAudioComponent->Footsteps(DeltaTime);
	
	bIsJumping = GetIsJumping();
	
	if (CurrentPlayMode == EPlayModes::RegularMode)
	{
		CheckInteractable();
	}
}
void APlayerCharacter_OM::InitializeAttributes()
{
	if (!GameInstance) return;
	if (!AbSysComp) return; 
	
	const FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();

	UGameplayEffect* CurrentMentalStatsGE = NewObject<UGameplayEffect>(GetTransientPackage(), TEXT("CurrentMentalStats"));
	CurrentMentalStatsGE->DurationPolicy = EGameplayEffectDurationType::Instant;

	{
		FGameplayModifierInfo Mod;
		Mod.Attribute = UMentalHealthStats_OM::GetEgoAttribute();
		Mod.ModifierOp = EGameplayModOp::Override;
		Mod.ModifierMagnitude = FScalableFloat(InnerStatus.Ego);
		CurrentMentalStatsGE->Modifiers.Add(Mod);
	}
	{
		FGameplayModifierInfo Mod;
		Mod.Attribute = UMentalHealthStats_OM::GetSocialAttribute();
		Mod.ModifierOp = EGameplayModOp::Override;
		Mod.ModifierMagnitude = FScalableFloat(InnerStatus.Social);
		CurrentMentalStatsGE->Modifiers.Add(Mod);
	}
	{
		FGameplayModifierInfo Mod;
		Mod.Attribute = UMentalHealthStats_OM::GetSexAppealAttribute();
		Mod.ModifierOp = EGameplayModOp::Override;
		Mod.ModifierMagnitude = FScalableFloat(InnerStatus.SexAppeal);
		CurrentMentalStatsGE->Modifiers.Add(Mod);
	}
	AbSysComp->ApplyGameplayEffectToSelf(CurrentMentalStatsGE, 1.f, AbSysComp->MakeEffectContext());
}

void APlayerCharacter_OM::InitializeConstantEffects()
{
	if (AbSysComp)
	{
		FGameplayEffectContextHandle EffectContext = AbSysComp->MakeEffectContext();
		EffectContext.AddSourceObject(this); 

		AbSysComp->ApplyGameplayEffectToSelf(EnergyTickClass.GetDefaultObject(), 1.0f, EffectContext);
		AbSysComp->ApplyGameplayEffectToSelf(FocusTickClass.GetDefaultObject(), 1.0f, EffectContext);
	}
}

void APlayerCharacter_OM::SyncStatsToGameInstance()
{
	if (!AbSysComp) return;
	const UMentalHealthStats_OM* MentalStats = AbSysComp->GetSet<UMentalHealthStats_OM>();
	if (!MentalStats) return;

	FInnerStatus NewInnerStatus;
	NewInnerStatus.Ego = MentalStats->GetEgo();
	NewInnerStatus.Social = MentalStats->GetSocial();
	NewInnerStatus.SexAppeal = MentalStats->GetSexAppeal();

	GameInstance->SetInnerStatus(NewInnerStatus);
}


/*
 *			GameModes
 *
 * 
 */


void APlayerCharacter_OM::InitPlayModes()
{
	FPlayModeConfig PauseModeConfig;
	PauseModeConfig.bSetToUiMode = true;
	PauseModeConfig.bAllowGameMovement = false;
	PauseModeConfig.bHasWidget = true;
	PauseModeConfig.ForcedLocation = FVector();
	PauseModeConfig.ForcedRotation = FRotator();
	PauseModeConfig.bHasAFadeIn = false;
	PauseModeConfig.bNeedsPreSteps = false;
	PauseModeConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Paused");
	PlayModeConfigs.Add(EPlayModes::PauseMode, PauseModeConfig);

	FPlayModeConfig SocialModeConfig;
	SocialModeConfig.bSetToUiMode = true;
	SocialModeConfig.bAllowGameMovement = true;
	SocialModeConfig.bHasWidget = true;
	SocialModeConfig.ForcedLocation = FVector();
	SocialModeConfig.ForcedRotation = FRotator();
	SocialModeConfig.bHasAFadeIn = false;
	SocialModeConfig.bNeedsPreSteps = false;
	SocialModeConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Social");
	PlayModeConfigs.Add(EPlayModes::SocialMode, SocialModeConfig);

	FPlayModeConfig WorkoutModeConfig;
	WorkoutModeConfig.bSetToUiMode = true;
	WorkoutModeConfig.bAllowGameMovement = false;
	WorkoutModeConfig.bHasWidget = true;
	WorkoutModeConfig.ForcedLocation = FVector();
	WorkoutModeConfig.ForcedRotation = FRotator();
	WorkoutModeConfig.bHasAFadeIn = false;
	WorkoutModeConfig.bNeedsPreSteps = true;
	WorkoutModeConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Workout");
	PlayModeConfigs.Add(EPlayModes::WorkoutMode, WorkoutModeConfig);

	const FVector PlayerFacingMirrorLoc = FVector(423.42f,-256.31f,91.501f);

	FPlayModeConfig MirrorModeConfig;
	MirrorModeConfig.bSetToUiMode = true;
	MirrorModeConfig.bAllowGameMovement = false;
	MirrorModeConfig.bHasWidget = true;
	MirrorModeConfig.ForcedLocation = PlayerFacingMirrorLoc;
	MirrorModeConfig.ForcedRotation = FRotator(1, 1, 0);
	MirrorModeConfig.bHasAFadeIn = false;
	MirrorModeConfig.bNeedsPreSteps = false;
	MirrorModeConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	PlayModeConfigs.Add(EPlayModes::MirrorMode, MirrorModeConfig);

	FPlayModeConfig MuscleViewModeConfig;
	MuscleViewModeConfig.bSetToUiMode = true;
	MuscleViewModeConfig.bAllowGameMovement = false;
	MuscleViewModeConfig.bHasWidget = true;
	MuscleViewModeConfig.ForcedLocation = FVector();
	MuscleViewModeConfig.ForcedRotation = FRotator::ZeroRotator;
	MuscleViewModeConfig.bHasAFadeIn = false;
	MuscleViewModeConfig.bNeedsPreSteps = false;
	MuscleViewModeConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	PlayModeConfigs.Add(EPlayModes::MuscleViewMode, MuscleViewModeConfig);
	
	const FVector PlayerFacingShelfLoc = FVector(508.4f, -202.3f, 90.1f);
	const FRotator PlayerFacingShelfRot = FRotator(-30,-90,0);

	FPlayModeConfig ShelfModeConfig;
	ShelfModeConfig.bSetToUiMode = true;
	ShelfModeConfig.bAllowGameMovement = false;
	ShelfModeConfig.bHasWidget = true;
	ShelfModeConfig.ForcedLocation = PlayerFacingShelfLoc;
	ShelfModeConfig.ForcedRotation = PlayerFacingShelfRot;
	ShelfModeConfig.bHasAFadeIn = false;
	ShelfModeConfig.bNeedsPreSteps = false;
	ShelfModeConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	PlayModeConfigs.Add(EPlayModes::ShelfMode, ShelfModeConfig);
  
	FPlayModeConfig LaptopModeConfig;
	LaptopModeConfig.bSetToUiMode = true;
	LaptopModeConfig.bAllowGameMovement = false;
	LaptopModeConfig.bHasWidget = true;
	LaptopModeConfig.ForcedLocation = FVector();
	LaptopModeConfig.ForcedRotation = FRotator();
	LaptopModeConfig.bHasAFadeIn = false;
	LaptopModeConfig.bNeedsPreSteps = false;
	LaptopModeConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	PlayModeConfigs.Add(EPlayModes::LaptopMode, LaptopModeConfig);

	FPlayModeConfig CalenderModeConfig;
	CalenderModeConfig.bSetToUiMode = true;
	CalenderModeConfig.bAllowGameMovement = false;
	CalenderModeConfig.bHasWidget = true;
	CalenderModeConfig.ForcedLocation = FVector();
	CalenderModeConfig.ForcedRotation = FRotator();
	CalenderModeConfig.bHasAFadeIn = false;
	CalenderModeConfig.bNeedsPreSteps = false;
	CalenderModeConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	PlayModeConfigs.Add(EPlayModes::CalenderMode, CalenderModeConfig);

	FPlayModeConfig WakeUpConfig;
	WakeUpConfig.bSetToUiMode = true;
	WakeUpConfig.bAllowGameMovement = false;
	WakeUpConfig.bHasWidget = true;
	WakeUpConfig.ForcedLocation = FVector();
	WakeUpConfig.ForcedRotation = FRotator();
	WakeUpConfig.bHasAFadeIn = false;
	WakeUpConfig.bNeedsPreSteps = false;
	WakeUpConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	PlayModeConfigs.Add(EPlayModes::WakeUpMode, WakeUpConfig);

	FPlayModeConfig TodoConfig;
	TodoConfig.bSetToUiMode = true;
	TodoConfig.bAllowGameMovement = true;
	TodoConfig.bHasWidget = true;
	TodoConfig.ForcedLocation = FVector();
	TodoConfig.ForcedRotation = FRotator();
	TodoConfig.bHasAFadeIn = false;
	TodoConfig.bNeedsPreSteps = false;
	TodoConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	PlayModeConfigs.Add(EPlayModes::TodoMode, TodoConfig);

	FPlayModeConfig VendingConfig;
	VendingConfig.bSetToUiMode = true;
	VendingConfig.bAllowGameMovement = false;
	VendingConfig.bHasWidget = true;
	VendingConfig.ForcedLocation = FVector();
	VendingConfig.ForcedRotation = FRotator();
	VendingConfig.bHasAFadeIn = false;
	VendingConfig.bNeedsPreSteps = false;
	TodoConfig.StateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	PlayModeConfigs.Add(EPlayModes::VendingMachine, VendingConfig);

}

EWorkoutStates APlayerCharacter_OM::GetWorkoutState() const
{
	if (ExerciseComponent)
		return ExerciseComponent->GetCurrentWorkoutState();
	return EWorkoutStates::NotInExercisePosition;
}
EExerciseType APlayerCharacter_OM::GetCurrentExerciseType() const
{
	if (ExerciseComponent)
		return ExerciseComponent->GetCurrentExerciseType();
	return EExerciseType::None;
}

void APlayerCharacter_OM::SetCurrentPlayMode(const EPlayModes InPlayMode, const TWeakObjectPtr<AInteractableActor_OM> InInteractedActor, const TWeakObjectPtr<ANpcBase_OM> InInteractedCharacter)
{
	// dont allow to switch between playmode unless its regular to x or x to regular 
	if (CurrentPlayMode != EPlayModes::RegularMode && InPlayMode != EPlayModes::RegularMode) return;

	if (!PlayerController) return;
	
	CurrentPlayMode = InPlayMode;

	OnPlayModeChange.Broadcast(CurrentPlayMode);


	if (CachedAnimInstance.IsValid())
	{
		CachedAnimInstance.Get()->SetCurrentPlayMode(CurrentPlayMode);
	}

	if (CurrentPlayMode == EPlayModes::MirrorMode)
		PlayerController->HideGamePointsHud(true);
	else
		PlayerController->HideGamePointsHud(false);

	if (CurrentPlayMode == EPlayModes::RegularMode)
	{
		ManageRegularMode();
		return;
	}
	CurrentInteractedActor = InInteractedActor.Get();
	CurrentInteractedCharacter = InInteractedCharacter.Get();
	

	if (!PlayModeConfigs.Contains(InPlayMode))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayModeConfig does not contain InPlayMode"));
		return;
	}
	const FPlayModeConfig& Config = PlayModeConfigs[InPlayMode];

	
	SwitchStateTag(Config.StateTag);
	
	if (!Config.ForcedLocation.IsZero())
	{
		SetActorLocation(Config.ForcedLocation);
	}
	if (!Config.ForcedRotation.IsZero())
	{
		PlayerController->SetControlRotation(Config.ForcedRotation);
	}
	
	if (Config.bNeedsPreSteps)
		ManageCurrentPlayMode();

	if (Config.bHasWidget)
	{
		PlayerController->PlaymodeWidgetManagement(CurrentPlayMode, Config.bHasAFadeIn);
	}

	SetToUIMode(Config.bSetToUiMode, Config.bAllowGameMovement);
	
	
	if (!Config.bNeedsPreSteps)
		ManageCurrentPlayMode();
}

void APlayerCharacter_OM::TogglePlayMode(EPlayModes InPlayMode, bool& InOpenOrClosedState, AInteractableActor_OM* InInteractableActor, ANpcBase_OM* InInteractedCharacter)
{
	if (!InOpenOrClosedState && CurrentPlayMode == EPlayModes::RegularMode)
	{
		SetCurrentPlayMode(InPlayMode, InInteractableActor, InInteractedCharacter);
		InOpenOrClosedState = true;
		UE_LOG(LogTemp, Error, TEXT("Toggle on"));
	}
	else
	{
		if (InPlayMode == EPlayModes::PauseMode)
			OnPauseMenuToggled.Broadcast(bPauseMenuOpen);
		else
			SetCurrentPlayMode(EPlayModes::RegularMode);
		InOpenOrClosedState = false;
		UE_LOG(LogTemp, Error, TEXT("Toggle off"));
	}


}

void APlayerCharacter_OM::TogglePauseMode()
{
	if (CurrentPlayMode == EPlayModes::WakeUpMode) return;
	
	TogglePlayMode(EPlayModes::PauseMode, bPauseMenuOpen); 
}


void APlayerCharacter_OM::ManageCurrentPlayMode()
{
	switch (CurrentPlayMode)
	{
	case EPlayModes::WorkoutMode:
		ManageWorkoutMode();
		break;
	case EPlayModes::RegularMode:
		ManageRegularMode();
		break;
	case EPlayModes::SocialMode:
		ManageSocialMode();
		break;
	case EPlayModes::TodoMode:
		ManageTodoMode();
		break;
	case EPlayModes::PauseMode:
		ManagePauseMode();
		break;
	default:
		break;
	}
}


void APlayerCharacter_OM::ManageRegularMode()
{
	if (!PlayerController) return;
	PlayerController->RemoveAllActiveWidgets();
	if (CurrentInteractedCharacter)
	{
		CurrentInteractedCharacter->EndDialog();
		CurrentInteractedCharacter = nullptr;
	}
	if (CurrentInteractedActor)
	{
		CurrentInteractedActor = nullptr;
	}

	PlayerController->SetViewTargetWithBlend(this, 0.5f);

	SetToUIMode(false);
	
	SetMaxMovementSpeed(GetOriginalMovementSpeed());

	SwitchStateTag(FGameplayTag::RequestGameplayTag("State.Idle"));

	
	if (!PlayerController->GetIsInteractableWidgetOnViewport())
	{
		PlayerController->ToggleInteractWidgetFromViewport(false);
	}
}

void APlayerCharacter_OM::SwitchTag(const FGameplayTag InTag, const FGameplayTag RootTag)
{
	TArray<FGameplayTag> CurrentTags;
	AbSysComp->GetOwnedGameplayTags().GetGameplayTagArray(CurrentTags);
	

	for (const FGameplayTag& Tag : CurrentTags)
	{
		if (Tag.MatchesTag(RootTag))
		{
			AbSysComp->RemoveLooseGameplayTag(Tag);
		}
	}
	AbSysComp->AddLooseGameplayTag(InTag);
}


void APlayerCharacter_OM::ManagePauseMode()
{
	if (!GameInstance->GetHasOpenedPauseMenuInitial())
		GameInstance->SetHasOpenedPauseMenuInitial(true);
}

void APlayerCharacter_OM::ManageSocialMode()
{
	if (!SocialComponent) return;
	
	SocialComponent->InitConversation();
}

void APlayerCharacter_OM::ManageWorkoutMode()
{
	if (AExerciseEquipment_OM* EquipmentActor = Cast<AExerciseEquipment_OM>(CurrentInteractedActor))
	{
		if (!EquipmentActor->GetGymCamera())
		{
			UE_LOG(LogTemp, Error, TEXT("Gym camera is null"));
			return;
		}
		
		const FVector NewLocation = EquipmentActor->GetLookAtCameraPosition();
		const FRotator NewRotation = EquipmentActor->GetLookAtCameraRotation();

		SetMaxMovementSpeed(0.f);
		PlayerController->SetControlRotation(NewRotation);
		SetActorLocationAndRotation(NewLocation, NewRotation);
		

		if (EquipmentActor->GetGymCamera())
		{
			PlayerController->SetViewTargetWithBlend(EquipmentActor->GetGymCamera(), 0.5f);
		}

		//PlayerController->PlaymodeWidgetManagement(EPlayModes::WorkoutMode, false);

	}
}


void APlayerCharacter_OM::ManageTodoMode()
{
	if (GameInstance && !GameInstance->GetHasOpenedTodoListInitial())
		GameInstance->SetHasOpenedTodoListInitial(true);
}

/*
 *			UI Related Stuff   
 *
 * 
 */

void APlayerCharacter_OM::SetToUIMode(const bool bSetToUiMode, const bool bAllowGameMovement, UUserWidget* InWidget, bool bAllowCameraRotation) const
{
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is NULL"));
		return;
	}
    
	if (bSetToUiMode)
	{
		FInputModeGameAndUI InputModeUI;
		InputModeUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		
		if (InWidget)
		{
			InputModeUI.SetWidgetToFocus(InWidget->TakeWidget());
		}
		else if (UUserWidget* WidgetInstanceToFocus = PlayerController->GetCurrentPlayModeWidgetInstance())
		{
			InputModeUI.SetWidgetToFocus(WidgetInstanceToFocus->TakeWidget());
		}
		else
		{
			InputModeUI.SetWidgetToFocus(nullptr);
		}


		
		PlayerController->SetInputMode(InputModeUI);
		if (!bAllowCameraRotation)
			PlayerController->SetIgnoreLookInput(true);
		PlayerController->SetShowMouseCursor(true);

		int32 ViewportSizeX, ViewportSizeY;
		PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
		PlayerController->SetMouseLocation(ViewportSizeX / 2, ViewportSizeY / 2);
       
		if (!bAllowGameMovement)
		{
			if (GetCharacterMovement())
			{
				GetCharacterMovement()->SetMovementMode(MOVE_None);
			}
		}
		else
		{
			if (GetCharacterMovement())
			{
				GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			}
		}
	}
	else
	{
		FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetIgnoreLookInput(false);
		
       
		if (GetCharacterMovement())
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}
}


/*
 *			
 *     --------------- Interact, States, Locomotion
 * 
 */

void APlayerCharacter_OM::Interact(const bool bToggleable)
{
	FVector Start = Camera->GetComponentLocation();
	FVector ForwardVector = Camera->GetForwardVector();
	FVector End = Start + (ForwardVector * 200.0f);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	if (CurrentPlayMode != EPlayModes::RegularMode && !bToggleable) return;
	
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	if (bHit)
	{
		AActor* InteractedActor = HitResult.GetActor();
		if (!InteractedActor) return;
		
		if (AInteractableActor_OM* InteractedActorInterface = Cast<AInteractableActor_OM>(InteractedActor))
		{
			if (!InteractedActorInterface->InteractableInterfaceProperties.bIsInteractable) return;
			if (!GameInstance->GetHasInteractedInitial())
				GameInstance->SetHasInteractedInitial(true);
			
			InteractedActorInterface->Interact_Implementation();
		}
		else if (ANpcBase_OM* InteractedNpcInterface = Cast<ANpcBase_OM>(InteractedActor))
		{
			InteractedNpcInterface->Interact_Implementation();
		}
	}
	else if (CurrentInteractedActor && CurrentPlayMode != EPlayModes::RegularMode && CurrentPlayMode != EPlayModes::WorkoutMode)
	{
		CurrentInteractedActor->Interact_Implementation();
	}
}

void APlayerCharacter_OM::CheckInteractable()
{
	const FVector Start = Camera->GetComponentLocation();
	const FVector ForwardVector = Camera->GetForwardVector();
	const FVector End = Start + (ForwardVector * 200.0f); 

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	if (!PlayerController) return;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bHit)
	{
		AActor* InteractedActor = HitResult.GetActor();
		if (!InteractedActor) return;
		
		
		if (AInteractableActor_OM* InteractedActorInterface = Cast<AInteractableActor_OM>(InteractedActor))
		{
			if (!InteractedActorInterface->InteractableInterfaceProperties.bIsInteractable) return;
			PlayerController->WidgetInteraction(InteractedActorInterface);
		}
		else if (ANpcBase_OM* InteractedNpcInterface = Cast<ANpcBase_OM>(InteractedActor))
		{
			PlayerController->WidgetInteraction(InteractedNpcInterface);
		}
		else if (PlayerController->GetIsInteractableWidgetOnViewport())
		{
			PlayerController->ToggleInteractWidgetFromViewport(true);
		}
	}
	else if (PlayerController->GetIsInteractableWidgetOnViewport())
	{
		PlayerController->ToggleInteractWidgetFromViewport(true);
	}
}

void APlayerCharacter_OM::UpdateMovementState()
{
	const FVector CurrentPosition = GetActorLocation();
	const float MovementDelta = FVector::Distance(CurrentPosition, LastPosition);
	SetIsWalking(MovementDelta > MinimumMovementThreshold);

	LastPosition = CurrentPosition;
}
void APlayerCharacter_OM::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
	
}
void APlayerCharacter_OM::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
	
}
bool APlayerCharacter_OM::GetIsJumping() const
{
	constexpr float LengthToFloor = 100.f;
	FHitResult HitResult;
	FVector PlayerPosition = GetActorLocation();
	FVector GroundPosition = PlayerPosition - FVector(0.0f, 0.0f, LengthToFloor);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, PlayerPosition, GroundPosition, ECC_Visibility, QueryParams))
	{
		if (HitResult.GetComponent())
		{
			return false;
		}
		return true;
	}
	return true;
}
UAbilitySystemComponent* APlayerCharacter_OM::GetAbilitySystemComponent() const
{
	return AbSysComp;
}



void APlayerCharacter_OM::Jump()
{
	if (!GetCharacterMovement())
	{
		UE_LOG(LogTemp, Error, TEXT("Cant get character movement from Jump"));
		return;
	}
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant get game instance from Jump"));
		return;
	}

	//FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	float CurrentJumpHeight = CalculateJumpHeight(0.2f);
	GetCharacterMovement()->JumpZVelocity = CurrentJumpHeight;
	Super::Jump();
}

void APlayerCharacter_OM::InteractClick()
{
	if (PlayerController && PlayerController->WidgInteractionComp)
	{
		PlayerController->WidgInteractionComp->PressPointerKey(EKeys::LeftMouseButton);
		PlayerController->WidgInteractionComp->ReleasePointerKey(EKeys::LeftMouseButton);
	}
	Interact(false);
}

float APlayerCharacter_OM::CalculateJumpHeight(const float LowerBodyStat) const 
{
	float NormalizedStat = FMath::Clamp(LowerBodyStat / 100.0f, 0.0f, 1.0f);
	
	float CalculatedHeight = BaseJumpHeight + (JumpHeightMultiplier * BaseJumpHeight * NormalizedStat);
	
	return FMath::Clamp(CalculatedHeight, MinJumpHeight, MaxJumpHeight);
}

float APlayerCharacter_OM::GetMaxMovementSpeed() const
{
	const UCharacterMovementComponent* PlayerMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	return PlayerMovement->MaxWalkSpeed;
}
void APlayerCharacter_OM::SetMaxMovementSpeed(const float InMaxMovementSpeed)
{
	if (UCharacterMovementComponent* PlayerMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement()))
	{
		PlayerMovement->MaxWalkSpeed = InMaxMovementSpeed;
	}
}

/*
 *
 * -------- Emotional States
 * 
 */


void APlayerCharacter_OM::SetEmotionalState()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	if (!GameInstance)
		return;
	

	constexpr float ChadThreshold = 0.7f;
	constexpr float GrindsetThreshold = 0.35f;
	constexpr float DoomerThreshold = -0.3f;
	constexpr float GoblinThreshold = -0.2f;

	const float Ego = GameInstance->GetEgo();
	const float SexAppeal = GameInstance->GetSexAppeal();
	const float Social = GameInstance->GetSocial();
	
	EPlayerEmotionalStates NewState;
	UE_LOG(LogTemp, Error, TEXT("Ego: %f \n SexAppeal: %f \n Social: %f "), Ego, SexAppeal, Social);

	if (Ego >= ChadThreshold && SexAppeal >= ChadThreshold)
	{
		UE_LOG(LogTemp, Error, TEXT("new state giga"));

		NewState = EPlayerEmotionalStates::Gigachad;
	}
	else if (Ego >= GrindsetThreshold && (Social >= GrindsetThreshold || SexAppeal >= GrindsetThreshold))
	{
		UE_LOG(LogTemp, Error, TEXT("new state grind"));
		NewState = EPlayerEmotionalStates::Grindset;
	}
	else if (SexAppeal <= GoblinThreshold && Social <= GoblinThreshold && Ego >= GrindsetThreshold)
	{
		UE_LOG(LogTemp, Error, TEXT("new state goblin"));
		NewState = EPlayerEmotionalStates::GoblinMode;
	}
	else if (Ego <= DoomerThreshold && (Social <= DoomerThreshold || SexAppeal <= DoomerThreshold))
	{
		UE_LOG(LogTemp, Error, TEXT("new state doom"));
		NewState = EPlayerEmotionalStates::Doomer;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("new state cope"));
		NewState = EPlayerEmotionalStates::Cope;
	}
	
	GameInstance->SetCurrentEmotionalState(NewState);
}

void APlayerCharacter_OM::SetTempEmotionalState(const ETemporaryEmotionalStates InState)
{
	if (CurrentTempEmotionalState == InState) return;
	
	CurrentTempEmotionalState = InState;
	OnTempEmotionsChanged.Broadcast(CurrentTempEmotionalState);
}


void APlayerCharacter_OM::ShitDay()
{
	PlayerAudioComponent->UpsetSoundEffects();
}
void APlayerCharacter_OM::ShitReaction()
{
	PlayerAudioComponent->GrumpySoundEffects();
}

/*
 *			Other
 *
 * 
 */


void APlayerCharacter_OM::ClearTimers()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(SocialComponent);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(ExerciseComponent);
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	if (!TodoManager)
		TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!PlayerController)
		PlayerController = Cast<APlayerController_OM>(GetController());
	GetWorld()->GetTimerManager().ClearAllTimersForObject(TodoManager);
	if (PlayerController)
		GetWorld()->GetTimerManager().ClearAllTimersForObject(PlayerController);
}

void APlayerCharacter_OM::ResetPlayer()
{
	USkeletalMeshComponent* SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();
	if (SkeletalMeshComponent && DefaultSkeletalMesh)
	{
		TSubclassOf<UAnimInstance> AnimInstance = SkeletalMeshComponent->GetAnimClass();
		
		SkeletalMeshComponent->SetSkeletalMesh(nullptr);
		SkeletalMeshComponent->SetSkeletalMesh(DefaultSkeletalMesh);
		
		SkeletalMeshComponent->SetAnimInstanceClass(AnimInstance);
		SkeletalMeshComponent->InitAnim(true); 
		SkeletalMeshComponent->TickAnimation(0.f, false);

		CachedAnimInstance = Cast<UPlayerCharacterAnimInstance_OM>(SkeletalMeshComponent->GetAnimInstance());

		if (!CachedAnimInstance.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to cache anim instance!"));
			return;
		}
		
		SkeletalMeshComponent->MarkRenderStateDirty();
	}
}
