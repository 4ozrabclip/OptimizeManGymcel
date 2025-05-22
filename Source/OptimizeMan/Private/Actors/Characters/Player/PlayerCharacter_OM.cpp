// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Player/PlayerCharacter_OM.h"

#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/InteractableActor_OM.h"
#include "OptimizeMan/Public/Widgets/InteractWidget_OM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/Items/Gym/Equipment/Barbell_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Characters/NPC/NpcBase_OM.h"
#include "Actors/Characters/Player/Components/PlayerDeformationsComponent_OM.h"
#include "OptimizeMan/Public/Utils/BedroomGameModeBase_OM.h"
#include "OptimizeMan/Public/Utils/GymGameModeBase_OM.h"
#include "Actors/Characters/Player/Components/Exercise_OM.h"
#include "Actors/Characters/Player/Components/FootstepAudio_OM.h"
#include "Actors/Characters/Player/Components/NotificationAudio_OM.h"
#include "Utils/GameInstance_OM.h"
#include "Actors/Characters/Player/Components/PlayerVoiceAudio_OM.h"
#include "Actors/Characters/Player/Components/SocialInteractionSystem_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Misc/MapErrors.h"
#include "Utils/TodoManagementSubsystem.h"
#include "Widgets/GymHud_OM.h"
#include "Widgets/HintsWidget_OM.h"

// Sets default values
APlayerCharacter_OM::APlayerCharacter_OM()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(RootComponent);
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

