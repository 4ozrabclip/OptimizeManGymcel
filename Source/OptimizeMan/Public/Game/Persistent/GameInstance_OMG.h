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
	/** Inits **/
	virtual void InitializePlayerData() override;

	void InitializePostersOwned();

	/** Save/Reset Management **/
	virtual void ResetGame() override;
	virtual void ResetAllSaves() override;

	virtual void HandleDayEvents() override;

	

	/** Finders/Getters **/
	UFUNCTION(BlueprintCallable)
	FGymResStats& GetGymResStats() { return GymResStats; }
	UFUNCTION()
	FBodyStatus& GetBodyStatus() { return BodyStatus;}
	UFUNCTION()
	FInventoryData& GetInventoryData() { return InventoryData; }
	UFUNCTION(BlueprintCallable)
	TMap<EEventAndGPData, bool> GetRandomEventsWitnessedMap() { return RandomEvents.RandomEventsWitnessedMap; }
	UFUNCTION(BlueprintCallable)
	FEventAndGPData& GetRandomEvents() { return RandomEvents; }
	UFUNCTION()
	FInnerStatus& GetInnerStatus() { return InnerStatus; }


	FBodyPartData* FindBodyPart(const EBodyPart& Part, const EBodyPartSide& Side);
	float GetBodyPartStrengthValue(const EBodyPart& Part, const EBodyPartSide& Side);
	float GetBodyPartLeftRightCombinedStrengthValue(const EBodyPart& Part);
	float* GetBodyPartStrengthPtr(const EBodyPart& Part, const EBodyPartSide& Side);
	TArray<bool> GetOwnedWaifuPosters() { return bOwnsWaifuPosters;}
	TArray<bool> GetOwnedChadPosters() { return bOwnsChadPosters;}
	bool GetOwnsSteroids() const { return InventoryData.bOwnsSteroids; }
	bool GetOwnsPreWorkout() const { return InventoryData.bOwnsPreWorkout; }
	bool GetCurrentlyOnSteroids() const { return BodyStatus.bCurrentlyOnSteroids; }
	bool GetHasBeenToGymToday() const { return bHasBeenToGymToday; }
	int GetMoney() const { return InventoryData.Money; }
	float GetEgo() const { return InnerStatus.Ego; }
	float GetSexAppeal() const { return InnerStatus.SexAppeal; }
	float GetSocial() const { return InnerStatus.Social; }
	
	/** Setters/Adders **/
	UFUNCTION()
	void AddGymResStats(float& Stat, float Value);
	UFUNCTION()
	void SetGymResStats(float& Stat, float Value);
	UFUNCTION(BlueprintCallable)
	void SetRandomEventAsWitnessed(const EEventAndGPData InRandomEvent, const bool InWitnessed);
	
	
	void SetPosterAsOwned(const int PosterIndex, const FString& PosterType);
	void SetHasBeenToGymToday(const bool InHasBeenToGymToday) { bHasBeenToGymToday = InHasBeenToGymToday; }
	void SetInnerStatus(const FInnerStatus& InInnerStatus) { InnerStatus = InInnerStatus;}
	void SetMoney(const int InMoney) { InventoryData.Money += InMoney; }

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
	TArray<bool> bOwnsWaifuPosters;
	TArray<bool> bOwnsChadPosters;
};
