// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Character/Abstract/BodyDeformationsComponent_OM.h"
#include "PlayerDeformationsComponent_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UPlayerDeformationsComponent_OM : public UBodyDeformationsComponent_OM
{
	GENERATED_BODY()
public:
	UPlayerDeformationsComponent_OM();
	virtual void BeginPlay() override;
	virtual void LoadDeformations(const bool bResetPlayer = false) override;
	
protected: // Deformation Sequences
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* MassiveJawSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* LargeJawSequence;

	// ------legs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* MassiveLowerBodySequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* LargeLowerBodySequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* MediumLowerBodySequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* MassiveCalvesSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* LargeCalvesSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* MediumCalvesSequence;

	// -------arms
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* MassiveLeftArmSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* LargeLeftArmSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* MassiveRightArmSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DeformerSequencers")
	ULevelSequence* LargeRightArmSequence;

};
