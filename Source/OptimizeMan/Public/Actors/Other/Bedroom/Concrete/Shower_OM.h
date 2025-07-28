// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Other/Abstract/InteractableActor_OM.h"
#include "Shower_OM.generated.h"

class UGameAudio_OM;
class UWidgetComponent;

UCLASS()
class OPTIMIZEMAN_API AShower_OM : public AInteractableActor_OM
{
	GENERATED_BODY()
public:
	AShower_OM();
protected:
	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void DarkModeToggle(const bool bIsDarkMode) override;

public:
	UFUNCTION()
	void TakeHotShower() { TakeShower(false); };
	UFUNCTION()
	void TakeColdShower() { TakeShower(true); };

protected:
	void TakeShower(bool bCold);
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UWidgetComponent* WidgetComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UGameAudio_OM* AudioComp;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	TArray<USoundBase*> ColdShowerSounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	TArray<USoundBase*> HotShowerSounds;
public:
	UFUNCTION()
	void CloseWidget();
};
