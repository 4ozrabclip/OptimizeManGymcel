// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor_OM.h"
#include "Calender_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ACalender_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
public:
	ACalender_OM();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Dark/Light Mode")
	void CheckAndSetDarkMode();
	void SetCalenderImage();

	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	class URectLightComponent* Light;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* JanuaryMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* JanuaryMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* FebruaryMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* FebruaryMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* MarchMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* MarchMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* AprilMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* AprilMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* MayMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* MayMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* JuneMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* JuneMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* JulyMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* JulyMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* AugustMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* AugustMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* SeptemberMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* SeptemberMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* OctoberMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* OctoberMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* NovemberMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* NovemberMaterialDarkMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* DecemberMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	UMaterial* DecemberMaterialDarkMode;
	
	
};