void APlayerCharacter_OM::BeginPlay()
{
	Super::BeginPlay();

	InitPlayModes();

	
	
	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	LastPosition = GetActorLocation();
	
	if (UCharacterMovementComponent* PlayerMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement()))
	{
		SetOriginalMovementSpeed(PlayerMovement->MaxWalkSpeed);
	}
	GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("No Game Instance found in player class beginplay"));
		return;
	}
	TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("TODO MANAGER IS NULL IN PLAYER CHARACTER BEGINOPLAY"));
		return;
	}
	if (USkeletalMeshComponent* SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>())
	{
		DefaultSkeletalMesh = SkeletalMeshComponent->GetSkeletalMeshAsset();
	}
		
	
	 //THIS IS SUPER MESSY, FIX THIS.  ITS JUST TO PLAY THE SPLAT SOUND
	if (GameInstance && NotificationAudioComponent)
	{
		if (GameInstance->GetDayNumber() == 1 && !GameInstance->GetHasBeenToGymToday())
		{
			// Only try to use the bedroom game mode if needed
			if (Cast<ABedroomGameModeBase_OM>(GetWorld()->GetAuthGameMode()))
			{
				NotificationAudioComponent->PlaySplatSound();
			}
		}
	}
	if (USkeletalMeshComponent* SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>())
	{
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

	RefreshJumpSettings();


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

void APlayerCharacter_OM::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputToLook, ETriggerEvent::Triggered, this, &APlayerCharacter_OM::Look);
		EnhancedInputComponent->BindAction(InputToMove, ETriggerEvent::Triggered, this, &APlayerCharacter_OM::Move);
		EnhancedInputComponent->BindAction(InputToJump, ETriggerEvent::Triggered, this, &APlayerCharacter_OM::Jump);
		EnhancedInputComponent->BindAction(InputToInteractClick, ETriggerEvent::Completed, this, &APlayerCharacter_OM::InteractClick);
		EnhancedInputComponent->BindAction(InputToInteractToggle, ETriggerEvent::Completed, this, &APlayerCharacter_OM::InteractToggle);
		EnhancedInputComponent->BindAction(InputToOpenTodo, ETriggerEvent::Completed, this, &APlayerCharacter_OM::ToggleTodoMode);
		EnhancedInputComponent->BindAction(InputToOpenPauseMenu, ETriggerEvent::Completed, this, &APlayerCharacter_OM::TogglePauseMode);
	}
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
	PauseModeConfig.WidgetToDisplay = PauseMenuWidget;
	PauseModeConfig.ForcedLocation = FVector();
	PauseModeConfig.ForcedRotation = FRotator();
	PauseModeConfig.bHasAFadeIn = false;
	PauseModeConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::PauseMode, PauseModeConfig);

	FPlayModeConfig SocialModeConfig;
	SocialModeConfig.bSetToUiMode = true;
	SocialModeConfig.bAllowGameMovement = true;
	SocialModeConfig.WidgetToDisplay = SocialWidget;
	SocialModeConfig.ForcedLocation = FVector();
	SocialModeConfig.ForcedRotation = FRotator();
	SocialModeConfig.bHasAFadeIn = false;
	SocialModeConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::SocialMode, SocialModeConfig);

	FPlayModeConfig WorkoutModeConfig;
	WorkoutModeConfig.bSetToUiMode = true;
	WorkoutModeConfig.bAllowGameMovement = false;
	WorkoutModeConfig.WidgetToDisplay = WorkoutWidget;
	WorkoutModeConfig.ForcedLocation = FVector();
	WorkoutModeConfig.ForcedRotation = FRotator();
	WorkoutModeConfig.bHasAFadeIn = false;
	WorkoutModeConfig.bNeedsPreSteps = true;
	PlayModeConfigs.Add(EPlayModes::WorkoutMode, WorkoutModeConfig);

	const FVector PlayerFacingMirrorLoc = FVector(423.42f,-256.31f,91.501f);

	FPlayModeConfig MirrorModeConfig;
	MirrorModeConfig.bSetToUiMode = true;
	MirrorModeConfig.bAllowGameMovement = false;
	MirrorModeConfig.WidgetToDisplay = MirrorWidget;
	MirrorModeConfig.ForcedLocation = PlayerFacingMirrorLoc;
	MirrorModeConfig.ForcedRotation = FRotator(1, 1, 0);
	MirrorModeConfig.bHasAFadeIn = false;
	MirrorModeConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::MirrorMode, MirrorModeConfig);

	FPlayModeConfig MuscleViewModeConfig;
	MuscleViewModeConfig.bSetToUiMode = true;
	MuscleViewModeConfig.bAllowGameMovement = false;
	MuscleViewModeConfig.WidgetToDisplay = MuscleViewWidget;
	MuscleViewModeConfig.ForcedLocation = FVector();
	MuscleViewModeConfig.ForcedRotation = FRotator::ZeroRotator;
	MuscleViewModeConfig.bHasAFadeIn = false;
	MuscleViewModeConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::MuscleViewMode, MuscleViewModeConfig);
	
	const FVector PlayerFacingShelfLoc = FVector(508.4f, -202.3f, 90.1f);
	const FRotator PlayerFacingShelfRot = FRotator(-30,-90,0);

	FPlayModeConfig ShelfModeConfig;
	ShelfModeConfig.bSetToUiMode = true;
	ShelfModeConfig.bAllowGameMovement = false;
	ShelfModeConfig.WidgetToDisplay = ShelfWidget;
	ShelfModeConfig.ForcedLocation = PlayerFacingShelfLoc;
	ShelfModeConfig.ForcedRotation = PlayerFacingShelfRot;
	ShelfModeConfig.bHasAFadeIn = false;
	ShelfModeConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::ShelfMode, ShelfModeConfig);

	FPlayModeConfig LaptopModeConfig;
	LaptopModeConfig.bSetToUiMode = true;
	LaptopModeConfig.bAllowGameMovement = false;
	LaptopModeConfig.WidgetToDisplay = LaptopWidget;
	LaptopModeConfig.ForcedLocation = FVector();
	LaptopModeConfig.ForcedRotation = FRotator();
	LaptopModeConfig.bHasAFadeIn = false;
	LaptopModeConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::LaptopMode, LaptopModeConfig);

	FPlayModeConfig CalenderModeConfig;
	CalenderModeConfig.bSetToUiMode = true;
	CalenderModeConfig.bAllowGameMovement = false;
	CalenderModeConfig.WidgetToDisplay = CalenderWidget;
	CalenderModeConfig.ForcedLocation = FVector();
	CalenderModeConfig.ForcedRotation = FRotator();
	CalenderModeConfig.bHasAFadeIn = false;
	CalenderModeConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::CalenderMode, CalenderModeConfig);

	FPlayModeConfig WakeUpConfig;
	WakeUpConfig.bSetToUiMode = true;
	WakeUpConfig.bAllowGameMovement = false;
	WakeUpConfig.WidgetToDisplay = WakeUpWidget;
	WakeUpConfig.ForcedLocation = FVector();
	WakeUpConfig.ForcedRotation = FRotator();
	WakeUpConfig.bHasAFadeIn = false;
	WakeUpConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::WakeUpMode, WakeUpConfig);

	FPlayModeConfig TodoConfig;
	TodoConfig.bSetToUiMode = true;
	TodoConfig.bAllowGameMovement = true;
	TodoConfig.WidgetToDisplay = TodoWidget;
	TodoConfig.ForcedLocation = FVector();
	TodoConfig.ForcedRotation = FRotator();
	TodoConfig.bHasAFadeIn = false;
	TodoConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::TodoMode, TodoConfig);

	FPlayModeConfig SpeakerModeConfig;
	SpeakerModeConfig.bSetToUiMode = true;
	SpeakerModeConfig.bAllowGameMovement = true;
	SpeakerModeConfig.WidgetToDisplay = nullptr;
	SpeakerModeConfig.ForcedLocation = FVector();
	SpeakerModeConfig.ForcedRotation = FRotator();
	SpeakerModeConfig.bHasAFadeIn = false;
	SpeakerModeConfig.bNeedsPreSteps = false;
	PlayModeConfigs.Add(EPlayModes::SpeakerMode, SpeakerModeConfig);
}

