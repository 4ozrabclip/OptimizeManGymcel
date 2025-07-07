// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PostProcessController_OM.generated.h"

class UGameInstance_OM;
class IPersistentStateProvider_OM;

UCLASS(Blueprintable)
class OPTIMIZEMANCORE_API APostProcessController_OM : public AActor
{
	GENERATED_BODY()
public:
	APostProcessController_OM();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckDarkMode();
	UFUNCTION()
	void SetDarkMode(bool bDark);

	UPROPERTY()
	UGameInstance_OM* GameInstance;

protected:
	UPROPERTY(EditInstanceOnly, Category="PostProcess")
	APostProcessVolume* GlobalPostProcessVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PostProcessing)
	UMaterialInterface* DarkModeMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PostProcessing)
	UMaterialInterface* LightModeMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* DarkModeMID;
	UPROPERTY()
	UMaterialInstanceDynamic* LightModeMID;


};
