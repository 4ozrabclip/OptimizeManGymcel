// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OptimizeMan/Public/Interfaces/InteractableInterface.h"
#include "GameFramework/Character.h"
#include "Game/Persistent/SaveData/NpcDataSave.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/InteractableInterface_OM.h"
#include "Utils/Structs/ExerciseData.h"
#include "Utils/Structs/NpcStates.h"
#include "Utils/Structs/SocialData.h"
#include "NpcBase_OM.generated.h"


class UPointLightComponent;
class UBlackboardComponent;
class UBehaviorTree;
class UGameAudio_OM;
class UNpcBaseAnimInstance_OM;

UCLASS(Abstract, Blueprintable)
class OPTIMIZEMAN_API ANpcBase_OM : public ACharacter, public IInteractableInterface_OM
{
	GENERATED_BODY()
public:
	ANpcBase_OM();
	virtual void Interact_Implementation() override;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



};