void APlayerCharacter_OM::SetCurrentPlayMode(const EPlayModes InPlayMode, AInteractableActor_OM* InInteractedActor, ANpcBase_OM* InInteractedCharacter)
{
	// dont allow to switch between playmode unless its regular to x or x to regular 
	if (CurrentPlayMode != EPlayModes::RegularMode && InPlayMode != EPlayModes::RegularMode) return;
	
	CurrentPlayMode = InPlayMode;

	if (CurrentPlayMode == EPlayModes::RegularMode)
	{
		ManageRegularMode();
		return;
	}
	CurrentInteractedActor = InInteractedActor;
	CurrentInteractedCharacter = InInteractedCharacter;

	if (!PlayModeConfigs.Contains(InPlayMode))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayModeConfig does not contain InPlayMode"));
		return;
	}
	const FPlayModeConfig& Config = PlayModeConfigs[InPlayMode];
	
	RemoveAllActiveWidgets();
	
	SetToUIMode(Config.bSetToUiMode, Config.bAllowGameMovement);
	
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

	if (!Config.WidgetToDisplay)
	{
		UE_LOG(LogTemp, Error, TEXT("No widget to display in current play mode"));
		return;
	}
	
	if (!Config.WidgetToDisplay->IsInViewport())
	{
		UE_LOG(LogTemp, Error, TEXT("Widget not already in viewport TEST"));
		if (Config.bHasAFadeIn && Config.WidgetToDisplay)
		{
			FadeWidgets(nullptr, Config.WidgetToDisplay);
			ActiveWidgets.Add(Config.WidgetToDisplay);
		}
		else if (Config.WidgetToDisplay)
		{
			Config.WidgetToDisplay->AddToViewport();
			UE_LOG(LogTemp, Error, TEXT("Added to viewport TEST"));
    
			// Add these debug lines
			UE_LOG(LogTemp, Error, TEXT("Widget Visibility: %d"), (int)Config.WidgetToDisplay->GetVisibility());
			UE_LOG(LogTemp, Error, TEXT("Widget Size: %s"), *Config.WidgetToDisplay->GetDesiredSize().ToString());
			UE_LOG(LogTemp, Error, TEXT("Widget Opacity: %f"), Config.WidgetToDisplay->GetRenderOpacity());
			
			ActiveWidgets.Add(Config.WidgetToDisplay);
		}
	}

	if (!Config.bNeedsPreSteps)
		ManageCurrentPlayMode();
}

