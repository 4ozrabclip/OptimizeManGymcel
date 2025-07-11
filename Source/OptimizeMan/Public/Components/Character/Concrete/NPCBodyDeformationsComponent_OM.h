// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/Abstract/BodyDeformationsComponent_OM.h"
#include "NPCBodyDeformationsComponent_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UNPCBodyDeformationsComponent_OM : public UBodyDeformationsComponent_OM
{
	GENERATED_BODY()
public:
	UNPCBodyDeformationsComponent_OM();
	virtual void LoadDeformations(const bool bResetPlayer = false) override;

protected: // Deformation Sequences
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deformations")
	ULevelSequence* MogDeformTransition_1;

	
};
