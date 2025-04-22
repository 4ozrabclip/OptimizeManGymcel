// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poster_OM.generated.h"

class URectLightComponent;
class UPosterComponent_OM;
UCLASS()
class OPTIMIZEMAN_API APoster_OM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoster_OM();
	virtual void BeginPlay() override;
	void CheckOwnedPosters();

	UFUNCTION(BlueprintCallable)
	void CheckAndSetDarkMode();

protected:
	// Called when the game starts or when spawned
	void SetVisibilityOfPoster(UPosterComponent_OM* InPoster, bool InIsOwned);

	/*void SetDarkModeForOwnedPoster(UStaticMeshComponent* InPoster, URectLightComponent* InLight,
	                               UMaterial* InDarkPicture,
	                               UMaterial* InLightPicture);
	UFUNCTION(BlueprintCallable)
	void CheckAndSetDarkMode();*/

	UPROPERTY()
	class UGameInstance_OM* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poster")
	UPosterComponent_OM* ChadPoster1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poster")
	UPosterComponent_OM* ChadPoster2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poster")
	UPosterComponent_OM* ChadPoster3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poster")
	UPosterComponent_OM* WaifuPoster1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poster")
	UPosterComponent_OM* WaifuPoster2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poster")
	UPosterComponent_OM* WaifuPoster3;

	



private:
	TArray<bool> OwnedChadPosters;
	TArray<bool> OwnedWaifuPosters;

	const int NumberOfWaifuPosters = 3;
	const int NumberOfChadPosters = 3;
};
