// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface_OM.generated.h"

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
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractableInterface_OM : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OPTIMIZEMANCORE_API IInteractableInterface_OM
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interaction)
	void Interact();
	
	
	virtual void SetIsInteractable(const bool InIsInteractable) { InteractableInterfaceProperties.bIsInteractable = InIsInteractable; }
	virtual FString GetInteractionWidgetText() const;
	virtual TSubclassOf<UUserWidget> GetInteractableWidget() const;
	virtual void SetInteractableWidgetText(const FString& InText);

	
	FInteractableInterface InteractableInterfaceProperties;
	
};