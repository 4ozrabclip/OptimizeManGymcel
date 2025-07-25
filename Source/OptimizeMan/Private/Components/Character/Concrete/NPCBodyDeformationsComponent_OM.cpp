// Copyright © 2025 4ozStudio. All rights reserved.


#include "Components/Character/Concrete/NPCBodyDeformationsComponent_OM.h"

UNPCBodyDeformationsComponent_OM::UNPCBodyDeformationsComponent_OM()
{
	CharacterTag = TEXT("NPC");
	
	MogDeformTransition_1 = nullptr;
}

void UNPCBodyDeformationsComponent_OM::LoadDeformations(const bool bResetPlayer)
{
	Super::LoadDeformations();

	UE_LOG(LogTemp, Display, TEXT("Load Deformation called for npc 2"));
	if (MogDeformTransition_1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Load Deformation called for npc 3"));
		SetDeformation(MogDeformTransition_1);
	}
}
