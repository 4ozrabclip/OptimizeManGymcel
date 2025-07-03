// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/NPC_AIController_OM.h"

#include "BehaviorTree/BehaviorTree.h"

ANPC_AIController_OM::ANPC_AIController_OM(const FObjectInitializer& ObjectInitializer)
{
	Npc = nullptr;

	PrimaryActorTick.bCanEverTick = true;
	
	
}

void ANPC_AIController_OM::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC_AIController_OM::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	
	
}

void ANPC_AIController_OM::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}
