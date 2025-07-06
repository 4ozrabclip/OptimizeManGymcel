#pragma once
#include "CoreMinimal.h"
#include "Structs/PlayerData.h"
#include "PlayerData_Gymcel.generated.h"


UENUM(BlueprintType)
enum EPlayerStatTypes : uint8
{
	Ego = 0,
	SexAppeal,
	Social
};


USTRUCT(BlueprintType)
struct FGymResStats
{
	GENERATED_USTRUCT_BODY()
	FGymResStats() :
	Energy(1.f),
	Focus(1.f),
	Bladder(0.f)
	{}
	
	UPROPERTY(BlueprintReadWrite)
	float Energy;
	UPROPERTY(BlueprintReadWrite)
	float Focus;
	UPROPERTY(BlueprintReadWrite)
	float Bladder;
	
};
UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	Jaw			UMETA(DisplayName = "Jaw"),
	Shoulder	UMETA(DisplayName = "Shoulder"),
	Arm			UMETA(DisplayName = "Arm"),
	Chest		UMETA(DisplayName = "Chest"),
	Back		UMETA(DisplayName = "Back"),
	Abdominal	UMETA(DisplayName = "Abdominal"),
	Thigh		UMETA(DisplayName = "Thigh"),
	Calve		UMETA(DisplayName = "Calve")
};
UENUM(BlueprintType)
enum class EBodyPartSide : uint8
{
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right"),
	Center	UMETA(DisplayName = "Center")
};
UENUM(BlueprintType)
enum class EInjuryLevel : uint8
{
	None	UMETA(DisplayName = "None"),
	Minor	UMETA(DisplayName = "Minor Injury"),
	Medium	UMETA(DisplayName = "Medium Injury"),
	Major	UMETA(DisplayName = "Major Injury"),
};
USTRUCT(BlueprintType)
struct FBodyPartData
{
	GENERATED_USTRUCT_BODY()
	FBodyPartData() :
	Strength(0.f),
	Part(EBodyPart::Abdominal),
	Side(EBodyPartSide::Center),
	InjuryLevel(EInjuryLevel::None)
	{}
	FBodyPartData(const EBodyPart& InPart, const EBodyPartSide& InSide) :
	Strength(0.f),
	Part(InPart),
	Side(InSide),
	InjuryLevel(EInjuryLevel::None)
	{}
	
	UPROPERTY(BlueprintReadOnly)
	float Strength;
	UPROPERTY(BlueprintReadOnly)
	EBodyPart Part;
	UPROPERTY(BlueprintReadOnly)
	EBodyPartSide Side;
	UPROPERTY(BlueprintReadOnly)
	EInjuryLevel InjuryLevel;

	void SetInjury(const EInjuryLevel& InInjuryLevel)
	{
		InjuryLevel = InInjuryLevel;
	}

	bool operator==(const FBodyPartData& Other) const
	{
		return Part == Other.Part && Side == Other.Side;
	}
};

FORCEINLINE uint32 GetTypeHash(const FBodyPartData& PartData)
{
	return HashCombine(GetTypeHash(PartData.Part), GetTypeHash(PartData.Side));
}

USTRUCT(BlueprintType)
struct FBodyStatus
{
	GENERATED_USTRUCT_BODY()

	FBodyStatus() :
	bHasJawSurgery(false),
	bHasLegLengtheningSurgery(false),
	bCurrentlyOnSteroids(false),
	bIsBulking(false)
	{
		BodyParts.Add(FBodyPartData(EBodyPart::Jaw, EBodyPartSide::Center));
		BodyParts.Add(FBodyPartData(EBodyPart::Arm, EBodyPartSide::Left));
		BodyParts.Add(FBodyPartData(EBodyPart::Arm, EBodyPartSide::Right));
		BodyParts.Add(FBodyPartData(EBodyPart::Chest, EBodyPartSide::Center));
		BodyParts.Add(FBodyPartData(EBodyPart::Back, EBodyPartSide::Center));
		BodyParts.Add(FBodyPartData(EBodyPart::Thigh, EBodyPartSide::Left));
		BodyParts.Add(FBodyPartData(EBodyPart::Thigh, EBodyPartSide::Right));
		BodyParts.Add(FBodyPartData(EBodyPart::Calve, EBodyPartSide::Left));
		BodyParts.Add(FBodyPartData(EBodyPart::Calve, EBodyPartSide::Right));
	}

	/*
	 *	Physical Stats
	 */
	UPROPERTY(BlueprintReadOnly)
	TArray<FBodyPartData> BodyParts;
	
	UPROPERTY(BlueprintReadWrite)
	bool bHasJawSurgery;
	UPROPERTY(BlueprintReadWrite)
	bool bHasLegLengtheningSurgery;
	UPROPERTY(BlueprintReadWrite)
	bool bCurrentlyOnSteroids;
	UPROPERTY(BlueprintReadWrite)
	bool bIsBulking;

	
};
USTRUCT(BlueprintType)
struct FInnerStatus
{
	GENERATED_USTRUCT_BODY()
	FInnerStatus() :
		Ego(0.f),
		SexAppeal(0.f),
		Social(0.f)
	{}
	
	UPROPERTY(BlueprintReadWrite)
	float Ego;
	UPROPERTY(BlueprintReadWrite)
	float SexAppeal;
	UPROPERTY(BlueprintReadWrite)
	float Social;
};
USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_USTRUCT_BODY()

	FInventoryData()
		: Money(30),
		bOwnsSteroids(false),
		bOwnsPreWorkout(false)
	{}

	UPROPERTY(BlueprintReadWrite)
	int Money;
	UPROPERTY(BlueprintReadWrite)
	bool bOwnsSteroids;
	UPROPERTY(BlueprintReadWrite)
	bool bOwnsPreWorkout;
};
