// Copyright © 2025 4ozStudio. All rights reserved.


#include "AnimInstances/PlayerCharacterAnimInstance_OMG.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"

void UPlayerCharacterAnimInstance_OMG::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Player = Cast<APlayerCharacter_OM>(TryGetPawnOwner());
	
	bIsInSquatPosition = false;
	bIsSquatting = false;
	bHasSquatInjury1 = false;
	bHasJawSurgery = true;
	bIsInLeftCurlPosition = false;
	bIsInRightCurlPosition = false;
	bIsLeftCurling = false;
	bIsRightCurling = false;
}

void UPlayerCharacterAnimInstance_OMG::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

bool UPlayerCharacterAnimInstance_OMG::GetIsInSquatPosition() const
{
	return bIsInSquatPosition;
}


void UPlayerCharacterAnimInstance_OMG::SetIsInSquatPosition(const bool InIsInSquatPosition)
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

void UPlayerCharacterAnimInstance_OMG::SetIsInCurlPosition(const bool InIsInCurlPosition)
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

void UPlayerCharacterAnimInstance_OMG::SetIsInOverheadPressPosition(bool InIsInOverheadPressPosition)
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

void UPlayerCharacterAnimInstance_OMG::SetIsInLeftCurlPosition(bool InIsInLeftCurlPosition)
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

void UPlayerCharacterAnimInstance_OMG::SetIsInRightCurlPosition(bool InIsInRightCurlPosition)
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

void UPlayerCharacterAnimInstance_OMG::EnterSquatPosition()
{
	bIsInSquatPosition = true;
	bIsSquatting = false;
}

void UPlayerCharacterAnimInstance_OMG::DoRepAnim(bool& InIsRepping, bool& InIsInPosition, float AnimDuration)
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

void UPlayerCharacterAnimInstance_OMG::ExitPosition(bool& InIsRepping, bool& InIsInPosition)
{
	InIsRepping = false;
	InIsInPosition = false;

	if (RepAnimTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RepAnimTimerHandle);
	}
}
