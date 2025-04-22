// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneObjectBindingID.h"
#include "Actors/Characters/Components/CharacterComponentBase_OM.h"
#include "BodyDeformationsComponent_OM.generated.h"

class ULevelSequence;

UENUM()
enum class EBodyParts : uint8
{
	Jaw,
	LeftArm,
	RightArm,
	LowerBody,
	Calves
};
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPTIMIZEMAN_API UBodyDeformationsComponent_OM : public UCharacterComponentBase_OM
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

protected:
	virtual void LoadDeformations(const bool bResetPlayer = false);
	void ClearDeformationForBodyPart(EBodyParts BodyPart);
	virtual void SetDeformationForBodyPart(ULevelSequence* InDeformationSequence, EBodyParts BodyPart);
	virtual void SetDeformation(ULevelSequence* InDeformationSequence);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Sequence Tag")
	FString CharacterTag;


private:
	struct FBodyPartSequence
	{
		class ALevelSequenceActor* SequenceActor = nullptr;
		class ULevelSequencePlayer* SequencePlayer = nullptr;
		TArray<FMovieSceneObjectBindingID> BindingIDs;
	};
	
	TMap<EBodyParts, FBodyPartSequence> ActiveSequences;
};
