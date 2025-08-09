// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OptimizeMan/Public/Interfaces/InteractableInterface_OM.h"
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
	UFUNCTION()
	virtual void DarkModeToggle(const bool bIsDarkMode) {}


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