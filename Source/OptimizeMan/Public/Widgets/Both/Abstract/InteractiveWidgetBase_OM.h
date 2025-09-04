// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ParentWidget_OM.h"
#include "InteractiveWidgetBase_OM.generated.h"

class USlider;
/**
 * 
 */
USTRUCT()
struct FButtonStruct
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UButton* Button;
	UPROPERTY()
	FButtonStyle DefaultButtonStyle;

};
USTRUCT()
struct FSliderStruct
{
	GENERATED_BODY()
public:
	UPROPERTY()
	USlider* Slider;
	UPROPERTY()
	FButtonStyle DefaultButtonStyle;

};
USTRUCT()
struct FFocusableWidgetStruct
{
	GENERATED_BODY()

	UPROPERTY()
	FName Type;

	UPROPERTY()
	FButtonStruct ButtonData;

	UPROPERTY()
	FSliderStruct SliderData;

	bool IsButton() const { return Type == "Button"; }
	bool IsSlider() const { return Type == "Slider"; }

	static FFocusableWidgetStruct FromButton(const FButtonStruct& InButton)
	{
		FFocusableWidgetStruct Out;
		Out.Type = "Button";
		Out.ButtonData = InButton;
		return Out;
	}

	static FFocusableWidgetStruct FromSlider(const FSliderStruct& InSlider)
	{
		FFocusableWidgetStruct Out;
		Out.Type = "Slider";
		Out.SliderData = InSlider;
		return Out;
	}
};

USTRUCT()
struct FUserInterfaceWindow
{
	GENERATED_BODY()

public:
	FUserInterfaceWindow() :
	WindowName(FName("Invalid")),
	Window(nullptr),
	bIsOpen(false)
	{}

	UPROPERTY()
	FName WindowName;
	
	UPROPERTY()
	UPanelWidget* Window;

	UPROPERTY()
	TArray<FFocusableWidgetStruct> FocusableContent;


	UPROPERTY()
	bool bIsOpen;
	

	bool operator==(const FName& Name) const
	{
		return this->WindowName == Name;
	}
};

UCLASS()
class OPTIMIZEMAN_API UInteractiveWidgetBase_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void UpdateButtonFocusVisuals(UButton* Button, const FButtonStyle& DefaultStyle, bool bIsFocused);


	void PlayClickSound();
	

	void ManageControllerInteraction();
	virtual FUserInterfaceWindow InitializeWindow(UPanelWidget* InWindow, TArray<FFocusableWidgetStruct> InFocusableContent, FName InWindowName);

	virtual void InitWindowsArray() { Windows.Empty(); }
	static FFocusableWidgetStruct MakeButton(UButton* InButton, const FButtonStyle& InStyle);

	virtual void OpenWindow(const FName InWindowName, bool bUsingGameAndUI = false, bool bPlayClick = true);


protected:

	FButtonStyle CurrentButtonStyle;

	FUserInterfaceWindow* CurrentOpenWindow = nullptr;

	UPROPERTY()
	TArray<FUserInterfaceWindow> Windows;


	bool bIsUsingController = false;

	
	/** Audio **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* ClickSound;
	

	
	

};
