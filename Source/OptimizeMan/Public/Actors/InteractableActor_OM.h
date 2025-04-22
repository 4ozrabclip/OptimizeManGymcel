// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OptimizeMan/Public/Interfaces/InteractableInterface_OM.h"
#include "InteractableActor_OM.generated.h"


UCLASS(Blueprintable)
class OPTIMIZEMAN_API AInteractableActor_OM : public AActor, public IInteractableInterface_OM
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor_OM();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY()
	APlayerController* PlayerController;

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