// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

USTRUCT(BlueprintType)
struct FInteractableInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText InteractableText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractableWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	bool bIsInteractable = true;
	
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OPTIMIZEMAN_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interaction)
	void Interact();
	
	
	virtual void SetIsInteractable(const bool InIsInteractable) { InteractableInterfaceProperties.bIsInteractable = InIsInteractable; }
	virtual FString GetInteractionWidgetText() const;
	virtual TSubclassOf<UUserWidget> GetInteractableWidget() const;
	virtual void SetInteractableWidgetText(const FString& InText);

	
	FInteractableInterface InteractableInterfaceProperties;
	
};