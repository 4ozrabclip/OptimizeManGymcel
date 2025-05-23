// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Structs/PlayerData.h"
#include "GymCamera.generated.h"

UCLASS()
class OPTIMIZEMAN_API AGymCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGymCamera();
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEmotionalStateChanged(EPlayerEmotionalStates NewState);

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform DoomerTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform GrindsetTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform CopeTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform GoblinTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform GigachadTransform;

	UPROPERTY()
	class UGameInstance_OM* GameInstance;

private:
	FTransform DefaultTransform;
	


	

};
