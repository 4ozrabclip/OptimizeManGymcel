#pragma once

#include "CoreMinimal.h"
#include "LaptopData.generated.h"


UENUM()
enum class EWebsites : uint8
{
	Bank UMETA(DisplayName = "SexyBank"),
	BulkMythology UMETA(DisplayName = "BulkMythology"),
	ForSkanForum UMETA(DisplayName = "ForSkanForum"),
	TheNattyLie UMETA(DisplayName = "TheNattyLie"),
	OneMansTrash UMETA(DisplayName = "OneMansTrash"),
	MusicStore UMETA(DisplayName = "MusicStore"),
	PosterStore UMETA(DisplayName = "PosterStore"),
	SupplyStore UMETA(DisplayName = "SupplyStore"),
	BlessedFlesh UMETA(DisplayName = "BlessedFlesh")
};
