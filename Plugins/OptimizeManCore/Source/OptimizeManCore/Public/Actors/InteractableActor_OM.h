// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "InteractableActor_OM.generated.h"



UCLASS(Blueprintable)
class OPTIMIZEMAN_API AInteractableActor_OM : public AActor, public IInteractableInterface_OM
{
	GENERATED_BODY()
public:	
	AInteractableActor_OM();
protected:
	/** Class Overrides **/
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Interact_Implementation() override {};


public:	
	/** Components **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AuraLight")
	class UPointLightComponent* AuraLight;


	/** Interactable Widget **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText InteractableText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractableWidget;
};