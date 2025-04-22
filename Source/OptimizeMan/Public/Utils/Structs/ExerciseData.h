#pragma once

#include "CoreMinimal.h"
#include "ExerciseData.generated.h"

UENUM()
enum class EEquipmentTypes : uint8
{
	None = 0,
	Barbell,
	Dumbell
};

UENUM()
enum class EButtonOptions : uint8
{
	ButtonNone = 0,
	ButtonOne,
	ButtonTwo,
	ButtonThree,
};

UENUM()
enum class EWorkoutStates : uint8
{
	NotInExercisePosition = 0,
	InExercisePosition,
	DoingRep,
	SetComplete
};
UENUM(BlueprintType)
enum class EExerciseType : uint8
{
	None			UMETA(DisplayName = "None"),
	Squat			UMETA(DisplayName = "Squat"),
	OverheadPress	UMETA(DisplayName = "Overhead Press"),
	BicepCurl		UMETA(DisplayName = "Bicepcurl"),
	LeftCurl		UMETA(DisplayName = "Left Curl"),
	RightCurl		UMETA(DisplayName = "Right Curl"),
	
};