#pragma once

#include "CoreMinimal.h"
#include "SocialData.generated.h"

UENUM(BlueprintType)
enum class ESocialType : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Friendly UMETA(DisplayName = "Friendly"),
	Randy UMETA(DisplayName = "Randy"),
	Angry UMETA(DisplayName = "Angry"),
	DontListen UMETA(DisplayName = "NoListen"),
	Funny UMETA(DisplayName = "Funny"),
	Hilarious UMETA(DisplayName = "Hilarious"),
	WeirdJoke UMETA(DisplayName = "Weird Joke"),
	Awkward UMETA(DisplayName = "Awkward"),
	Flexing UMETA(DisplayName = "Flexing")
};
UENUM(BlueprintType)
enum class ENpcMood : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Happy UMETA(DisplayName = "Happy"),
	Angry UMETA(DisplayName = "Angry"),
	Randy UMETA(DisplayName = "Randy"),
	Uncomfortable UMETA(DisplayName = "Uncomfortable"),
	Disgusted UMETA(DisplayName = "Disgusted")
	
};
UENUM(BlueprintType)
enum class ENpcRelationshipState : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Friend UMETA(DisplayName = "Friend"),
	Enemy UMETA(DisplayName = "Enemy"),
	HatesYou UMETA(DisplayName = "HatesYou")
};
USTRUCT()
struct FNpcRelationship
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FName NpcIdentifier;

	UPROPERTY(EditAnywhere)
	bool bHasMetPlayer = false;

	UPROPERTY(EditAnywhere)
	float FriendshipLevel = 0.f;

	UPROPERTY(VisibleAnywhere)
	ENpcRelationshipState RelationshipState = ENpcRelationshipState::Neutral;
	
	FORCEINLINE void UpdateRelationshipState()
	{
		if (FriendshipLevel > 0.4f)
			RelationshipState = ENpcRelationshipState::Friend;
		else if (FriendshipLevel < -0.8f)
			RelationshipState = ENpcRelationshipState::HatesYou;
		else if (FriendshipLevel < -0.5f)
			RelationshipState = ENpcRelationshipState::Enemy;
		else
			RelationshipState = ENpcRelationshipState::Neutral;
	}
};

USTRUCT()
struct FDialogueCondition
{
	GENERATED_BODY()

	UPROPERTY()
	ENpcMood Mood;
	  
	UPROPERTY()
	float FriendshipThreshold;

	FDialogueCondition()
	{
		Mood = ENpcMood::Neutral;
		FriendshipThreshold = 0.f;
	}
	FDialogueCondition(const ENpcMood InMood, const float InFriendshipThreshold)
	{
		Mood = InMood;
		FriendshipThreshold = InFriendshipThreshold;
	}
	
	bool operator==(const FDialogueCondition& Other) const
	{
		return Mood == Other.Mood && FriendshipThreshold == Other.FriendshipThreshold;
	}

	friend uint32 GetTypeHash(const FDialogueCondition& Condition)
	{
		return HashCombine(GetTypeHash(static_cast<uint8>(Condition.Mood)), 
						  GetTypeHash(Condition.FriendshipThreshold));
	}
};

