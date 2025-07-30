// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "SpringArmComponent_OM.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OPTIMIZEMAN_API USpringArmComponent_OM : public USpringArmComponent
{
	GENERATED_BODY()
public:
	USpringArmComponent_OM();

protected:
	/** Function Overrides **/
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void PlayBreathingMovementInterval();
	UFUNCTION()
	void BreathUp();
	void BreathDown();

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	bool bPlayBreathing = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float MaxBreathOffset = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float BreathUpInterpSpeed = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float BreathDownInterpSpeed = 0.1f;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float DeltaTime = 0.065f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float BreathingTimerInterval = 2.f;

	

private:
	FTimerHandle BreathingTimerHandle;



	bool bTickToggle = false;

	FVector OriginalTargetOffset;

};
