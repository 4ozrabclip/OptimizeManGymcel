#pragma once

#include "CoreMinimal.h"
#include "SlotData.generated.h"

UENUM()
enum class ESlotItemType : uint8
{
	None	UMETA(DisplayName = "Null"),
	A		UMETA(DisplayName = "A_Type"),
	B		UMETA(DisplayName = "B_Type"),
	C		UMETA(DisplayName = "C_Type"),
	D		UMETA(DisplayName = "D_Type"),
};
USTRUCT()
struct FSlotItemData
{
	GENERATED_BODY()
	FSlotItemData() :
	Type(ESlotItemType::None),
	Image(nullptr)
	{}
	
	UPROPERTY(EditAnywhere)
	ESlotItemType Type;
	UPROPERTY(EditAnywhere)
	UTexture2D* Image;

	bool operator==(const FSlotItemData& Other)
	{
		return Type == Other.Type;
	}
	
};