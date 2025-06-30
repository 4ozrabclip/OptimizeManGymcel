#pragma once

#include "CoreMinimal.h"
#include "Dates.generated.h"

UENUM(BlueprintType)
enum class EWeekDay : uint8
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

UENUM(BlueprintType)
enum class EMonth : uint8
{
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

USTRUCT(BlueprintType)
struct FDayInfo
{
	GENERATED_USTRUCT_BODY()

	FDayInfo()
	: DayNumber(1),
	MonthDayNumber(1),
	CurrentDay(EWeekDay::Monday),
	CurrentMonth(EMonth::January),
	bIsSpecialDay(false),
	DayEvent("")
	{}
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DayNumber;
	
	UPROPERTY(BlueprintReadWrite)
	int32 MonthDayNumber;
	
	UPROPERTY(BlueprintReadWrite)
	EWeekDay CurrentDay;

	UPROPERTY(BlueprintReadWrite)
	EMonth CurrentMonth;

	UPROPERTY(BlueprintReadWrite)
	bool bIsSpecialDay;

	UPROPERTY(BlueprintReadWrite)
	FString DayEvent;
};
