// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BedroomGameModeBase_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ABedroomGameModeBase_OM : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABedroomGameModeBase_OM();
protected:
	virtual void BeginPlay() override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

public:
	void ProcessIncompleteTodos();
	void WakeUp();
	void TutorialDay();
	void ShowTodoHint();
	void ShowPauseMenuHint();
	void ShowInteractHint();


	void ShowCurrentDay();

	void StartFadeOut();

	bool GetIsFadingOut();

	UUserWidget* GetShowDayWidget() { return ShowDayWidget;}

	bool GetWidgetIsVisible() const;

	void SetWidgetIsVisible(const bool InWidgetIsVisible);

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	UUserWidget* ShowDayWidget;

	UPROPERTY()
	class UGameInstance_OM* GameInstance;

	UPROPERTY()
	class UTodoManagementSubsystem* TodoManager;


	UPROPERTY()
	class APlayerCharacter_OM* Player;

	UPROPERTY()
	class APlayerController_OM* PlayerController;


	
	FTimerHandle DelayTilFadeHandle;
	FTimerHandle FadeTimerHandle;
	
	FTimerHandle ShowTodoTimerHandle;
	FTimerHandle ShowPauseMenuTimerHandle;
	FTimerHandle ShowInteractTimerHandle;

private:
	bool bHasOpenedTodoList;
	bool bIsFadingOut;
	bool bWidgetIsVisible;
};
