// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExerciseSelectionParentWidget_OM.h"
#include "IsolatedSelectionWidget_OM.generated.h"

/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UIsolatedSelectionWidget_OM : public UExerciseSelectionParentWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
};
