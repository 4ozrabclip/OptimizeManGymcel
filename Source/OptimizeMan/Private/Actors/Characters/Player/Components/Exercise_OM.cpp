// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Player/Components/Exercise_OM.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/Items/Gym/Equipment/Barbell_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/Components/PlayerVoiceAudio_OM.h"
#include "Utils/GameInstance_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Utils/TodoManagementSubsystem.h"

UExercise_OM::UExercise_OM()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentExerciseType = EExerciseType::None;
	bStoppedExercise = true;
	bStartedSet = false;
	bDoingRep = false;
	Equipment = nullptr;
	AudioComponent = nullptr;
	RepCount = 0;
	SetCount = 0;
	TimeSinceLastRep = 0.f;
	NewRelativeLocation = FVector(21.f, -1.f, 0.f); //bicepcurl
	CurrentWorkoutState = EWorkoutStates::NotInExercisePosition;
}

void UExercise_OM::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance->SetHasSquatInjury(false);
	
	AudioComponent = Player->FindComponentByClass<UPlayerVoiceAudio_OM>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Audio Component is NULL"));
	}
	if (GameInstance)
	{
		ExerciseParameters.UpdateParameters(GameInstance);
		UE_LOG(LogTemp, Display, TEXT("Updated Exercise Paramaters"));
	}

	SetComponentTickEnabled(false);
}
void UExercise_OM::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentWorkoutState != EWorkoutStates::SetComplete)
	{
		if (CurrentWorkoutState == EWorkoutStates::InExercisePosition && TimeSinceLastRep < 5.f)
		{
			TimeSinceLastRep += DeltaTime;
		}
		else if (TimeSinceLastRep >= 5.f && CurrentWorkoutState == EWorkoutStates::InExercisePosition)
		{
			TimeSinceLastRep = 0.f;
			SetCurrentWorkoutState(EWorkoutStates::SetComplete);
			SetCount++;
			RepCount = 0;
			
		}
		else if (TimeSinceLastRep > 0.f && CurrentWorkoutState == EWorkoutStates::DoingRep)
		{
			TimeSinceLastRep = 0.f;
		}
	}

	if (TimeSinceLastRep > 10.f) //idle in set complete mode
	{
		constexpr float FocusDecreaseInWorkoutIdle = -0.0001f;
		AddFocus(FocusDecreaseInWorkoutIdle);
	}
}

void UExercise_OM::SetExerciseType(const EExerciseType InExerciseType)
{

	if (CurrentExerciseType != InExerciseType)
	{
		SetCurrentWorkoutState(EWorkoutStates::NotInExercisePosition);
	
	}
	//need exercise type to be stated before EnterExercisePosition
	CurrentExerciseType = InExerciseType;
	

}
void UExercise_OM::PrepareExercise()
{
	if (GameInstance && GameInstance->GetGymResStats().Energy <= 0.f)
	{
		if (CurrentExerciseType != EExerciseType::None)
		{
			LeaveExercise();
		}
		return;
	}
	

	if (CurrentWorkoutState == EWorkoutStates::NotInExercisePosition)
	{
		EnterExercisePosition();
	}
}
void UExercise_OM::EnterExercisePosition()
{
	const FName NeckSocket = FName("NeckSocket");
	const FName LeftHandSocket = FName("LeftHandSocket");
	const FName RightHandSocket = FName("RightHandSocket");

	AnimInstance = Player->GetCachedAnimInstance();

	if (!AnimInstance) return;
	
	Equipment = Cast<AExerciseEquipment_OM>(Player->GetCurrentInteractedActor());
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		break;
	case EExerciseType::Squat:
		//Have a check here to see if equipment is a barbell
		Equipment->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, NeckSocket);
		AnimInstance->SetIsInSquatPosition(true);
		break;
	case EExerciseType::BicepCurl:
		Equipment->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, LeftHandSocket);
		//Equipment->SetPivotOffset(NewRelativeLocation);
		Equipment->SetActorRelativeLocation(NewRelativeLocation);
		//Equipment->SetActorLocation(NewRelativeLocation);
		AnimInstance->SetIsInCurlPosition(true);
		break;
	case EExerciseType::OverheadPress:
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, "EnterExercisePosition: OHP");
		AnimInstance->SetIsInOverheadPressPosition(true);
		break;
	case EExerciseType::LeftCurl:
		Equipment->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, LeftHandSocket);
		AnimInstance->SetIsInLeftCurlPosition(true);
		break;
	case EExerciseType::RightCurl:
		Equipment->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandSocket);
		AnimInstance->SetIsInRightCurlPosition(true);
		break;
	default:
		return;
	}
	
	RepCount = 0;
	SetCount = 0;
	bStartedSet = false;
	if (IsComponentTickEnabled())
		SetComponentTickEnabled(false);

	Equipment->AuraLight->SetVisibility(false);
	Player->GetCharacterMovement()->SetMovementMode(MOVE_None);
	SetStoppedExercise(false);
	SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
}

