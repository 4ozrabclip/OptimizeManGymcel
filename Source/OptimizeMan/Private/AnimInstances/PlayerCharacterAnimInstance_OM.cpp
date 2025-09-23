// Copyright © 2025 4ozStudio. All rights reserved.


#include "AnimInstances/PlayerCharacterAnimInstance_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Game/Persistent/GameInstance_OM.h"

void UPlayerCharacterAnimInstance_OM::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	bUseMultiThreadedAnimationUpdate = false;
	Player = Cast<APlayerCharacter_OM>(TryGetPawnOwner());

	bIsWalking = false;
	bIsJumping = false;
	bIsInSquatPosition = false;
	bIsSquatting = false;
	bHasInjury = false;
	bHasJawSurgery = true;
	bIsInLeftCurlPosition = false;
	bIsInRightCurlPosition = false;
	bIsLeftCurling = false;
	bIsRightCurling = false;

	if (!Player) return;
	if (UGameInstance_OM* GI = Player->GetWorld()->GetGameInstance<UGameInstance_OM>())
	{
		Thigh_Left = *GI->FindBodyPart(EBodyPart::Thigh, EBodyPartSide::Left);
		Thigh_Right = *GI->FindBodyPart(EBodyPart::Thigh, EBodyPartSide::Right);
		Arm_Left = *GI->FindBodyPart(EBodyPart::Arm, EBodyPartSide::Left);
		Arm_Right = *GI->FindBodyPart(EBodyPart::Arm, EBodyPartSide::Right);
	}

}

void UPlayerCharacterAnimInstance_OM::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Player && GetWorld() && !GetWorld()->IsPaused())
	{
		if (CurrentPlayMode != EPlayModes::WorkoutMode)
		{
			bIsWalking = Player->GetIsWalking();
			bIsJumping = Player->GetIsJumping();
		}
		else
		{
			CurrentWorkoutState = Player->GetWorkoutState();

			CurrentExerciseType = Player->GetCurrentExerciseType();
		}
	}
}

bool UPlayerCharacterAnimInstance_OM::GetIsInSquatPosition() const
{
	return bIsInSquatPosition;
}


void UPlayerCharacterAnimInstance_OM::SetIsInSquatPosition(const bool InIsInSquatPosition)
{

	if (InIsInSquatPosition)
	{
		UE_LOG(LogTemp, Error, TEXT("Set is in squat position true")); 
		bIsInCurlPosition = false;
		bIsInOverheadPressPosition = false;
		bIsInLeftCurlPosition = false;
		bIsInRightCurlPosition = false;
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Set is in squat position false"));
	}
	bIsInSquatPosition = InIsInSquatPosition;

}

void UPlayerCharacterAnimInstance_OM::SetIsInCurlPosition(const bool InIsInCurlPosition)
{
	if (InIsInCurlPosition)
	{
		bIsInSquatPosition = false;
		bIsInOverheadPressPosition = false;
		bIsInLeftCurlPosition = false;
		bIsInRightCurlPosition = false;
	}
	bIsInCurlPosition = InIsInCurlPosition;
}

void UPlayerCharacterAnimInstance_OM::SetIsInOverheadPressPosition(bool InIsInOverheadPressPosition)
{
	if (InIsInOverheadPressPosition)
	{
		bIsInSquatPosition = false;
		bIsInCurlPosition = false;
		bIsInLeftCurlPosition = false;
		bIsInRightCurlPosition = false;
	}
	bIsInOverheadPressPosition = InIsInOverheadPressPosition;
}

void UPlayerCharacterAnimInstance_OM::SetIsInLeftCurlPosition(bool InIsInLeftCurlPosition)
{
	if (InIsInLeftCurlPosition)
	{
		bIsInSquatPosition = false;
		bIsInCurlPosition = false;
		bIsInOverheadPressPosition = false;
		bIsInRightCurlPosition = false;

	}
	bIsInLeftCurlPosition = InIsInLeftCurlPosition;
}

void UPlayerCharacterAnimInstance_OM::SetIsInRightCurlPosition(bool InIsInRightCurlPosition)
{
	if (InIsInRightCurlPosition)
	{
		bIsInSquatPosition = false;
		bIsInCurlPosition = false;
		bIsInOverheadPressPosition = false;
		bIsInLeftCurlPosition = false;
	}
	bIsInRightCurlPosition = InIsInRightCurlPosition;
}

void UPlayerCharacterAnimInstance_OM::EnterSquatPosition()
{
	bIsInSquatPosition = true;
	bIsSquatting = false;
}

void UPlayerCharacterAnimInstance_OM::DoRepAnim(bool& InIsRepping, bool& InIsInPosition, float AnimDuration)
{
	UE_LOG(LogTemp, Error, TEXT("DO Rep Anim"));
	if (!InIsInPosition)
	{
		UE_LOG(LogTemp, Error, TEXT("Set is in pos false"));
		return;
	}
	if (InIsRepping)
	{
		UE_LOG(LogTemp, Error, TEXT("already repping"));
		return;
	}

	InIsRepping = true;
	UE_LOG(LogTemp, Display, TEXT("IN IS REPPING"));

	GetWorld()->GetTimerManager().ClearTimer(RepAnimTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RepAnimTimerHandle, [this, &InIsRepping]()
	{
		InIsRepping = false;
	}, AnimDuration, false);
}

void UPlayerCharacterAnimInstance_OM::ExitPosition(bool& InIsRepping, bool& InIsInPosition)
{
	InIsRepping = false;
	InIsInPosition = false;

	if (RepAnimTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RepAnimTimerHandle);
	}
}