void APlayerCharacter_OM::TogglePlayMode(EPlayModes InPlayMode, bool& InOpenOrClosedState, AInteractableActor_OM* InInteractableActor)
{
	if (!InOpenOrClosedState && CurrentPlayMode == EPlayModes::RegularMode)
	{
		SetCurrentPlayMode(InPlayMode, InInteractableActor);
		InOpenOrClosedState = true;
		UE_LOG(LogTemp, Error, TEXT("Toggle on"));
	}
	else
	{
		SetCurrentPlayMode(EPlayModes::RegularMode);
		InOpenOrClosedState = false;
		UE_LOG(LogTemp, Error, TEXT("Toggle off"));
	}
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
	RemoveAllActiveWidgets();
	if (CurrentInteractedCharacter)
	{
		CurrentInteractedCharacter->EndDialog();
		CurrentInteractedCharacter = nullptr;
	}
	if (CurrentInteractedActor)
	{
		CurrentInteractedActor = nullptr;
	}
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(this, 0.5f);

		SetToUIMode(false);
	}
	SetMaxMovementSpeed(GetOriginalMovementSpeed());
	
	if (InteractableActorWidget && !InteractableActorWidget->IsInViewport())
	{
		InteractableActorWidget->AddToViewport();
	}
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
		
		if (WorkoutWidget && !WorkoutWidget->IsInViewport())
		{
			if (EquipmentActor->GetGymCamera())
			{
				PlayerController->SetViewTargetWithBlend(EquipmentActor->GetGymCamera(), 0.5f);
			}

			WorkoutWidget->AddToViewport();
			ActiveWidgets.Add(WorkoutWidget);
		}
	}
}

void APlayerCharacter_OM::ManageTodoMode()
{
	if (GameInstance && !GameInstance->GetHasOpenedTodoListInitial())
		GameInstance->SetHasOpenedTodoListInitial(true);
}


/*
 *			UI Related Stuff    ------- make hints component, and widgets component
 *
 * 
 */
void APlayerCharacter_OM::UpdateGymHud()
{
	if (!GymHudWidget->IsInViewport()) return;
	if (UGymHud_OM* HudClass = Cast<UGymHud_OM>(GymHudWidget))
	{
		HudClass->UpdateProgressBars();
	}
}
void APlayerCharacter_OM::SetGymHud(bool bLoad)
{
	if (!GymHudWidget) return;

	if (bLoad)
	{
		if (GymHudWidget->IsInViewport()) return;

		GymHudWidget->AddToViewport();
	}
	else
	{
		if (!GymHudWidget->IsInViewport()) return;

		GymHudWidget->RemoveFromParent();
	}


}

void APlayerCharacter_OM::ShowOrHideHint(const FString& HintText, float HintLength, bool HideHint, bool RemoveFully) const // Move this out of the player class
{ 
	if (!HintWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("HintWidget is NULL"));
		return;
	}
	UHintsWidget_OM* HintWidgetClass = Cast<UHintsWidget_OM>(HintWidget);
	if (!HintWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Cast Failed to HintsWidget_OM"));
		return;
	}
	const FText HintInputText = FText::FromString(*HintText);

	if (RemoveFully && HintWidget->IsInViewport())
		HintWidget->RemoveFromParent();
	
	if (HideHint && HintWidget->IsInViewport())
	{
		HintWidgetClass->HideHint();
	}
	else if (!HideHint && !HintWidget->IsInViewport())
	{
		HintWidget->AddToViewport();
		if (HintLength > 0.f)
		{
			HintWidgetClass->ShowHint(HintInputText, HintLength);
		}
		else
		{
			HintWidgetClass->ShowHint(HintInputText);
		}
	}
	else if (!HideHint && HintWidget->IsInViewport())
	{
		if (HintLength > 0.f)
		{
			HintWidgetClass->ShowHint(HintInputText, HintLength);
		}
		else
		{
			HintWidgetClass->ShowHint(HintInputText);
		}
	}
}

