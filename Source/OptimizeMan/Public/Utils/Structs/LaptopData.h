#pragma once

#include "CoreMinimal.h"
#include "LaptopData.generated.h"


UENUM()
enum class EWebsites : uint8
{
	Bank UMETA(DisplayName = "SexyBank"),
	SupplementsShop UMETA(DisplayName = "SupplementNation"),
	ForSkanForum UMETA(DisplayName = "ForSkanForum"),
	CornSite UMETA(DisplayName = "YourHeavenX"),
	GeneralStore UMETA(DisplayName = "GeneralStore"),
	MusicStore UMETA(DisplayName = "MusicStore"),
	PosterStore UMETA(DisplayName = "PosterStore"),
	SupplyStore UMETA(DisplayName = "SupplyStore"),
	PlasticSurgeryShop UMETA(DisplayName = "PlasticSurgeryShop")
};
