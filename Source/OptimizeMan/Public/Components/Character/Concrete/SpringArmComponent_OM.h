// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "SpringArmComponent_OM.generated.h"

enum class EBreathingPhase : uint8
{
	Idle,
	BreathingIn,
	BreathingOut
};
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OPTIMIZEMAN_API USpringArmComponent_OM : public USpringArmComponent
{
	GENERATED_BODY()
public:
	USpringArmComponent_OM();

protected:
	/** Function Overrides **/
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	void ManageBreathingTick(float DeltaTime);
	

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	bool bPlayBreathing = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float MaxBreathOffset = 10.f;


	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float BreathUpInterpSpeed = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float BreathDownInterpSpeed = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "params")
	float BreathingTimerInterval = 2.f;


	
public:
	/** Setters **/
	void SetBreathingPhase(const EBreathingPhase InBreathingPhase) { BreathingPhase = InBreathingPhase; };
	

private:
	FTimerHandle BreathingTimerHandle;

	EBreathingPhase BreathingPhase = EBreathingPhase::Idle;
	float BreathingPhaseTime = 0.0f;
	float BreathingDuration = 1.2f; // total time for one breath direction

	float TimeSinceIdle = 0.f;
	float MinBreathOffset;
	
	bool bTickToggle = false;

	FVector OriginalSocketOffset;

};
