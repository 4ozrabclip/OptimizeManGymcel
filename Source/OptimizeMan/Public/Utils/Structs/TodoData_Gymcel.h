#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TodoData_Gymcel.generated.h"

UENUM(BlueprintType)
enum ETodoArrayList : uint8
{
	CompleteWorkout = 0,
	BuySomething,
	TalkToAGirl,
	BuySteroids,
	MakeSomeoneLikeYou,
	HitTenSquats,
	StartBulking,
	GetARealGirlfriend
};
