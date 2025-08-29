// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase_OM.generated.h"

class UGameAudio_OM;
/**
 * 
 */
UCLASS()
class OPTIMIZEMAN_API APlayerControllerBase_OM : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerBase_OM();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void PlayUISound(USoundBase* InSound) const;
	

protected:
	/** Components **/
	UPROPERTY()
	UGameAudio_OM* UserInterfaceAudio;


	
};
