// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "InteractableActor_OM.generated.h"


class APlayerController_OM;

UCLASS(Blueprintable)
class OPTIMIZEMAN_API AInteractableActor_OM : public AActor, public IInteractableInterface_OM
{
	GENERATED_BODY()
public:	
	AInteractableActor_OM();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY()
	APlayerController_OM* PlayerController;

	UPROPERTY()
	class APlayerCharacter_OM* Player;

	UPROPERTY()
	class UGameInstance_OM* GameInstance;

	UPROPERTY()
	class UTodoManagementSubsystem* TodoManager;

public:	
	virtual void Interact_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AuraLight")
	class UPointLightComponent* AuraLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText InteractableText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractableWidget;
};