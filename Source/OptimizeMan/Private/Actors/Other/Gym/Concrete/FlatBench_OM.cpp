// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/FlatBench_OM.h"

AFlatBench_OM::AFlatBench_OM()
{
	Barbell = CreateDefaultSubobject<UStaticMeshComponent>("Barbell");
	Barbell->SetupAttachment(RootComponent);
	
}
