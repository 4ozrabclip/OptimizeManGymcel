#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "ParticleTypes.generated.h"

USTRUCT(BlueprintType)
struct FParticleType
{
	GENERATED_BODY()

	FParticleType() :
	Name("Invalid"),
	ParticleSystem(nullptr)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* ParticleSystem;

	bool operator==(const FName& Other) const
	{
		return Name == Other;
	}
	
};
