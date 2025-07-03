// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor_OM.h"
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
