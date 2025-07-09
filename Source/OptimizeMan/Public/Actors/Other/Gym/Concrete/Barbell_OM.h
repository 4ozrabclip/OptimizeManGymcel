// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Gym/Abstract/CompoundEquipment_OM.h"
#include "Barbell_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API ABarbell_OM : public ACompoundEquipment_OM
{
	GENERATED_BODY()
	
public:

	ABarbell_OM();

	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* ExtraCollider;

	


};
