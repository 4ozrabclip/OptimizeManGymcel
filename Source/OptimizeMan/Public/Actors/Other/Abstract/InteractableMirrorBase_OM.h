// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor_OM.h"
#include "InteractableMirrorBase_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API AInteractableMirrorBase_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
public:
	AInteractableMirrorBase_OM();
	
    virtual void DarkModeToggle(const bool bIsDarkMode) override;


	FVector GetPlayerFacingMirrorLocation() const { return PlayerFacingMirrorLocation; }

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MirrorSystem")
	UStaticMeshComponent* MirrorGlassPlane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MirrorSystem")
	USceneCaptureComponent2D* MirrorSceneCapture;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
	FPostProcessSettings DarkPostProcess;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
	FPostProcessSettings LightPostProcess;


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector PlayerFacingMirrorLocation;
};
