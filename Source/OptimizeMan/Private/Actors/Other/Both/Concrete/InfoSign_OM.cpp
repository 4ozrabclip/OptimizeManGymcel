// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Both/Concrete/InfoSign_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"


// Sets default values
AInfoSign_OM::AInfoSign_OM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	
	StaticMesh->SetGenerateOverlapEvents(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AInfoSign_OM::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AInfoSign_OM::OnPlayerOverlap);
}

void AInfoSign_OM::OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (auto* PlayerChar = Cast<APlayerCharacter_OM>(OtherActor))
		{
			if (auto* PC = Cast<APlayerController>(PlayerChar->GetController()))
			{
				Destroy();
			}
		}
	}
}

void AInfoSign_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

