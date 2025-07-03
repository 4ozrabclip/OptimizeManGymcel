// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/PlayerController_OM.h"
#include "Game/Persistent/GameInstance_OMG.h"
#include "PlayerController_OMG.generated.h"

class APlayerCharacter_OM;
class UWakeUpWidget_OM;
class UWakeUpTutorial_OM;
class UPauseMenuWidget_OM;
class UMirrorWidget_OM;
class UMuscleViewWidget_OM;
class UExerciseInteractWidget_OM;
class USocialInteractionWidget_OM;
class ULaptopWidget_OM;
class UTodoList_OM;
class UShelfWidget_OM;
class UCalenderWidget_OM;
class UGymHud_OM;
class UHintsWidget_OM;
class UTodoCompletePopupWidget_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API APlayerController_OMG : public APlayerController_OM
{
	GENERATED_BODY()
public:
	APlayerController_OMG();
protected:
	/** Class Overrides **/
	virtual void BeginPlay() override;
public:
	virtual void BindInputMapping() override;
	// Sequence Management ------------
	void PlaySequence(ULevelSequence* InSequence);

	
	// UI --------------
	void PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn);
	void FadeWidgets(UUserWidget* FadeOutWidget, UUserWidget* FadeInWidget);
	void SetGymHud(const bool bLoad = true);
	
	void ShowOrHideHint(const FString& HintText, float HintLength = 0.f, bool HideHint = false, bool RemoveFully = false) const;

	
	// UI --------------
	UFUNCTION()
	void TodoCompletedPopUp();
	UFUNCTION()
	void UpdateGymHud();
	UFUNCTION()
	void RemoveAllActiveWidgets();


	//------- Getters
	UUserWidget* GetCurrentPlayModeWidgetInstance() const { return CurrentPlayModeWidgetInstance; }

private:
	/** Class Cache **/
	APlayerCharacter_OM* GetPlayer_Gymcel() const;


	FORCEINLINE UGameInstance_OMG* GetGameInstance_Gymcel() const
	{
		return Cast<UGameInstance_OMG>(GameInstance);
	}
	
	// Timers
	FTimerHandle TodoPopUpHandle;
	FTimerHandle SetModeWidgetFadeInTimerHandle;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWakeUpWidget_OM> WakeUpWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWakeUpTutorial_OM> WakeUpWidget_Tutorial;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPauseMenuWidget_OM> PauseMenuWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMirrorWidget_OM> MirrorWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMuscleViewWidget_OM> MuscleViewWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UExerciseInteractWidget_OM> WorkoutWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USocialInteractionWidget_OM> SocialWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ULaptopWidget_OM> LaptopWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTodoList_OM> TodoWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHintsWidget_OM> HintWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTodoCompletePopupWidget_OM> TodoCompleteWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UShelfWidget_OM> ShelfWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCalenderWidget_OM> CalenderWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGymHud_OM> GymHudWidget;


	UPROPERTY()
	TObjectPtr<UGymHud_OM> GymHudPtr;
	UPROPERTY()
	TObjectPtr<UHintsWidget_OM> HintsPtr;
	UPROPERTY()
	TObjectPtr<UTodoCompletePopupWidget_OM> TodoWidgetPtr;



	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentPlayModeWidgetInstance;
};
