// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Characters/NPC/Abstract/FemaleBase_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Character/Concrete/NPCBodyDeformationsComponent_OM.h"

void AFemaleBase_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInDialogue)
	{
		if (!bHasMogFace && DeformationComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Load deformations 1"));
			DeformationComponent->LoadDeformations();
			bHasMogFace = true;

			if (Player)
				Player->SetCurrentInteractedCharacter(this);
		}
	}
}
