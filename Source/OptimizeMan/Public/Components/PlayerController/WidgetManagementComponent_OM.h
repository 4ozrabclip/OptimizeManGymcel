// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utils/Structs/MinigameData.h"
#include "Utils/Structs/PlayModes.h"
#include "WidgetManagementComponent_OM.generated.h"

class UDisplayDayWidget_OM;
class UTutorialWidget_OM;
class UPlayModeBaseWidget_OM;
class UYouDiedWidget_OM;
class UVendingMachineWidget_OM;
class UWidgetInteractionComponent;
class ULevelSequence;
class UInteractWidget_OM;
class UCalenderWidget_OM;
class UShelfWidget_OM;
class UHintsWidget_OM;
class ULaptopWidget_OM;
class UMuscleViewWidget_OM;
class UMirrorWidget_OM;
class UPauseMenuWidget_OM;
class UWakeUpTutorial_OM;
class UWakeUpWidget_OM;
class UGamePointsHud_OM;
class UTodoCompletePopupWidget_OM;
class UTodoList_OM;
class USocialInteractionWidget_OM;
class UExerciseMinigameWidget_OM;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetExited);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OPTIMIZEMAN_API UWidgetManagementComponent_OM : public UActorComponent
{
	GENERATED_BODY()
public:
	UWidgetManagementComponent_OM();
protected:
	virtual void BeginPlay() override;

public:
	/** Core **/
	void PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn);
	void WidgetInteraction(const TScriptInterface<class IInteractableInterface_OM>& InteractedActorInterface);
	void ResetUI();

	/** Toggles **/
	void ToggleInteractWidgetFromViewport(bool bRemove);
	void HideUnhideInteractableWidget(bool bHide) const;
	void ShowOrHideHint(const FString& HintText, float HintLength = 0.f, bool HideHint = false, bool RemoveFully = false);
	void HidePersistentHud(bool bHide) const;
	void HideMentalHealthStats(float TimeHidden = 2.f);
	void ShowExitButton(bool bHide = false) const;

	/** Indicators **/
	void FlashExitButton(int LoopsToPlay = 2) const;
	
	/** Getters **/
	bool GetIsInteractableWidgetOnViewport() const;
	UPlayModeBaseWidget_OM* GetCurrentPlayModeWidgetInstance() const { return CurrentPlayModeWidgetInstance; }
	TArray<UUserWidget*> GetActiveWidgets() const { return ActiveWidgets; }

	/** Setters **/
	UFUNCTION()
	void SetTutorialWidget(const UTutorialWidget_OM* InTutorialWidget);
	UFUNCTION()
	void SetWorkoutMinigame(EMinigameType InMiniGame);


	/** Delegate Called UFunctions **/
	UFUNCTION()
	void ShowYouDiedWidget();
	UFUNCTION()
	void TodoCompletedPopUp();
	UFUNCTION()
	void RemoveAllActiveWidgets();

protected:
	/** Delegate Events **/
	UPROPERTY(EditDefaultsOnly, Category = "Events")
	FOnWidgetExited OnWidgetExited;

private:
	/** Helpers **/
	void FadeWidgets(UUserWidget* FadeOutWidget, UUserWidget* FadeInWidget);
	void LoadPersistentHud(const bool bLoad = true);
	
	/** Timer Handles **/
	FTimerHandle TodoPopUpHandle;
	FTimerHandle SetModeWidgetFadeInTimerHandle;
	FTimerHandle HideMentalStats;
	FTimerHandle YouDiedTimer;
	


	UPROPERTY()
	TArray<UUserWidget*> ActiveWidgets;


	/** Widget Classes **/
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TMap<EPlayModes, TSubclassOf<UPlayModeBaseWidget_OM>> PlayModeWidgets;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TMap<EMinigameType, TSubclassOf<UExerciseMinigameWidget_OM>> WorkoutMinigames;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGamePointsHud_OM> PersistentHud;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractWidget_OM> InteractWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UYouDiedWidget_OM> YouDiedWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UDisplayDayWidget_OM> ShowDayWidget;
	
	UPROPERTY()
	TObjectPtr<UPlayModeBaseWidget_OM> CurrentPlayModeWidgetInstance;
	UPROPERTY()
	TObjectPtr<UGamePointsHud_OM> PersistentHudPtr;
	UPROPERTY()
	TObjectPtr<UInteractWidget_OM> InteractWidgetPtr;


	
	/** Add These To Persistent Hud **/
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHintsWidget_OM> HintWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTodoCompletePopupWidget_OM> TodoCompleteWidget;
	UPROPERTY()
	TObjectPtr<UHintsWidget_OM> HintsPtr;
	UPROPERTY()
	TObjectPtr<UTodoCompletePopupWidget_OM> TodoWidgetPtr;




	


};
