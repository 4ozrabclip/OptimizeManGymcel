// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "ParentWidget_OM.generated.h"

class UButton;
/**
 * 
 */
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
	TArray<UWidget*> FocusableContent;

	UPROPERTY()
	bool bIsOpen;
	

	bool operator==(const FName& Name) const
	{
		return this->WindowName == Name;
	}
	
};


UCLASS(Abstract)
class OPTIMIZEMAN_API UParentWidget_OM : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FUserInterfaceWindow InitializeWindow(UPanelWidget* InWindow, TArray<UWidget*> InFocusableContent, FName InWindowName);

	virtual void InitWindowsArray() {Windows.Empty();}
	
	virtual void OpenWindow(const FName InWindowName, bool bUsingGameAndUI = false);
	


	virtual void UpdateButtonFocusVisuals(UButton* Button, const FButtonStyle& DefaultStyle, bool bIsFocused);


	UFUNCTION()
	virtual void DarkModeToggle(const bool bIsDarkMode);
	
	UFUNCTION()
	virtual void FadeIn();

protected:

	

	FButtonStyle CurrentButtonStyle;

	FUserInterfaceWindow* CurrentOpenWindow = nullptr;

	UPROPERTY()
	TArray<FUserInterfaceWindow> Windows;

	
	
	FTimerHandle FadeInTimerHandle;
	bool bIsFadingIn = false;

	
	UPROPERTY()
	class UGameInstance_OM* GameInstance;
	
	FGameSettings GameSettings;

	UPROPERTY()
	FSlateColor Black;
	UPROPERTY()
	FSlateColor White;
	
};
