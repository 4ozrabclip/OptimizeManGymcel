// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Home/Abstract/WakeUpBase_OM.h"
#include "WakeUpTutorial_OM.generated.h"

class UOverlay;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UWakeUpTutorial_OM : public UWakeUpBase_OM
{
	GENERATED_BODY()
public:
	explicit UWakeUpTutorial_OM(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	
	void InitiateTutorialSequence();
	void PlayTutorialAnimation(UWidgetAnimation* InAnimationPart);
	void PlayContPrompt();

	UFUNCTION()
	void AdvanceTutorial();
	void FinishTutorial();

	virtual void OnExitButtonClicked() override;
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* TodoLisTut_Overlay;
	UPROPERTY(meta = (BindWidget))
	UOverlay* ChooseTasksTut_Overlay;
	

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TutPart1;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TutPart1_Cont;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TutPart2;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TutPart2_Cont;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TutPart3;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TutPart3_Cont;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TutPart4;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TutPart4_Cont;

private:


	FTimerHandle Handle;
	int CurrentTutorialStep;
	bool bWaitingForInput;
};
