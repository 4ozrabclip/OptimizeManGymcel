// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/GameInstance_OM.h"
#include "Utils/Structs/EventAndGPData.h"
#include "Utils/Structs/PlayerData_Gymcel.h"
#include "GameInstance_OMG.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGymStatsChanged);

class APoster_OM;
UCLASS()
class OPTIMIZEMAN_API UGameInstance_OMG : public UGameInstance_OM
{
	GENERATED_BODY()
public:
	/** Overrides **/
	virtual void Init() override;
	
	virtual void InitializePlayerData() override;
	virtual void InitializePostersOwned() override;
	virtual void InitializeGameSettings() override;

	virtual void ResetGame() override;

	

	/** Finders/Getters **/
	UFUNCTION(BlueprintCallable)
	FGymResStats& GetGymResStats() { return GymResStats; }
	UFUNCTION()
	FBodyStatus& GetBodyStatus() { return BodyStatus;}

	FBodyPartData* FindBodyPart(const EBodyPart& Part, const EBodyPartSide& Side);
	float GetBodyPartStrengthValue(const EBodyPart& Part, const EBodyPartSide& Side);
	float GetBodyPartLeftRightCombinedStrengthValue(const EBodyPart& Part);
	float* GetBodyPartStrengthPtr(const EBodyPart& Part, const EBodyPartSide& Side);
	bool GetCurrentlyOnSteroids() const { return BodyStatus.bCurrentlyOnSteroids; }
	TArray<bool> GetOwnedWaifuPosters() { return bOwnsWaifuPosters;}
	TArray<bool> GetOwnedChadPosters() { return bOwnsChadPosters;}


	bool GetHasBeenToGymToday() const { return bHasBeenToGymToday; }

	/** Setters/Adders **/
	UFUNCTION()
	void AddGymResStats(float& Stat, float Value);
	UFUNCTION()
	void SetGymResStats(float& Stat, float Value);
	
	void SetPosterAsOwned(const int PosterIndex, const FString& PosterType);
	void SetHasBeenToGymToday(const bool InHasBeenToGymToday) { bHasBeenToGymToday = InHasBeenToGymToday; }
	void SetInnerStatus(const FInnerStatus& InInnerStatus) { InnerStatus = InInnerStatus;}

	/** Day Management **/
	void Payday(const int InMoney);
	void FirstDay();
	void FinishDemo();


		




	/** Delegates **/
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGymStatsChanged OnGymStatsChanged;


protected:
	/** Structures **/
	UPROPERTY(BlueprintReadOnly, Category = "Structures")
	FGymResStats GymResStats;
	UPROPERTY(BlueprintReadOnly, Category = "Structures")
	FBodyStatus BodyStatus;
	UPROPERTY(BlueprintReadOnly, Category = "Structures")
	FEventAndGPData RandomEvents;
	UPROPERTY(BlueprintReadOnly, Category = "Structures")
	FInnerStatus InnerStatus;
	UPROPERTY(BlueprintReadOnly, Category = "Structures")
	FInventoryData InventoryData;

private:
	/** Private Variables **/
	bool bHasBeenToGymToday;
};
