// Fill out your copyright notice in the Description page of Project Settings.

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
	class UGameInstance_OMG* GameInstance;

	UPROPERTY()
	class UTodoManagement_OMG* TodoManager;


	UPROPERTY()
	class APlayerCharacter_OM* Player;

	UPROPERTY()
	class APlayerController_OMG* PlayerController;


	
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
