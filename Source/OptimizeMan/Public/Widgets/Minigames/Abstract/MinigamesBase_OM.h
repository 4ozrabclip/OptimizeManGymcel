// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/MinigameData.h"
#include "Widgets/Both/Abstract/ParentWidget_OM.h"
#include "MinigamesBase_OM.generated.h"



/**
 * 
 */
UCLASS(Abstract)
class OPTIMIZEMAN_API UMinigamesBase_OM : public UParentWidget_OM
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


};