void APlayerCharacter_OM::SetToUIMode(const bool bSetToUiMode, const bool bAllowGameMovement) const
{
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is NULL"));
		return;
	}
    
	if (bSetToUiMode)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		
		InputMode.SetWidgetToFocus(nullptr); 
       
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);

		int32 ViewportSizeX, ViewportSizeY;
		PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
		PlayerController->SetMouseLocation(ViewportSizeX / 2, ViewportSizeY / 2);
       
		if (!bAllowGameMovement)
		{
			PlayerController->SetIgnoreLookInput(true);

			if (GetCharacterMovement())
			{
				GetCharacterMovement()->SetMovementMode(MOVE_None);
			}
		}
		else
		{
			PlayerController->SetIgnoreLookInput(false);
           
			if (GetCharacterMovement())
			{
				GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			}
		}
	}
	else
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetIgnoreLookInput(false);
       
		if (GetCharacterMovement())
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}
}

void APlayerCharacter_OM::FadeWidgets(UUserWidget* FadeOutWidget, UUserWidget* FadeInWidget)
{
	ABedroomGameModeBase_OM* BedroomGameMode = Cast<ABedroomGameModeBase_OM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!FadeOutWidget && BedroomGameMode)
		FadeOutWidget = BedroomGameMode->GetShowDayWidget(); 
	if (!FadeOutWidget)
		return;
	
	if (!FadeOutWidget->IsInViewport() && !FadeInWidget->IsInViewport())
	{
		FadeInWidget->AddToViewport();
		return;
	}
	
	if (UParentWidget_OM* WidgetParentClass = Cast<UParentWidget_OM>(FadeInWidget))
	{
		GetWorld()->GetTimerManager().SetTimer(
			SetModeWidgetFadeInTimerHandle,
			[this, FadeOutWidget, WidgetParentClass]()
			{
				if (FadeOutWidget->GetRenderOpacity() < 1.f)
				{
					GetWorld()->GetTimerManager().ClearTimer(SetModeWidgetFadeInTimerHandle);
					WidgetParentClass->FadeIn();
				}
			},
		0.016f, 
		true
		);
	}
}
void APlayerCharacter_OM::HideUnhideInteractableWidget(const bool bHide)
{
	if (!InteractableActorWidget) return;

	if (bHide)
		InteractableActorWidget->SetVisibility(ESlateVisibility::Hidden);
	else
		InteractableActorWidget->SetVisibility(ESlateVisibility::Visible);
}
void APlayerCharacter_OM::RemoveAllActiveWidgets()
{
	if (InteractableActorWidget && InteractableActorWidget->IsInViewport())
	{
		InteractableActorWidget->RemoveFromParent();
	}
	for (UUserWidget* Widget : ActiveWidgets)
	{
		if (Widget && Widget->IsInViewport())
		{
			UE_LOG(LogTemp, Error, TEXT("Removing widget from viewport"));
			Widget->RemoveFromParent();
		}
	}
	ActiveWidgets.Empty();
}

void APlayerCharacter_OM::WidgetInteraction(const TScriptInterface<IInteractableInterface_OM>& InteractedActorInterface)
{
	if (InteractableActorWidget) return;
	
	if (const TSubclassOf<UUserWidget> WidgetClass = InteractedActorInterface->GetInteractableWidget())
	{
		InteractableActorWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (UInteractWidget_OM* InteractWidget = Cast<UInteractWidget_OM>(InteractableActorWidget))
		{
			//InteractWidget->CheckAndSetTextColour();
			InteractWidget->SetText(InteractedActorInterface->GetInteractionWidgetText());
		}
		if (!InteractableActorWidget->IsInViewport())
		{
			InteractableActorWidget->AddToViewport();
		}
	}
}

