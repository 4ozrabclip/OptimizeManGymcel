#pragma once

#include "CoreMinimal.h"
#include "ExerciseData.generated.h"

UENUM()
enum class EWeightClass
{
	Light_A UMETA(DisplayName = "Light_A"),
	Light_B UMETA(DisplayName = "Light_B"),
	Light_C UMETA(DisplayName = "Light_C"),
	Medium_A UMETA(DisplayName = "Medium_A"),
	Medium_B UMETA(DisplayName = "Medium_B"),
	Medium_C UMETA(DisplayName = "Medium_C"),
	Heavy_A UMETA(DisplayName = "Heavy_A"),
	Heavy_B UMETA(DisplayName = "Heavy_B"),
	Heavy_C UMETA(DisplayName = "Heavy_C")
};

USTRUCT(Blueprintable)
struct FEquipmentData
{
	GENERATED_USTRUCT_BODY()
	FEquipmentData() :
	WeightClass(EWeightClass::Light_A),
	EquipmentMesh(nullptr)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeightClass WeightClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* EquipmentMesh;
};
UENUM()
enum class EEquipmentTypes : uint8
{
	None = 0,
	Barbell,
	Dumbell,
	Dipbar,
	Legpress
};

UENUM()
enum class EButtonOptions : uint8
{
	ButtonNone = 0,
	ButtonOne,
	ButtonTwo,
	ButtonThree,
};

UENUM(BlueprintType)
enum class EWorkoutStates : uint8
{
	NotInExercisePosition = 0,
	Entry,
	InExercisePosition,
	DoingRep,
	PostRep,
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
	ChestDip		UMETA(DisplayName = "Chest Dip"),
	LegPress		UMETA(DisplayName = "Leg Press"),
	
};