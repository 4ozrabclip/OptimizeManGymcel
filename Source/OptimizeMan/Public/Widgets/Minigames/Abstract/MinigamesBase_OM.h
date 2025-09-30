// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/MinigameData.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "MinigamesBase_OM.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinigameResult, EMinigameResult, Result);

class APlayerController_OM;
class APlayerCharacter_OM;
/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API UMinigamesBase_OM : public UParentWidget_OM
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


	/** Delegates / Events **/
	FOnMinigameResult OnMinigameResult;

protected:
	UPROPERTY()
	APlayerCharacter_OM* Player;
	UPROPERTY()
	APlayerController_OM* PlayerController;
};
