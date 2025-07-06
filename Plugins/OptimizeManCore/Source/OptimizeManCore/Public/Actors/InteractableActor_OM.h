// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "InteractableActor_OM.generated.h"


class UTodoManagementSubsystem;
class UGameInstance_OM;
class APlayerController_OM;
class APlayerCharacterBase_OM;

UCLASS(Blueprintable)
class OPTIMIZEMANCORE_API AInteractableActor_OM : public AActor, public IInteractableInterface_OM
{
	GENERATED_BODY()
public:	
	AInteractableActor_OM();
protected:
	/** Class Overrides **/
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
	
public:
	virtual void Interact_Implementation() override {};

	UFUNCTION()
	virtual void CheckAndSetDarkMode(bool bIsDarkMode) {};

protected:
	/** Cache **/
	UPROPERTY()
	APlayerCharacterBase_OM* Player;
	UPROPERTY()
	APlayerController_OM* PlayerController;
	UPROPERTY()
	UGameInstance_OM* GameInstance;

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