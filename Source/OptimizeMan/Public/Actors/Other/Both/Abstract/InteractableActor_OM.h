// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Structs/PlayModes.h"
#include "OptimizeMan/Public/Interfaces/InteractableInterface_OM.h"
#include "InteractableActor_OM.generated.h"


class APlayerController_OM;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, TSubclassOf<UUserWidget>, InWidget);

UCLASS(Blueprintable)
class OPTIMIZEMAN_API AInteractableActor_OM : public AActor, public IInteractableInterface_OM
{
	GENERATED_BODY()
public:	
	AInteractableActor_OM();
protected:
	/** Native Overrides **/
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;

	
	/** Bound Event Functions **/
	virtual void OnPlayModeChanged(EPlayModes InPlayMode) {};
	UFUNCTION()
	virtual void DarkModeToggle(const bool bIsDarkMode) {}


	/** Getters **/
	bool GetIsInteractable() const { return InteractableInterfaceProperties.bIsInteractable; }


	/** Events/Delegates **/
	UPROPERTY(VisibleAnywhere, Category = Events)
	FOnInteract OnInteract;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> WidgetClass;

	/** Class Cache **/	
	UPROPERTY()
	APlayerController_OM* PlayerController;

	UPROPERTY()
	class APlayerCharacter_OM* Player;

	UPROPERTY()
	class UGameInstance_OM* GameInstance;

	UPROPERTY()
	class UTodoManagementSubsystem* TodoManager;

public:	

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AuraLight")
	class UPointLightComponent* AuraLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText InteractableText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractableWidget;
};