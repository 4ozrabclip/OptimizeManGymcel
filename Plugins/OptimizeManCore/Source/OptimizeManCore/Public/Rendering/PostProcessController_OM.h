// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PostProcessController_OM.generated.h"

class IPersistentStateProvider_OM;

UCLASS()
class OPTIMIZEMAN_API APostProcessControllerBase_OM : public AActor
{
	GENERATED_BODY()
public:
	APostProcessControllerBase_OM();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckDarkMode();
	void SetDarkMode(bool bDark) const;

	IPersistentStateProvider_OM* Persistence;

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
