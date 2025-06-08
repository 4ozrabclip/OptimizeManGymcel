// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/Components/BodyDeformationsComponent_OM.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneObjectBindingID.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Utils/GameInstance_OM.h"



void UBodyDeformationsComponent_OM::BeginPlay()
{
	Super::BeginPlay();
}

void UBodyDeformationsComponent_OM::LoadDeformations(const bool bResetPlayer)
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldnt load game instance in bodydeformationscomponent"));
		return;
	}
}
void UBodyDeformationsComponent_OM::ClearDeformationForBodyPart(const FBodyPartData BodyPart)
{
	if (FBodyPartSequence* BodyPartSequence = ActiveSequences.Find(BodyPart))
	{
		if (BodyPartSequence->SequencePlayer)
		{
			BodyPartSequence->SequencePlayer->Stop();
		}
        
		if (BodyPartSequence->SequenceActor)
		{
			for (const FMovieSceneObjectBindingID& BindingID : BodyPartSequence->BindingIDs)
			{
				BodyPartSequence->SequenceActor->RemoveBinding(BindingID, GetOwner());
			}
			BodyPartSequence->SequenceActor->Destroy();
		}
		ActiveSequences.Remove(BodyPart);
	}
}

void UBodyDeformationsComponent_OM::SetDeformation(ULevelSequence* InDeformationSequence)
{
	if (!InDeformationSequence)
		return;
	
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.bAutoPlay = true;

	ALevelSequenceActor* SequenceActor = nullptr;
	ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
	   GetWorld(),
	   InDeformationSequence,
	   PlaybackSettings,
	   SequenceActor
	);

	if (!SequencePlayer)
		return;
	if (!SequenceActor)
		return;

	FName CharacterBindingTag = FName(*CharacterTag);
	TArray<FMovieSceneObjectBindingID> BindingIDArray = InDeformationSequence->FindBindingsByTag(CharacterBindingTag);

	if (BindingIDArray.Num() > 0)
	{
		for (FMovieSceneObjectBindingID BindingID : BindingIDArray)
		{
			SequenceActor->AddBinding(BindingID, GetOwner(), true);
		}
		SequencePlayer->Play();
	}
	else
	{
		return;
	}
	if (SequencePlayer->IsPlaying())
	{
		UE_LOG(LogTemp, Error, TEXT("Sequence playing"));
	}
}

void UBodyDeformationsComponent_OM::SetDeformationForBodyPart(ULevelSequence* InDeformationSequence, const FBodyPartData BodyPart)
{
	ClearDeformationForBodyPart(BodyPart);
    
	if (!InDeformationSequence)
	{
		UE_LOG(LogTemp, Error, TEXT("Sequence that you inputted is null"));
		return;
	}
    
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.bAutoPlay = true;

	ALevelSequenceActor* SequenceActor = nullptr;
	ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(),
		InDeformationSequence,
		PlaybackSettings,
		SequenceActor
	);

	if (!SequencePlayer || !SequenceActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create sequence player or actor"));
		return;
	}

	FName CharacterBindingTag = FName(*CharacterTag);
	TArray<FMovieSceneObjectBindingID> BindingIDArray = InDeformationSequence->FindBindingsByTag(CharacterBindingTag);

	FBodyPartSequence& BodyPartSequence = ActiveSequences.FindOrAdd(BodyPart);
	BodyPartSequence.SequenceActor = SequenceActor;
	BodyPartSequence.SequencePlayer = SequencePlayer;
	BodyPartSequence.BindingIDs.Empty(); 
    
	if (BindingIDArray.Num() > 0)
	{
		for (FMovieSceneObjectBindingID BindingID : BindingIDArray)
		{
			UE_LOG(LogTemp, Error, TEXT("Found binding"));
			SequenceActor->AddBinding(BindingID, GetOwner(), true);
			BodyPartSequence.BindingIDs.Add(BindingID);
		}
		SequencePlayer->Play();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Havent set binding id on the sequence"));
	}
}
