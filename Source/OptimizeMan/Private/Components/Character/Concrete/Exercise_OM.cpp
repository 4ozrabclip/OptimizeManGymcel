// Copyright © 2025 4ozStudio. All rights reserved.

#include "Components/Character/Concrete/Exercise_OM.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/Other/Gym/Concrete/Barbell_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Audio/Concrete/PlayerVoiceAudio_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Components/Character/Concrete/AbilitySystemComponent_OM.h"
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
	AbSysComp = nullptr;
	GymStats = nullptr;
	RepCount = 0;
	SetCount = 0;
	TimeSinceLastRep = 0.f;
	NewRelativeLocation = FVector(21.f, -1.f, 0.f); //bicepcurl
	CurrentWorkoutState = EWorkoutStates::NotInExercisePosition;
	CurrentInjuredPart = nullptr;
}

void UExercise_OM::BeginPlay()
{
	Super::BeginPlay();

	if (Player)
		AbSysComp = Cast<UAbilitySystemComponent_OM>(Player->GetAbilitySystemComponent());
	if (AbSysComp)
		GymStats = AbSysComp->GetSet<UGymSpecificStats_OM>();
	
	InitInjurys();
	
	AudioComponent = Player->FindComponentByClass<UPlayerVoiceAudio_OM>();
	if (!AudioComponent) return;
	if (GameInstance)
	{
		ExerciseParameters.UpdateParameters(GameInstance);
		UE_LOG(LogTemp, Display, TEXT("Updated Exercise Paramaters"));
	}

	SetComponentTickEnabled(false);
}
void UExercise_OM::InitInjurys()
{
	if (!AnimInstance) return;
	
	AnimInstance->SetHasInjury(false);

	CurrentInjuredPart = nullptr;
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
	if (BodyParts.IsEmpty()) return;

	
	AnimInstance->SetInjuryLevel(InInjuryLevel);
	AnimInstance->SetHasInjury(true);
	AudioComponent->InjurySoundEffects(CurrentExerciseType);
	constexpr float InjuryFocusDecrease = -0.2f;

	

	if (BodyParts.Num() < 1) return;

	FBodyPartData* MostInjuredBodyPart = &BodyParts[0];

	
	// Update most injured body part
	if (BodyParts.Num() == 2)
	{
		MostInjuredBodyPart =  BodyParts[1].InjuryLevel > BodyParts[0].InjuryLevel ? &BodyParts[1] : &BodyParts[0];
	}
	else if (BodyParts.Num() > 2)
	{
		for (FBodyPartData& Part : GameInstance->GetBodyStatus().BodyParts)
		{
			if (BodyParts.Contains(Part))
			{
				if (Part.InjuryLevel > MostInjuredBodyPart->InjuryLevel)
					MostInjuredBodyPart = &Part;
			}
		}
	}

	CurrentInjuredPart = MostInjuredBodyPart;
	
	
	for (FBodyPartData& Part : GameInstance->GetBodyStatus().BodyParts)
	{
		if (BodyParts.Contains(Part))
		{
			if (BodyParts.Num() == 1)
			{
				EInjuryLevel NewLevel = Part.InjuryLevel == EInjuryLevel::None ? InInjuryLevel :
										Part.InjuryLevel == EInjuryLevel::Minor ? EInjuryLevel::Medium : EInjuryLevel::Major;
				Part.SetInjury(NewLevel);
				UseEnergy();
				AddFocus(InjuryFocusDecrease);
				break;
			}
			EInjuryLevel NewLevel = Part.InjuryLevel == EInjuryLevel::None ? InInjuryLevel :
									Part.InjuryLevel == EInjuryLevel::Minor ? EInjuryLevel::Medium : EInjuryLevel::Major;
			Part.SetInjury(NewLevel);
			UseEnergy();
			AddFocus(InjuryFocusDecrease);
		}
	}
		
}
void UExercise_OM::UseEnergy(float InLevel)
{
	if (EnergyNegativeHitEffect)
	{
		FGameplayEffectContextHandle Context = AbSysComp->MakeEffectContext();
		Context.AddSourceObject(this);

		const FGameplayEffectSpecHandle SpecHandle = AbSysComp->MakeOutgoingSpec(EnergyNegativeHitEffect, InLevel, Context);
		if (SpecHandle.IsValid())
		{
			AbSysComp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
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
	if (GymStats->GetEnergy() < EnergyUse)
	{
		LeaveExercise();
		return;
	}
	SetCurrentWorkoutState(EWorkoutStates::DoingRep);
	RepCount++;

	if (!bStartedSet)
		bStartedSet = true;

	if (!IsComponentTickEnabled())
		SetComponentTickEnabled(true);


	
	if (ModifyMuscleValueFunc)
	{
		ModifyMuscleValueFunc(MuscleIncrease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find modify muscle value func"));
	}
	FGymResStats& GymRes = GameInstance->GetGymResStats();
	UseEnergy();
	//GameInstance->AddGymResStats(GymRes.Energy, EnergyUse);
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


float UExercise_OM::GetEnergy() const
{
	if (GymStats)
		return GymStats->GetEnergy();
	return 0.f;
}

float UExercise_OM::GetFocus() const
{
	if (GymStats)
		return GymStats->GetFocus();
	return 0.f;
}

void UExercise_OM::LeaveExercise()
{
	SetCurrentWorkoutState(EWorkoutStates::NotInExercisePosition);

	Equipment->SetIsInteractable(true);
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
