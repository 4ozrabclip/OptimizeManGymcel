// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InfoSign_OM.generated.h"

class UTutorialWidget_OM;
class APlayerCharacter_OM;

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
	UFUNCTION()
	void OnTutorialOff();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	UTutorialWidget_OM* TutorialWidget;


private:
	UPROPERTY(EditAnywhere, Category = "Motion")
	float Amplitude = 20.f;
	UPROPERTY(EditAnywhere, Category = "Motion")
	float Frequency = 1.f;

	FVector InitialLocation;

	UPROPERTY()
	APlayerCharacter_OM* Player;

	
	
	
};
