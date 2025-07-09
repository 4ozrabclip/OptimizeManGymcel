// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Abstract/InteractableActor_OM.h"
#include "GameFramework/Actor.h"
#include "Shelf_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AShelf_OM : public AInteractableActor_OM
{
	GENERATED_BODY()

public:
	AShelf_OM();

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;

	
	UFUNCTION(BlueprintCallable, Category = "Shelf")
	void UpdateShelfItems() const;


	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShelfItem")
	UStaticMeshComponent* SteroidsMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShelfItem")
	UStaticMeshComponent* PreWorkoutMesh;
	
	
	
};
