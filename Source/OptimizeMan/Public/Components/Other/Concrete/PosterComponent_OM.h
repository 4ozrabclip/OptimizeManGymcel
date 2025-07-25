// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PosterComponent_OM.generated.h"

class URectLightComponent;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UPosterComponent_OM : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPosterComponent_OM();
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

	UFUNCTION()
	void DarkModeToggle(const bool bIsDarkMode);

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	URectLightComponent* Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	UMaterial* DarkModeImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	UMaterial* LightModeImage;

	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	
};