void APlayerCharacter_OM::TodoCompletedPopUp()
{
	// Clean this up so that I dont need to recast so blatantly
	if (!NotificationAudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Notification component is null"));
		return;
	}
	NotificationAudioComponent->PlayTodoCompletedSound();
	
	if (TodoCompleteWidget && !TodoCompleteWidget->IsInViewport())
	{
		TodoCompleteWidget->AddToViewport();
	}
	
	constexpr float PopUpTimeAmount = 4.f;

	GetWorld()->GetTimerManager().ClearTimer(TodoPopUpHandle);
	GetWorld()->GetTimerManager().SetTimer(
		TodoPopUpHandle,
		[this]()
		{
			if (TodoCompleteWidget->IsInViewport())
			{
				TodoCompleteWidget->RemoveFromParent();
			}
		},
		PopUpTimeAmount,
		false
		);
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

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bHit)
	{
		AActor* InteractedActor = HitResult.GetActor();
		if (!InteractedActor) return;
		
		
		if (AInteractableActor_OM* InteractedActorInterface = Cast<AInteractableActor_OM>(InteractedActor))
		{
			if (!InteractedActorInterface->InteractableInterfaceProperties.bIsInteractable) return;
			WidgetInteraction(InteractedActorInterface);
		}
		else if (ANpcBase_OM* InteractedNpcInterface = Cast<ANpcBase_OM>(InteractedActor))
		{
			WidgetInteraction(InteractedNpcInterface);
		}
		else if (InteractableActorWidget && InteractableActorWidget->IsInViewport())
		{
			InteractableActorWidget->RemoveFromParent();
			InteractableActorWidget = nullptr;
		}
	}
	else if (InteractableActorWidget && InteractableActorWidget->IsInViewport())
	{
		InteractableActorWidget->RemoveFromParent();
		InteractableActorWidget = nullptr;
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

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter_OM::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}
bool APlayerCharacter_OM::GetIsJumping()
{
	constexpr float LengthToFloor = 100.f;
	FHitResult HitResult;
	FVector PlayerPosition = GetActorLocation();
	FVector GroundPosition = PlayerPosition - FVector(0.0f, 0.0f, LengthToFloor);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, PlayerPosition, GroundPosition, ECC_Visibility, QueryParams))
	{
		if (UPrimitiveComponent* HitComponent = HitResult.GetComponent())
		{
			return false;
		}
		return true;
	}
	return true;
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

	FPlayerData PlayerData = GameInstance->GetPlayerData();
	float CurrentJumpHeight = CalculateJumpHeight(PlayerData.LowerBody);
	GetCharacterMovement()->JumpZVelocity = CurrentJumpHeight;
	Super::Jump();
}
float APlayerCharacter_OM::CalculateJumpHeight(const float LowerBodyStat) const 
{
	float NormalizedStat = FMath::Clamp(LowerBodyStat / 100.0f, 0.0f, 1.0f);
	
	float CalculatedHeight = BaseJumpHeight + (JumpHeightMultiplier * BaseJumpHeight * NormalizedStat);
	
	return FMath::Clamp(CalculatedHeight, MinJumpHeight, MaxJumpHeight);
}
void APlayerCharacter_OM::RefreshJumpSettings()
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
	FPlayerData PlayerData = GameInstance->GetPlayerData();


	float CurrentJumpHeight = CalculateJumpHeight(PlayerData.LowerBody);
	GetCharacterMovement()->JumpZVelocity = CurrentJumpHeight;

	
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
	
	FPlayerData& PlayerData = GameInstance->GetPlayerData();
	
	constexpr float ChadThreshold = 0.7f;
	constexpr float GrindsetThreshold = 0.35f;
	constexpr float DoomerThreshold = -0.3f;
	constexpr float GoblinThreshold = -0.2f;

	const float Ego = PlayerData.GetEgo();
	const float SexAppeal = PlayerData.GetSexAppeal();
	const float Social = PlayerData.GetSocial();
	
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
EPlayerEmotionalStates APlayerCharacter_OM::GetCurrentEmotionalState()
{
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());

	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Cast GI in GetEmotionalState, just return doomer"));
		return EPlayerEmotionalStates::Doomer;
	}

	const FPlayerData& PlayerData = GameInstance->GetPlayerData();

	return PlayerData.CurrentEmotionalState;
	
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
	GetWorld()->GetTimerManager().ClearAllTimersForObject(InteractableActorWidget);
	if (!GameInstance)
		GameInstance = Cast<UGameInstance_OM>(GetGameInstance());
	if (!TodoManager)
		TodoManager = Cast<UTodoManagementSubsystem>(GameInstance->GetSubsystem<UTodoManagementSubsystem>());
	GetWorld()->GetTimerManager().ClearAllTimersForObject(TodoManager);
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
