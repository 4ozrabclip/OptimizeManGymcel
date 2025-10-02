// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Both/Concrete/InfoSign_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Both/Concrete/TutorialWidget_OM.h"

AInfoSign_OM::AInfoSign_OM()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AInfoSign_OM::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto* GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance()))
	{
		if (!GameInstance->GetTutorialsOn())
			Destroy();
	}
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AInfoSign_OM::OnPlayerOverlap);

	InitialLocation = GetActorLocation();

	Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	
	if (TutorialWidget)
	{
		TutorialWidget->InitInfoSign(this);
	}
	
}

void AInfoSign_OM::OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (!Player)
			Player = Cast<APlayerCharacter_OM>(OtherActor);
		if (Player)
		{
			if (auto* PC = Cast<APlayerController_OM>(Player->GetController()))
			{
				PC->GetWidgetManagementComponent()->SetTutorialWidget(TutorialWidget);


				Player->SetCurrentPlayMode(EPlayModes::TutorialMode);
				
				SetActorHiddenInGame(true);

			}
		}
	}
}

void AInfoSign_OM::OnTutorialOff()
{
	if (TutorialWidget && TutorialWidget->IsInViewport())
	{
		TutorialWidget->RemoveFromParent();
	}
	Destroy();
}

void AInfoSign_OM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetWorld()) return;


	if (Player)
	{
		FVector PlayerLocation = Player->GetActorLocation();
		FVector Direction = (PlayerLocation - GetActorLocation()).GetSafeNormal();

		FRotator NewRotation = Direction.Rotation();
		
		SetActorRotation(FRotator(0.f, NewRotation.Yaw, 0.f));
	}

	float DeltaHeight = FMath::Sin(GetWorld()->GetTimeSeconds() * Frequency * 2 * PI) * Amplitude;
	FVector NewLocation = InitialLocation;
	NewLocation.Z += DeltaHeight;

	SetActorLocation(NewLocation);
	
	
	
}
