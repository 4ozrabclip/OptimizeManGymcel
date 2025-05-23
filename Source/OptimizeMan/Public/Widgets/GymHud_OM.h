// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ParentWidget_OM.h"
#include "GymHud_OM.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UGymHud_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void UpdateProgressBars();
	
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Energy_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Focus_PBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Bladder_PBar;
	
};
