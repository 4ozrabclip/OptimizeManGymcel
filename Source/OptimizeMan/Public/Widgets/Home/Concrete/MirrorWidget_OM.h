// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "MirrorWidget_OM.generated.h"

/**
 * 
 */


class UImage;
class UButton;
class UProgressBar;
UCLASS()
class OPTIMIZEMAN_API UMirrorWidget_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void DarkModeToggle(const bool bIsDarkMode) override;

	void CheckAndSetWarningText();

protected:
	
	UPROPERTY(meta = (BindWidget))
	UImage* EgoImage;
	UPROPERTY(meta = (BindWidget))
	UImage* SexAppealImage;
	UPROPERTY(meta = (BindWidget))
	UImage* SocialImage;
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* EgoNegativeBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* EgoPositiveBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* SexNegativeBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* SexPositiveBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* SocialNegativeBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* SocialPositiveBar;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light Mode")
	UMaterial* EgoBlackText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light Mode")
	UMaterial* EgoWhiteText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light Mode")
	UMaterial* SexAppealBlackText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light Mode")
	UMaterial* SexAppealWhiteText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light Mode")
	UMaterial* SocialBlackText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dark/Light Mode")
	UMaterial* SocialWhiteText;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WarningText;
	

public:
	
	UFUNCTION(BlueprintCallable)
	void UpdateStats();
	void UpdateStatBar(float InTypeStat, UProgressBar* InPositiveBar, UProgressBar* InNegativeBar);

private:
	FTimerHandle FadeInTimerHandle;

	bool bIsFadingIn = false;
};