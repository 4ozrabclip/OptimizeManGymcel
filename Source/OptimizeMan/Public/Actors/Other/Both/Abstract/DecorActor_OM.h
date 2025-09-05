// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "NonInteractableActor_OM.h"
#include "GameFramework/Actor.h"
#include "DecorActor_OM.generated.h"

UCLASS(Abstract)
class OPTIMIZEMAN_API ADecorActor_OM : public ANonInteractableActor_OM
{
	GENERATED_BODY()
public:
	ADecorActor_OM();
protected:
	/** Overrides **/
	virtual void BeginPlay() override;

	/** UFUNCS **/
	UFUNCTION()
	virtual void OnDarkModeToggled(bool bIsDarkMode);


	/** Components **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Materials)
	UMaterial* LightModeMat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Materials)
	UMaterial* DarkModeMat;
public:
};