void UExercise_OM::MiniGame()
{
	if (CurrentWorkoutState == EWorkoutStates::NotInExercisePosition)
	{
		UE_LOG(LogTemp, Error, TEXT("Not in exercise position"));
		EnterExercisePosition();
	}
	else
	{
		SetRep();
	}
}



void UExercise_OM::Injury()
{
	switch (CurrentExerciseType)
	{
		case EExerciseType::None:
			break;
		case EExerciseType::Squat:
			AnimInstance->SetHasSquatInjury(true);
			AudioComponent->InjurySoundEffects(CurrentExerciseType);
		
			break;
		default:
			break;
	}
}

void UExercise_OM::MinorInjury()
{
	constexpr float InjuryFocusDecrease = -0.2f;
	constexpr float MinorInjuryEnergyUse = -0.2f;
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		break;
	case EExerciseType::Squat:
		AnimInstance->SetHasMinorSquatInjury(true);
		AudioComponent->MinorInjurySoundEffects(CurrentExerciseType);
		break;
	case EExerciseType::BicepCurl:
		AudioComponent->MinorInjurySoundEffects(CurrentExerciseType);
		break;
	case EExerciseType::OverheadPress:
		AudioComponent->MinorInjurySoundEffects(CurrentExerciseType);
		break;
	case EExerciseType::LeftCurl:
		AudioComponent->MinorInjurySoundEffects(CurrentExerciseType);
		break;
	case EExerciseType::RightCurl:
		AudioComponent->MinorInjurySoundEffects(CurrentExerciseType);
		break;
	default:
		break;
	}
	FGymResStats& GymResStats = GameInstance->GetGymResStats();
	GameInstance->AddGymResStats(GymResStats.Energy, MinorInjuryEnergyUse);
	AddFocus(InjuryFocusDecrease);
}

void UExercise_OM::DoASquat()
{
	if (!Player || !Player->IsValidLowLevel()) return;
	
	if (CurrentWorkoutState == EWorkoutStates::NotInExercisePosition)
	{
		EnterExercisePosition();
	}
	else
	{
		SetRep();
	}
}

float UExercise_OM::GetRepDuration()
{
	switch (CurrentExerciseType)
	{
		case EExerciseType::None:
			return 0.f;
		case EExerciseType::Squat:
			return SquatDuration;
		case EExerciseType::BicepCurl:
			return BicepCurlDuration;
		case EExerciseType::OverheadPress:
			return OverheadPressDuration;
		default:
			return SquatDuration;;
	}
}

EExerciseType UExercise_OM::GetCurrentExerciseType()
{
	return CurrentExerciseType;
}
void UExercise_OM::SetRep()
{
	constexpr float EgoIncrease = 0.07f;
	
	FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	FInnerStatus& InnerStatus = GameInstance->GetInnerStatus();
	FGymResStats& GymResStats = GameInstance->GetGymResStats();

	if (!TodoManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Todomanager is null in exercise SetRep"));
		return;
	}
	
	GameInstance->AddStat(InnerStatus.Ego, EgoIncrease);
	
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		break;
	case EExerciseType::Squat:
		DoRep([this]{AnimInstance->DoSquatRep();},
			[this, &BodyStatus](float Increase)  {GameInstance->AddStat(BodyStatus.LowerBody, Increase);},
			ExerciseParameters.LowerBodyIncrease,
			ExerciseParameters.SquatsEnergyUse,
			SquatDuration);
		break;
	case EExerciseType::BicepCurl:
		DoRep([this] {AnimInstance->DoCurlRep();},
			[this, &BodyStatus](float Increase){GameInstance->AddStat(BodyStatus.LeftArm, Increase); GameInstance->AddStat(BodyStatus.RightArm, Increase);},
			ExerciseParameters.ArmIncrease,
			ExerciseParameters.BicepCurlEnergyUse*2,
			BicepCurlDuration);
		break;
	case EExerciseType::OverheadPress:
		DoRep([this]{AnimInstance->DoOverheadPressRep();},
			[this, &BodyStatus](float Increase){GameInstance->AddStat(BodyStatus.Shoulders, Increase);},
			ExerciseParameters.ShoulderIncrease,
			ExerciseParameters.OverheadPressEnergyUse,
			OverheadPressDuration);
		break;
	case EExerciseType::LeftCurl:
		DoRep([this]{AnimInstance->DoLeftCurlRep();},
			[this, &BodyStatus](float Increase){GameInstance->AddStat(BodyStatus.LeftArm, Increase);},
			ExerciseParameters.ArmIncrease,
			ExerciseParameters.BicepCurlEnergyUse,
			BicepCurlDuration);
		break;
		case EExerciseType::RightCurl:
		DoRep([this]{AnimInstance->DoRightCurlRep();},
[this, &BodyStatus](float Increase){GameInstance->AddStat(BodyStatus.RightArm, Increase);},
			ExerciseParameters.ArmIncrease,
			ExerciseParameters.BicepCurlEnergyUse,
			BicepCurlDuration);
		break;
	default:
		break;
	}
}


