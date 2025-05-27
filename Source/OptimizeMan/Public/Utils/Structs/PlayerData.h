#pragma once
#include "CoreMinimal.h"
#include "PlayerData.generated.h"

UENUM(BlueprintType)
enum EPlayerStatTypes : uint8
{
	Ego = 0,
	SexAppeal,
	Social
};

UENUM(BlueprintType)
enum EPlayerEmotionalStates : uint8
{
	Doomer,
	Cope,
	Grindset,
	Gigachad,
	GoblinMode
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


USTRUCT(BlueprintType)
struct FBodyStatus
{
	GENERATED_USTRUCT_BODY()

	FBodyStatus()
	: OverallStrength(0.f),
	Jaw(0.f),
	LowerBody(0.f),
	Calves(0.f),
	LeftArm(0.f),
	RightArm(0.f),
	Shoulders(0.f),
	bHasJawSurgery(false),
	bHasLegLengtheningSurgery(false),
	bCurrentlyOnSteroids(false),
	bIsBulking(false)
	{}

	/*
	 *	Physical Stats
	 */
	UPROPERTY(BlueprintReadWrite)
	float OverallStrength;
	// Face
	UPROPERTY(BlueprintReadWrite)
	float Jaw;
	//	Lower
	UPROPERTY(BlueprintReadWrite)
	float LowerBody;
	UPROPERTY(BlueprintReadWrite)
	float Calves;
	// Arms
	UPROPERTY(BlueprintReadWrite)
	float LeftArm;
	UPROPERTY(BlueprintReadWrite)
	float RightArm;
	UPROPERTY(BlueprintReadWrite)
	float Shoulders;
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
	FInnerStatus()
		: CurrentEmotionalState(EPlayerEmotionalStates::Cope),
		Ego(0.f),
		SexAppeal(0.f),
		Social(0.f),
		bIsDelusional(false)
	{}

	EPlayerEmotionalStates CurrentEmotionalState;

	UPROPERTY(BlueprintReadWrite)
	float Ego;
	UPROPERTY(BlueprintReadWrite)
	float SexAppeal;
	UPROPERTY(BlueprintReadWrite)
	float Social;
	UPROPERTY(BlueprintReadWrite)
	bool bIsDelusional;



};
USTRUCT(BlueprintType)
struct FGamePointsData
{
	GENERATED_USTRUCT_BODY()

	FGamePointsData()
		: GamePoints(0.f)
	{}
	UPROPERTY(BlueprintReadWrite)
	int GamePoints;

	
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
