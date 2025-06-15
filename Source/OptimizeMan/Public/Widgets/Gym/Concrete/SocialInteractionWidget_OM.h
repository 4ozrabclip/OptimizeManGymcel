// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Structs/SocialData.h"

#include "Widgets/Both/Abstract/MinigameBaseWidget_OM.h"
#include "SocialInteractionWidget_OM.generated.h"

/**
 * 
 */


class UImage;
class UButton;
enum class ENpcMood : uint8;

USTRUCT(BlueprintType)
struct FSocialInteractionTypes
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Social Interaction Types")
	ESocialType SocialType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Social Interaction Types")
	UTexture2D* EmojiType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Social Interaction Types")
	UTexture2D* PressedEmoji;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Social Interaction Types")
	UTexture2D* EmojiType_Goblin;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Social Interaction Types")
    UTexture2D* PressedEmoji_Goblin;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Social Interaction Types")
	UTexture2D* EmojiType_Chad;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Social Interaction Types")
	UTexture2D* PressedEmoji_Chad;
	

	FSocialInteractionTypes() : SocialType(ESocialType::Neutral), EmojiType(nullptr),PressedEmoji(nullptr), EmojiType_Goblin(nullptr),PressedEmoji_Goblin(nullptr),  EmojiType_Chad(nullptr),
								PressedEmoji_Chad(nullptr) {}
};
UCLASS()
class OPTIMIZEMAN_API USocialInteractionWidget_OM : public UMinigameBaseWidget_OM
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Social Interaction Types")
	TArray<FSocialInteractionTypes> SocialInteractionTypes;

	virtual void NativeConstruct() override;
	
	virtual ~USocialInteractionWidget_OM() override;
	void CheckAndSetDarkMode();

	UFUNCTION()
	void OnEmotionalStateChanged(EPlayerEmotionalStates InEmotionalState);

	virtual void OnExitButtonClicked() override;

	void SetButton(UButton* InButton, const ESocialType InSocialType) const;
	
	void SetSocialOptions();
	void ShowFriendshipLevel();

	void ManageInteraction(const UButton* ClickedButton);

	UPROPERTY(meta = (BindWidget))
	class UBorder* SocialOptionsBorder;

	

	UPROPERTY(meta = (BindWidget))
	UButton* Option1Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Option2Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Option3Button;
	

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* LikeBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* DislikeBar;

	FButtonStyle NeutralButtonStyle;
	FButtonStyle NeutralButtonStyle_Goblin;
	FButtonStyle NeutralButtonStyle_Chad;

	FButtonStyle FriendlyButtonStyle;
	FButtonStyle FriendlyButtonStyle_Goblin;
	FButtonStyle FriendlyButtonStyle_Chad;

	FButtonStyle RandyButtonStyle;
	FButtonStyle RandyButtonStyle_Goblin;
	FButtonStyle RandyButtonStyle_Chad;

	FButtonStyle AngryButtonStyle;
	FButtonStyle AngryButtonStyle_Goblin;
	FButtonStyle AngryButtonStyle_Chad;

	FButtonStyle DontListenButtonStyle;
	FButtonStyle DontListenButtonStyle_Goblin;
	FButtonStyle DontListenButtonStyle_Chad;

	FButtonStyle FunnyButtonStyle;
	FButtonStyle FunnyButtonStyle_Goblin;
	FButtonStyle FunnyButtonStyle_Chad;

	FButtonStyle HilariousButtonStyle;
	FButtonStyle HilariousButtonStyle_Goblin;
	FButtonStyle HilariousButtonStyle_Chad;

	FButtonStyle WeirdJokeButtonStyle;
	FButtonStyle WeirdJokeButtonStyle_Goblin;
	FButtonStyle WeirdJokeButtonStyle_Chad;

	FButtonStyle AwkwardButtonStyle;
	FButtonStyle AwkwardButtonStyle_Goblin;
	FButtonStyle AwkwardButtonStyle_Chad;

	FButtonStyle FlexingButtonStyle;
	FButtonStyle FlexingButtonStyle_Goblin;
	FButtonStyle FlexingButtonStyle_Chad;




protected:
	UPROPERTY()
	class USocialInteractionSystem_OM* SocialInteractionComponent;

	UPROPERTY(EditAnywhere, Category = "Dark/Light Mode")
	UMaterial* WhiteBorder;
	UPROPERTY(EditAnywhere, Category = "Dark/Light Mode")
	UMaterial* BlackBorder;


	FTimerHandle ChatTimerHandle;
	


private:
	void InitializeButtonStyles();
	void InitializeInteractionMap();

	bool IsButtonThisStyle(const FButtonStyle* Style1, const FButtonStyle* Style2);
	
	TMap<FDialogueCondition, TArray<ESocialType>> InteractionMap;
	
	UPROPERTY()
	class ANpcBase_OM* Npc;

	UPROPERTY()
	class UNpcBaseAnimInstance_OM* AnimInstance;

	UPROPERTY()
	float ChatDuration = 3.f;

	const float NeutralThreshold = 0.f;
	float EnemyThreshold;
	float FriendThreshold;
	


	UFUNCTION()
	void OnButton1Clicked() { ManageInteraction(Option1Button); };
	UFUNCTION()
	void OnButton2Clicked() { ManageInteraction(Option2Button); };
	UFUNCTION()
	void OnButton3Clicked() { ManageInteraction(Option3Button); };
	
};