void UExercise_OM::DoRep(const TFunction<void()>& AnimFunction, const TFunction<void(float)>& ModifyMuscleValueFunc, const float MuscleIncrease, const float EnergyUse, const float RepDuration)
{
	SetCurrentWorkoutState(EWorkoutStates::DoingRep);
	if (AnimFunction)
	{
		AnimFunction();
	}
	RepCount++;

	if (!bStartedSet)
		bStartedSet = true;

	if (!IsComponentTickEnabled())
		SetComponentTickEnabled(true);
	

	GetWorld()->GetTimerManager().ClearTimer(ExerciseTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		ExerciseTimerHandle,
		[this]()
		{
			SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
			if (GameInstance->GetGymResStats().Energy <= 0.f)
			{
				LeaveExercise();
			}
		},
		RepDuration, 
		false 
	);
	if (ModifyMuscleValueFunc)
	{
		ModifyMuscleValueFunc(MuscleIncrease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find modify muscle value func"));
	}
	FGymResStats& GymRes = GameInstance->GetGymResStats();
	GameInstance->AddGymResStats(GymRes.Energy, EnergyUse);
	AudioComponent->WorkoutGruntSoundEffects(CurrentExerciseType);
	CheckForExerciseAchievements();
}

void UExercise_OM::CheckForExerciseAchievements()
{
	//CompletedTodosCheckList.Empty();
	if (RepCount >= 10 && !CompletedTodosCheckList.Contains(FGameplayTag::RequestGameplayTag("Todos.Gym.HitTenSquats")))
	{
		CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Gym.HitTenSquats"));
	}
	if (RepCount >= 1 && !CompletedTodosCheckList.Contains(FGameplayTag::RequestGameplayTag("Todos.Gym.Workout")))
	{
		CompletedTodosCheckList.Add(FGameplayTag::RequestGameplayTag("Todos.Gym.Workout"));
	}

	TodoManager->DelayForPlayerAchievements(CompletedTodosCheckList);
}


void UExercise_OM::LeaveExercise()
{
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		break;
	case EExerciseType::Squat:
		AnimInstance->ExitSquatPosition();
		break;
	case EExerciseType::BicepCurl:
		AnimInstance->ExitCurlPosition();
		break;
	case EExerciseType::OverheadPress:
		AnimInstance->ExitOverheadPressPosition();
		break;
	case EExerciseType::LeftCurl:
		AnimInstance->ExitLeftCurlPosition();
		break;
	case EExerciseType::RightCurl:
		AnimInstance->ExitRightCurlPosition();
		break;
	default:
		break;
	}
	SetCurrentWorkoutState(EWorkoutStates::NotInExercisePosition);
	
	DetachEquipment();

	
	if (Equipment && !Equipment->AuraLight->GetVisibleFlag())
	{
		Equipment->AuraLight->SetVisibility(true);
	}

	
	
	CurrentExerciseType = EExerciseType::None;

	CheckForExerciseAchievements();

}


void UExercise_OM::DetachEquipment() const
{
	if (!Equipment)	return;
	if (!Equipment->IsAttachedTo(Player)) return;

	Equipment->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Equipment->SetActorTransform(Equipment->GetOriginalPosition());
}

void UExercise_OM::SetCurrentWorkoutState(const EWorkoutStates InWorkoutState)
{
	CurrentWorkoutState = InWorkoutState;

	OnWorkoutStateChanged.Broadcast(CurrentWorkoutState);
	
}

bool UExercise_OM::GetHasEnergy()
{
	return GameInstance->GetGymResStats().Energy > 0;
}
