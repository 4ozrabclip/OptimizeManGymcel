// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InfoSign_OM.generated.h"

UCLASS()
class OPTIMIZEMAN_API AInfoSign_OM : public AActor
{
	GENERATED_BODY()
public:
	AInfoSign_OM();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* StaticMesh;



	
};
