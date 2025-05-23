// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/Player/Components/PlayerDeformationsComponent_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/GameInstance_OM.h"

UPlayerDeformationsComponent_OM::UPlayerDeformationsComponent_OM()
{
	CharacterTag = TEXT("PlayerCharacter");
	
	MassiveLowerBodySequence = nullptr;
	LargeLowerBodySequence = nullptr;
	MassiveJawSequence = nullptr;
	LargeJawSequence = nullptr;
	MassiveCalvesSequence = nullptr;
	LargeCalvesSequence = nullptr;
	MediumCalvesSequence = nullptr;
	MediumLowerBodySequence = nullptr;
	LargeLeftArmSequence = nullptr;
	LargeRightArmSequence = nullptr;
	MassiveLeftArmSequence = nullptr;
	MassiveRightArmSequence = nullptr;
}

void UPlayerDeformationsComponent_OM::BeginPlay()
{
	Super::BeginPlay();
	LoadDeformations();
}

void UPlayerDeformationsComponent_OM::LoadDeformations(const bool bResetPlayer)
{
	Super::LoadDeformations();
	
	FPlayerData& PlayerData = GameInstance->GetPlayerData();
	constexpr float MassiveThreshold = 0.9f;
	constexpr float LargeThreshold = 0.5f;
	constexpr float MediumThreshold = 0.2f;

	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (bResetPlayer)
		Player->ResetPlayer();
	
	// Jaw
	if (PlayerData.Jaw >= MassiveThreshold)
		SetDeformationForBodyPart(MassiveJawSequence, EBodyParts::Jaw);
	else if (PlayerData.Jaw >= LargeThreshold)
		SetDeformationForBodyPart(LargeJawSequence, EBodyParts::Jaw);
	else
		ClearDeformationForBodyPart(EBodyParts::Jaw);
		
	

	// Arms
	if (PlayerData.LeftArm >= MassiveThreshold)
		SetDeformationForBodyPart(MassiveLeftArmSequence, EBodyParts::LeftArm);
	else if (PlayerData.LeftArm >= LargeThreshold)
		SetDeformationForBodyPart(LargeLeftArmSequence, EBodyParts::LeftArm);
	else
		ClearDeformationForBodyPart(EBodyParts::LeftArm);
	if (PlayerData.RightArm >= MassiveThreshold)
		SetDeformationForBodyPart(MassiveRightArmSequence, EBodyParts::RightArm);
	else if (PlayerData.RightArm >= LargeThreshold)
		SetDeformationForBodyPart(LargeRightArmSequence, EBodyParts::RightArm);
	else
		ClearDeformationForBodyPart(EBodyParts::RightArm);
	
	// LowerBody
	if (PlayerData.LowerBody >= MassiveThreshold)
		SetDeformationForBodyPart(MassiveLowerBodySequence, EBodyParts::LowerBody);
	else if (PlayerData.LowerBody >= LargeThreshold)
		SetDeformationForBodyPart(LargeLowerBodySequence, EBodyParts::LowerBody);
	else if (PlayerData.LowerBody >= MediumThreshold)
		SetDeformationForBodyPart(MediumLowerBodySequence, EBodyParts::LowerBody);
	else
		ClearDeformationForBodyPart(EBodyParts::LowerBody);
	// Calves
	if (PlayerData.Calves >= MassiveThreshold)
		SetDeformationForBodyPart(MassiveCalvesSequence, EBodyParts::Calves);
	else if (PlayerData.Calves >= LargeThreshold)
		SetDeformationForBodyPart(LargeCalvesSequence, EBodyParts::Calves);
	else if (PlayerData.Calves >= MediumThreshold)
		SetDeformationForBodyPart(MediumCalvesSequence, EBodyParts::Calves);
	else
		ClearDeformationForBodyPart(EBodyParts::Calves);
}

