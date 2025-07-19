// Copyright © 2025 4ozStudio. All rights reserved.

#include "Components/Character/Concrete/Exercise_OM.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/Other/Gym/Concrete/Barbell_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Audio/Concrete/PlayerVoiceAudio_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

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
	
	InitInjurys();
	
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
void UExercise_OM::InitInjurys() const
{
	if (!AnimInstance) return;

	AnimInstance->SetHasInjury(false);
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

void UExercise_OM::SetBodyPartInUse(const FBodyPartData& InBodyPart)
{
	BodyParts.Add(InBodyPart);
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
		{
			//Have a check here to see if equipment is a barbell
			Equipment->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, NeckSocket);
			SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
			break;
		}
	case EExerciseType::BicepCurl:
		{
			Equipment->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, LeftHandSocket);
			//Equipment->SetPivotOffset(NewRelativeLocation);
			Equipment->SetActorRelativeLocation(NewRelativeLocation);
			//Equipment->SetActorLocation(NewRelativeLocation);
			SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
			break;
		}
	case EExerciseType::OverheadPress:
		{
			SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
			//AnimInstance->SetIsInOverheadPressPosition(true);
			break;
		}
	case EExerciseType::LeftCurl:
		{
			Equipment->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, LeftHandSocket);
			//AnimInstance->SetIsInLeftCurlPosition(true);
			SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
			break;
		}
	case EExerciseType::RightCurl:
		{
			Equipment->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandSocket);
			//AnimInstance->SetIsInRightCurlPosition(true);
			SetCurrentWorkoutState(EWorkoutStates::InExercisePosition);
			break;
		}
	case EExerciseType::ChestDip:
		{
			SetCurrentWorkoutState(EWorkoutStates::Entry);
			break;
			//ManageEntry();
		}
	case EExerciseType::LegPress:
		{
			SetCurrentWorkoutState(EWorkoutStates::Entry);
			break;
		}
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

}
void UExercise_OM::ManageEntry()
{
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


void UExercise_OM::Injury(const EInjuryLevel& InInjuryLevel)
{
	AnimInstance->SetInjuryLevel(InInjuryLevel);
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		break;
	case EExerciseType::Squat:
		AnimInstance->SetHasInjury(true);
		AudioComponent->InjurySoundEffects(CurrentExerciseType);
		break;
	default:
		break;
	}

	if (BodyParts.IsEmpty()) return;
	
	for (FBodyPartData& Part : GameInstance->GetBodyStatus().BodyParts)
	{
		if (BodyParts.Contains(Part))
		{
			Part.SetInjury(InInjuryLevel);
		}
	}
		
}
void UExercise_OM::MinorInjury()
{
	constexpr float InjuryFocusDecrease = -0.2f;
	constexpr float MinorInjuryEnergyUse = -0.2f;
	switch (CurrentExerciseType)
	{
	case EExerciseType::None:
		return;
	case EExerciseType::Squat:
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
		return;
	}
	AnimInstance->SetHasInjury(true);
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
		case EExerciseType::ChestDip:
			return ChestDipDuration;
		case EExerciseType::LegPress:
			return 4.2f; // ---------------- Magic Number, Sort this whole duration thing out.  Maybe use dynamic?
		default:
			return SquatDuration;;
	}
}

EExerciseType UExercise_OM::GetCurrentExerciseType()
{
	return CurrentExerciseType;
}
void UExercise_OM::AddMuscleStat(const EBodyPart Part, const EBodyPartSide Side, float Increase) const
{
	if (!GameInstance) return;
	if (FBodyPartData* Data = GameInstance->FindBodyPart(Part, Side))
	{
		GameInstance->AddStat(Data->Strength, Increase);
	}
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
		DoRep(
			  [this](float Increase)
			  {
				  AddMuscleStat(EBodyPart::Thigh, EBodyPartSide::Left, Increase);
				  AddMuscleStat(EBodyPart::Thigh, EBodyPartSide::Right, Increase);
			  },
			  ExerciseParameters.LowerBodyIncrease,
			  ExerciseParameters.SquatsEnergyUse,
			  SquatDuration);
		break;

	case EExerciseType::BicepCurl:
		DoRep(
			  [this](float Increase)
			  {
				  AddMuscleStat(EBodyPart::Arm, EBodyPartSide::Left, Increase);
				  AddMuscleStat(EBodyPart::Arm, EBodyPartSide::Right, Increase);
			  },
			  ExerciseParameters.ArmIncrease,
			  ExerciseParameters.BicepCurlEnergyUse * 2,
			  BicepCurlDuration);
		break;

	case EExerciseType::OverheadPress:
		DoRep(
			  [this](float Increase)
			  {
				  AddMuscleStat(EBodyPart::Shoulder, EBodyPartSide::Center, Increase);
			  },
			  ExerciseParameters.ShoulderIncrease,
			  ExerciseParameters.OverheadPressEnergyUse,
			  OverheadPressDuration);
		break;

	case EExerciseType::LeftCurl:
		DoRep(
			  [this](float Increase)
			  {
				  AddMuscleStat(EBodyPart::Arm, EBodyPartSide::Left, Increase);
			  },
			  ExerciseParameters.ArmIncrease,
			  ExerciseParameters.BicepCurlEnergyUse,
			  BicepCurlDuration);
		break;

	case EExerciseType::RightCurl:
		DoRep(
			  [this](float Increase)
			  {
				  AddMuscleStat(EBodyPart::Arm, EBodyPartSide::Right, Increase);
			  },
			  ExerciseParameters.ArmIncrease,
			  ExerciseParameters.BicepCurlEnergyUse,
			  BicepCurlDuration);
		break;
	case EExerciseType::ChestDip:
		DoRep(
			[this](float Increase)
			{
				AddMuscleStat(EBodyPart::Chest, EBodyPartSide::Center, Increase);
			},
			ExerciseParameters.ArmIncrease,
			ExerciseParameters.ChestDipEnergyUse,
			ChestDipDuration);
		break;
	case EExerciseType::LegPress:
		DoRep(
			[this](float Increase)
			{
				AddMuscleStat(EBodyPart::Thigh, EBodyPartSide::Left, Increase);
				AddMuscleStat(EBodyPart::Thigh, EBodyPartSide::Right, Increase);
			},
			ExerciseParameters.LowerBodyIncrease,
			ExerciseParameters.LegPressEnergyUse,
			4.2f); // --- ----------------------- magic
	default:
		break;
	}
}


void UExercise_OM::DoRep(const TFunction<void(float)>& ModifyMuscleValueFunc, const float MuscleIncrease, const float EnergyUse, const float RepDuration)
{
	SetCurrentWorkoutState(EWorkoutStates::DoingRep);
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
	Equipment->SetIsInteractable(true);
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
