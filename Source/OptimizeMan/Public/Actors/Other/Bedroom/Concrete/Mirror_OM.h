// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Both/Abstract/InteractableMirrorBase_OM.h"
#include "Mirror_OM.generated.h"

/**
 * 
 */

class UGameAudio_OM;

UCLASS()
class OPTIMIZEMAN_API AMirror_OM : public AInteractableMirrorBase_OM
{
	GENERATED_BODY()

public:
	AMirror_OM();

	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;

	virtual void DarkModeToggle(const bool bIsDarkMode) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* ExtraCollider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MirrorAudio")
	UGameAudio_OM* MirrorAudio;



protected:

	UPROPERTY()
	class UMirrorWidget_OM* MirrorWidget;



	
private:
	FTransform OriginalTransform;

	FRotator LockedCameraRotation;
	
	bool bOriginalMouseVisibility;
	bool bOriginalMouseLockMode;
	FTimerHandle CameraForceLookTimerHandle;

	
};
