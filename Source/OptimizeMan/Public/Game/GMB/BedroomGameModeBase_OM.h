// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameModeBase_OM.h"
#include "GameFramework/GameModeBase.h"
#include "BedroomGameModeBase_OM.generated.h"

class UDisplayDayWidget_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API ABedroomGameModeBase_OM : public AGameModeBase_OM
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

	UDisplayDayWidget_OM* GetShowDayWidget() const;
	TSubclassOf<UDisplayDayWidget_OM> GetShowDayWidgetClass() const { return ShowDayWidgetClass; }

	bool GetWidgetIsVisible() const;

	void SetWidgetIsVisible(const bool InWidgetIsVisible);

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UDisplayDayWidget_OM> ShowDayWidgetClass;

	UPROPERTY()
	UDisplayDayWidget_OM* ShowDayWidget;

	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	


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
