// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UIAudioManager_OM.generated.h"

class UGameAudio_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API UUIAudioManager_OM : public UObject
{
	GENERATED_BODY()
public:

	


protected:
	UPROPERTY()
	UGameAudio_OM* AudioComponent;
	

	
};
