// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Bedroom/Concrete/Shower_OM.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "ShowerWidget_OM.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UShowerWidget_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InitShower(const TSoftObjectPtr<AShower_OM>& InShower) { Shower = InShower.Get();}


	
protected:
	UPROPERTY()
	AShower_OM* Shower;


	/**	Widget Objects **/
	UPROPERTY(meta = (BindWidget))
	UButton* ColdShowerButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HotShowerButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;
public:
	
	
};
