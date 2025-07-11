// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/PlayerDeformationsComponent_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"

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
	
	FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();
	
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (bResetPlayer)
		Player->ResetPlayer();

	for (const FBodyPartData& BodyPart : BodyStatus.BodyParts)
	{
		constexpr float MassiveThreshold = 0.9f;
		constexpr float LargeThreshold = 0.5f;
		constexpr float MediumThreshold = 0.2f;
		const float Strength = BodyPart.Strength;
		const EBodyPartSide Side = BodyPart.Side;
		switch (BodyPart.Part)
		{
			case EBodyPart::Jaw:
			{
				if (Strength >= MassiveThreshold)
					SetDeformationForBodyPart(MassiveJawSequence, BodyPart);
				else if (Strength >= LargeThreshold)
					SetDeformationForBodyPart(LargeJawSequence, BodyPart);
				else
					ClearDeformationForBodyPart(BodyPart);
				break;
			}
			case EBodyPart::Arm:
			{
				if (Side == EBodyPartSide::Left)
				{
					if (Strength >= MassiveThreshold)
						SetDeformationForBodyPart(MassiveLeftArmSequence, BodyPart);
					else if (Strength >= LargeThreshold)
						SetDeformationForBodyPart(LargeLeftArmSequence, BodyPart);
					else
						ClearDeformationForBodyPart(BodyPart);
				}
				else if (Side == EBodyPartSide::Right)
				{
					if (Strength >= MassiveThreshold)
						SetDeformationForBodyPart(MassiveRightArmSequence, BodyPart);
					else if (Strength >= LargeThreshold)
						SetDeformationForBodyPart(LargeRightArmSequence, BodyPart);
					else
						ClearDeformationForBodyPart(BodyPart);
				}
				break;
			}
			case EBodyPart::Thigh:
			{
				if (Strength >= MassiveThreshold)
					SetDeformationForBodyPart(MassiveLowerBodySequence, BodyPart);
				else if (Strength >= LargeThreshold)
					SetDeformationForBodyPart(LargeLowerBodySequence, BodyPart);
				else if (Strength >= MediumThreshold)
					SetDeformationForBodyPart(MediumLowerBodySequence, BodyPart);
				else
					ClearDeformationForBodyPart(BodyPart);
				break;
			}
			case EBodyPart::Calve:
			{
				if (Strength >= MassiveThreshold)
					SetDeformationForBodyPart(MassiveCalvesSequence, BodyPart);
				else if (Strength >= LargeThreshold)
					SetDeformationForBodyPart(LargeCalvesSequence, BodyPart);
				else if (Strength >= MediumThreshold)
					SetDeformationForBodyPart(MediumCalvesSequence, BodyPart);
				else
					ClearDeformationForBodyPart(BodyPart);
				break;
			}
			default:
				break;
		}
	}
}

