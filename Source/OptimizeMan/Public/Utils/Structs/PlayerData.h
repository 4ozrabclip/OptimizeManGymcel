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
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()

	FPlayerData()
	: CurrentEmotionalState(EPlayerEmotionalStates::Cope),
	Ego(0.f),
	SexAppeal(0.f),
	Social(0.f),
	bIsDelusional(false),
	bCurrentlyOnSteroids(false),
	Money(30),
	bOwnsSteroids(false),
	bOwnsPreWorkout(false),
	bIsBulking(false),
	OverallStrength(0.f),
	Jaw(0.f),
	LowerBody(0.f),
	Calves(0.f),
	LeftArm(0.f),
	RightArm(0.f),
	Shoulders(0.f),
	bHasJawSurgery(false),
	bHasLegLengtheningSurgery(false)
	{}

	EPlayerEmotionalStates CurrentEmotionalState;

	/*
	 *	Mental Stats
	 */
	UPROPERTY(BlueprintReadWrite)
	float Ego;
	UPROPERTY(BlueprintReadWrite)
	float SexAppeal;
	UPROPERTY(BlueprintReadWrite)
	float Social;
	UPROPERTY(BlueprintReadWrite)
	bool bIsDelusional;
	UPROPERTY(BlueprintReadWrite)
	bool bCurrentlyOnSteroids;
	/*
	 * Energy, Money, Possesions
	 */
	UPROPERTY(BlueprintReadWrite)
	int Money;
	UPROPERTY(BlueprintReadWrite)
	bool bOwnsSteroids;
	UPROPERTY(BlueprintReadWrite)
	bool bOwnsPreWorkout;
	UPROPERTY(BlueprintReadWrite)
	bool bIsBulking;
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


	
	void SetStat(float& Stat, float Value)
	{
		Stat = FMath::Clamp(Value, -1.f, 1.0f);
	}
	void AddStat(float& Stat, float Value)
	{
		Stat = FMath::Clamp(Stat + Value, -1.f, 1.0f);
	}
	void SetPossesion(bool& bPossesable, const bool bInPossesion)
	{
		bPossesable = bInPossesion;
	}
	
	
	bool GetOwnsSteroids() const { return bOwnsSteroids; }
	bool GetOwnsPreWorkout() const { return bOwnsPreWorkout; }
	int GetMoney() const { return Money; }
	void SetMoney(const int InMoney)
	{
		Money += InMoney;
	}
	
	bool GetIsDelusional() const { return bIsDelusional; }
	bool GetCurrentlyOnSteroids() const { return bCurrentlyOnSteroids; }
	float GetEgo() const { return Ego; }
	float GetSexAppeal() const { return SexAppeal; }
	float GetSocial() const { return Social; }

	
};