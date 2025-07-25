// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "GamePointsHud_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UGamePointsHud_OM : public UParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateGamePoints();


	virtual void DarkModeToggle(const bool bIsDarkMode) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Points_TextBlock;

protected:
	UPROPERTY()
	UTodoManagementSubsystem* TodoManager;
	
};
