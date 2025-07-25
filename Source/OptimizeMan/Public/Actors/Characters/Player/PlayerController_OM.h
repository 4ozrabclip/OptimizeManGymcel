// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Utils/Structs/PlayModes.h"
#include "Widgets/Home/Concrete/MirrorWidget_OM.h"
#include "PlayerController_OM.generated.h"

class UVendingMachineWidget_OM;
class UWidgetInteractionComponent;
class ULevelSequence;
class UInteractWidget_OM;
class UGymHud_OM;
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
class UExerciseInteractWidget_OM;
class UGameInstance_OM;
class APlayerCharacter_OM;
class UInputMappingContext;
class UInputAction;
class UGameInstance_OM;
class APlayerCharacter_OM;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UInputAction;
class UTodoManagementSubsystem;

/**
 *			- Enhanced Input Management
 *			- UI / Hud Management
 */
UCLASS()
class OPTIMIZEMAN_API APlayerController_OM : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerController_OM();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

public:
	void BindInputMapping();

	
	

	// Sequence Management ------------
	void PlaySequence(ULevelSequence* InSequence);


	
	// UI --------------
	void PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn);
	void FadeWidgets(UUserWidget* FadeOutWidget, UUserWidget* FadeInWidget);
	void SetGymHud(const bool bLoad = true);
	void LoadGamePointsHud(const bool bLoad = true);
	bool GetIsInteractableWidgetOnViewport();
	void ToggleInteractWidgetFromViewport(bool bRemove);
	void WidgetInteraction(const TScriptInterface<class IInteractableInterface_OM>& InteractedActorInterface);
	void HideUnhideInteractableWidget(bool bHide);
	void ShowOrHideHint(const FString& HintText, float HintLength = 0.f, bool HideHint = false, bool RemoveFully = false) const;
	void HideGamePointsHud(bool bHide);
	
	// UI --------------
	UFUNCTION()
	void TodoCompletedPopUp();
	UFUNCTION()
	void UpdateGymHud();
	UFUNCTION()
	void RemoveAllActiveWidgets();


	//------- Getters
	UUserWidget* GetCurrentPlayModeWidgetInstance() const { return CurrentPlayModeWidgetInstance; }

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UWidgetInteractionComponent* WidgInteractionComp;
protected:
	// Enhanced Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToLook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToJump;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToInteractClick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToInteractToggle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToOpenTodo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputToOpenPauseMenu;




	
private:
	// Timers
	FTimerHandle TodoPopUpHandle;
	FTimerHandle SetModeWidgetFadeInTimerHandle;

	UPROPERTY()
	TArray<UUserWidget*> ActiveWidgets;


	// Character Possessed
	UPROPERTY()
	APlayerCharacter_OM* PlayerCharacter;

	UPROPERTY()
	UGameInstance_OM* GameInstance;
	
protected: //Widgets

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UVendingMachineWidget_OM> VendorWidget;
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
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGamePointsHud_OM> GamePointsWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UInteractWidget_OM> InteractWidget;

	UPROPERTY()
	TObjectPtr<UGymHud_OM> GymHudPtr;
	UPROPERTY()
	TObjectPtr<UGamePointsHud_OM> GamePointsHudPtr;
	UPROPERTY()
	TObjectPtr<UHintsWidget_OM> HintsPtr;
	UPROPERTY()
	TObjectPtr<UTodoCompletePopupWidget_OM> TodoWidgetPtr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UInteractWidget_OM> InteractWidgetPtr;

	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentPlayModeWidgetInstance;
	
	
};

