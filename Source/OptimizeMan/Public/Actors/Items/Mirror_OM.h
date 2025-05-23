// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableMirrorBase_OM.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* ExtraCollider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MirrorAudio")
	UGameAudio_OM* MirrorAudio;

	UFUNCTION(BlueprintCallable)
	void UpdateStats();


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
