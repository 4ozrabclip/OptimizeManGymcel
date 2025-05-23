// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Utils/Structs/PlayModes.h"
#include "PlayerController_OM.generated.h"

class APlayerCharacter_OM;
class UInputMappingContext;
class UInputAction;
/**
 *			- Enhanced Input Management
 *			- UI / Hud Management
 */
UCLASS()
class OPTIMIZEMAN_API APlayerController_OM : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	void BindInputMapping();

	virtual void OnPossess(APawn* InPawn) override;
	void PlaymodeWidgetManagement(EPlayModes CurrentPlayMode, bool bHasFadeIn);
	void SetCurrentPlayModeWidget(EPlayModes CurrentPlayMode);


	// UI --------------
	void FadeWidgets(UUserWidget* FadeOutWidget, UUserWidget* FadeInWidget);
	void SetGymHud(const bool bLoad = true);
	bool GetIsInteractableWidgetOnViewport();
	void ToggleInteractWidgetFromViewport(bool bRemove);
	void WidgetInteraction(const TScriptInterface<class IInteractableInterface_OM>& InteractedActorInterface);
	void HideUnhideInteractableWidget(bool bHide);
	void ShowOrHideHint(const FString& HintText, float HintLength = 0.f, bool HideHint = false, bool RemoveFully = false) const;
	
	// UI --------------
	UFUNCTION()
	void TodoCompletedPopUp();
	UFUNCTION()
	void UpdateGymHud();
	UFUNCTION()
	void RemoveAllActiveWidgets();


	//------- Getters
	UUserWidget* GetMirrorWidget() const { return MirrorWidget; }
	UUserWidget* GetLaptopWidget() const { return LaptopWidget; }

	


	
protected: // Enhanced Input
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

	// Array
	TArray<UUserWidget*> ActiveWidgets;


	// Character Possessed
	UPROPERTY()
	APlayerCharacter_OM* PlayerCharacter;
	
protected: //Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* InteractableActorWidget;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* PauseMenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* MirrorWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* MuscleViewWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* WorkoutWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* SocialWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* LaptopWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* TodoWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* WakeUpWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* HintWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* TodoCompleteWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* ShelfWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* CalenderWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* GymHudWidget;

private:
	UPROPERTY()
	UUserWidget* CurrentPlayModeWidget;



	
};
