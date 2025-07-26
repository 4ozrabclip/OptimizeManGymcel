// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Gym/Concrete/SocialInteractionWidget_OM.h"
#include "Components/Button.h"
#include "AnimInstances/NpcBaseAnimInstance_OM.h"
#include "Actors/Characters/NPC/Abstract/NpcBase_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Actors/Characters/Player/PlayerController_OM.h"
#include "Components/Character/Concrete/SocialInteractionSystem_OM.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Gym/Concrete/ExerciseInteractWidget_OM.h"

void USocialInteractionWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeButtonStyles();

	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
	}
	if (!PlayerController)
	{
		PlayerController = Cast<APlayerController_OM>(Player->GetController());
	}

	Npc = Player->GetCurrentInteractedCharacter();
	if (!Npc)
	{
		UE_LOG(LogTemp, Error, TEXT("Npc is NULL"));
		return;
	}
	if (Npc->GetMesh()->GetAnimInstance())
	{

			UAnimInstance* ThisTempAnimInstance = Npc->GetMesh()->GetAnimInstance();
			UE_LOG(LogTemp, Warning, TEXT("Npc Has anim instance: %s"), 
		*ThisTempAnimInstance->GetClass()->GetFullName());
	}

	AnimInstance = Cast<UNpcBaseAnimInstance_OM>(Npc->GetAnimInstance());
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("NpcAnimInstance is NULL"));
		return;
	}
	SocialInteractionComponent = Player->GetComponentByClass<USocialInteractionSystem_OM>();
	if (!SocialInteractionComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Social Interaction Component is NULL"));
		return;
	}
	EnemyThreshold = SocialInteractionComponent->GetEnemyThreshold();
	FriendThreshold = SocialInteractionComponent->GetFriendThreshold();

	InitializeInteractionMap();
	
	SetSocialOptions();
	
	if (Option1Button && Option2Button && Option3Button)
	{
		Option1Button->OnClicked.RemoveAll(this);
		Option2Button->OnClicked.RemoveAll(this);
		Option3Button->OnClicked.RemoveAll(this);
		Option1Button->OnClicked.AddDynamic(this, &USocialInteractionWidget_OM::OnButton1Clicked);
		Option2Button->OnClicked.AddDynamic(this, &USocialInteractionWidget_OM::OnButton2Clicked);
		Option3Button->OnClicked.AddDynamic(this, &USocialInteractionWidget_OM::OnButton3Clicked);
	}

	SetDesiredSizeInViewport(FVector2D(1920, 1080));
}

void USocialInteractionWidget_OM::NativeDestruct()
{
	Super::NativeDestruct();
	InteractionMap.Empty();
	SocialInteractionTypes.Empty();
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void USocialInteractionWidget_OM::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	/*if (Npc && PlayerController)
	{
		FVector WorldLoc = Npc->GetActorLocation() + Offset;
		FVector2D ScreenPos;
		UGameplayStatics::ProjectWorldToScreen(PlayerController, WorldLoc, ScreenPos);
		SocialOptionsBorder->SetRenderTranslation(ScreenPos);
	}*/
		
}
void USocialInteractionWidget_OM::DarkModeToggle(const bool bIsDarkMode)
{
	Super::DarkModeToggle(bIsDarkMode);
	if (!WhiteBorder || !BlackBorder)
	{
		UE_LOG(LogTemp, Error, TEXT("White or Black border is null in social interaction widget"));
		return;
	}
	
	if (bIsDarkMode)
	{
		FSlateBrush DarkModeBrush;
		DarkModeBrush.SetResourceObject(WhiteBorder);
		SocialOptionsBorder->SetBrush(DarkModeBrush);
	}
	else
	{
		FSlateBrush LightModeBrush;
		LightModeBrush.SetResourceObject(BlackBorder);
		SocialOptionsBorder->SetBrush(LightModeBrush);
	}
}

void USocialInteractionWidget_OM::OnEmotionalStateChanged(EPlayerEmotionalStates InEmotionalState)
{
	InitializeButtonStyles();
}


void USocialInteractionWidget_OM::InitializeButtonStyles()
{
	if (!Player)
		Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	EPlayerEmotionalStates CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
	
	auto SetupButtonStyle = [this, CurrentEmotionalState](FButtonStyle& Style, int Index)
	{
		if (!SocialInteractionTypes.IsValidIndex(Index))
		{
			UE_LOG(LogTemp, Error, TEXT("Social Interaction Type Invalid Index"));
			return;
		}
		UTexture2D* Normal;
		UTexture2D* Pressed;
		if (CurrentEmotionalState == EPlayerEmotionalStates::GoblinMode)
		{
			Normal = SocialInteractionTypes[Index].EmojiType_Goblin;
			Pressed = SocialInteractionTypes[Index].PressedEmoji_Goblin;
		}
		else if (CurrentEmotionalState == EPlayerEmotionalStates::Gigachad)
		{
			Normal = SocialInteractionTypes[Index].EmojiType_Chad;
			Pressed = SocialInteractionTypes[Index].PressedEmoji_Chad;
		}
		else
		{
			Normal = SocialInteractionTypes[Index].EmojiType;
			Pressed = SocialInteractionTypes[Index].PressedEmoji;
		}

		Style.Normal.SetResourceObject(Normal);
		Style.Hovered.SetResourceObject(Normal);
		Style.Pressed.SetResourceObject(Pressed);
	
		Style.Normal.Margin = FMargin(0);
		Style.Hovered.Margin = FMargin(0);
		Style.Pressed.Margin = FMargin(0);
    
		Style.NormalPadding = FMargin(15);
		Style.PressedPadding = FMargin(15);
		
	};
	
	SetupButtonStyle(NeutralButtonStyle, 0);
	SetupButtonStyle(FriendlyButtonStyle, 1);
	SetupButtonStyle(RandyButtonStyle, 2);
	SetupButtonStyle(AngryButtonStyle, 3);
	SetupButtonStyle(DontListenButtonStyle, 4);
	SetupButtonStyle(FunnyButtonStyle, 5);
	SetupButtonStyle(HilariousButtonStyle, 6);
	SetupButtonStyle(AwkwardButtonStyle, 7);
	SetupButtonStyle(FlexingButtonStyle, 8);
	SetupButtonStyle(WeirdJokeButtonStyle, 9);
	
	
}

void USocialInteractionWidget_OM::InitializeInteractionMap()
{
	/* for each dialogue condition, we need a good, neutral, bad choice.
	 * always have atleast 1 neutral
	 * 
	 */

	
	//		---------- Full Neutral 
	// Neutral Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Neutral, NeutralThreshold),
		{ESocialType::Neutral, ESocialType::Friendly, ESocialType::Awkward
		});
	// Angry Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Angry, NeutralThreshold),
		{ESocialType::WeirdJoke, ESocialType::Awkward, ESocialType::Randy
		}); //if in angry mood, weird joke will be hit or miss rand
	// Randy Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Randy, NeutralThreshold),
		{ESocialType::Angry, ESocialType::Flexing, ESocialType::Friendly
		});
	// Happy Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Happy, NeutralThreshold),
		{ESocialType::Randy, ESocialType::Funny, ESocialType::Angry
		});
	// Disgusted Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Disgusted, NeutralThreshold),
		{ESocialType::WeirdJoke, ESocialType::DontListen, ESocialType::Awkward
		});
	// Uncomfortable Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Uncomfortable, NeutralThreshold),
	{ESocialType::Neutral, ESocialType::WeirdJoke, ESocialType::Friendly
	});

	//	------------- Enemy
	// Neutral Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Neutral, EnemyThreshold),
	{ESocialType::Neutral, ESocialType::WeirdJoke, ESocialType::Randy
	});
	// Angry Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Angry, EnemyThreshold),
		{ESocialType::Awkward, ESocialType::Angry, ESocialType::Hilarious
		});
	// Randy Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Randy, EnemyThreshold),
		{ESocialType::Randy, ESocialType::Flexing, ESocialType::Angry
		});
	// Happy Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Happy, EnemyThreshold),
		{ESocialType::Flexing, ESocialType::Awkward, ESocialType::Friendly
		});
	// Disgusted Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Disgusted, EnemyThreshold),
		{ESocialType::DontListen, ESocialType::WeirdJoke, ESocialType::Neutral
		});
	// Uncomfortable Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Uncomfortable, EnemyThreshold),
		{ESocialType::Neutral, ESocialType::Friendly, ESocialType::Randy
		});

	//	------------- Friend
	// Neutral Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Neutral, FriendThreshold),
	{ESocialType::Neutral, ESocialType::WeirdJoke, ESocialType::Friendly
	});
	// Angry Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Angry, FriendThreshold),
		{ESocialType::DontListen, ESocialType::Awkward, ESocialType::Hilarious
		});
	// Randy Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Randy, FriendThreshold),
		{ESocialType::Flexing, ESocialType::Neutral, ESocialType::Angry
		});
	// Happy Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Happy, FriendThreshold),
		{ESocialType::Randy, ESocialType::Funny, ESocialType::Awkward
		});
	// Disgusted Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Disgusted, FriendThreshold),
		{ESocialType::WeirdJoke, ESocialType::Awkward, ESocialType::Neutral
		});
	// Uncomfortable Mood
	InteractionMap.Add(FDialogueCondition(ENpcMood::Uncomfortable, FriendThreshold),
		{ESocialType::WeirdJoke, ESocialType::Awkward, ESocialType::Neutral
		});
}


void USocialInteractionWidget_OM::SetSocialOptions()
{
	if (!Option1Button || !Option2Button || !Option3Button)
	{
		UE_LOG(LogTemp, Error, TEXT("One or more buttons are null"));
		return;
	}
	
	// Set Threshold to work (rather than just single value), relative to friendship level
	float CurrentThreshold;
	if (Npc->GetFriendshipLevel() <= EnemyThreshold)
	{
		CurrentThreshold = EnemyThreshold;
	}
	else if (Npc->GetFriendshipLevel() >= FriendThreshold)
	{
		CurrentThreshold = FriendThreshold;
	}
	else
	{
		CurrentThreshold = NeutralThreshold;
	}
	
	FDialogueCondition CurrentDialogueCondition(Npc->GetCurrentMood(), CurrentThreshold);
	
	// Find the current button options based on dialogue condition :)
	if (const TArray<ESocialType>* SocialOptions = InteractionMap.Find(CurrentDialogueCondition))
	{
		TArray<ESocialType> Responses = *SocialOptions;
		if (Responses.Num() < 3) return;
		SetButton(Option1Button, Responses[0]);
		SetButton(Option2Button, Responses[1]);
		SetButton(Option3Button, Responses[2]);
	}

	//update friendship level bar
	ShowFriendshipLevel();
	
}

void USocialInteractionWidget_OM::ManageInteraction(const UButton* ClickedButton)
{
	if (!ClickedButton)
	{
		UE_LOG(LogTemp, Error, TEXT("ClickedButton passed into ManageInteraction is null"));
		return;
	}
	if (!AnimInstance)
	{
		AnimInstance = Npc->GetAnimInstance();
	}
	
	if (IsButtonThisStyle(&ClickedButton->GetStyle(), &NeutralButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::Neutral);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &FriendlyButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::Friendly);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &RandyButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::Randy);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &FunnyButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::Funny);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &DontListenButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::DontListen);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &AngryButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::Angry);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &HilariousButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::Hilarious);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &WeirdJokeButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::WeirdJoke);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &AwkwardButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::Awkward);
	}
	else if (IsButtonThisStyle(&ClickedButton->GetStyle(), &FlexingButtonStyle))
	{
		SocialInteractionComponent->ManageInteractionLogic(ESocialType::Flexing);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Button has no Style"));
		return;
	}
	/*
	FButtonStyle HilariousButtonStyle;
	FButtonStyle WeirdJokeButtonStyle;
	FButtonStyle AwkwardButtonStyle;
	FButtonStyle FlexingButtonStyle;
	 */
	Option1Button->SetIsEnabled(false);
	Option2Button->SetIsEnabled(false);
	Option3Button->SetIsEnabled(false);
	
	AnimInstance->SetIsTalking(true);

	SocialInteractionComponent->ProcessConversationData();

	
	ChatDuration = Npc->GetCurrentTalkTime() - 0.15f; //little offset so reenabling the buttons feels more natural
	GetWorld()->GetTimerManager().ClearTimer(ChatTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		ChatTimerHandle,
		[this]()
		{
			if (!IsValid(this) || !Option1Button || !Option2Button || !Option3Button || !AnimInstance) return;

			Option1Button->SetIsEnabled(true);
			Option2Button->SetIsEnabled(true);
			Option3Button->SetIsEnabled(true);
			
			AnimInstance->SetIsTalking(false);
			SetSocialOptions();
		},
		ChatDuration, 
		false 
	);
}

void USocialInteractionWidget_OM::ShowFriendshipLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Friendship Levvel from widg = %f"), Npc->GetFriendshipLevel());
	//FString FriendOrEnemy = Npc->GetFriendshipLevel() >= 0.5 ? 'Friend' : "Not friend";
	
	
	if (Npc->GetFriendshipLevel() > NeutralThreshold)
	{
		LikeBar->SetPercent(Npc->GetFriendshipLevel());
		DislikeBar->SetPercent(0.f);
	}
	else if (Npc->GetFriendshipLevel() < NeutralThreshold)
	{
		LikeBar->SetPercent(0.f);
		DislikeBar->SetPercent(Npc->GetFriendshipLevel() * -1);
	}
	else
	{
		LikeBar->SetPercent(0.f);
		DislikeBar->SetPercent(0.f);
	}
	
}

void USocialInteractionWidget_OM::SetButton(UButton* InButton, const ESocialType InSocialType) const
{
	if (!InButton)
	{
		UE_LOG(LogTemp, Error, TEXT("InButton passed into SetButton is null"));
		return;
	}
	
	const FButtonStyle* ButtonStyle = nullptr;


	switch (InSocialType)
	{
	case ESocialType::Neutral:
		ButtonStyle = &NeutralButtonStyle;
		break;
	case ESocialType::Friendly:
		ButtonStyle = &FriendlyButtonStyle;
		break;
	case ESocialType::Randy:
		ButtonStyle = &RandyButtonStyle;
		break;
	case ESocialType::Funny:
		ButtonStyle = &FunnyButtonStyle;
		break;
	case ESocialType::DontListen:
		ButtonStyle = &DontListenButtonStyle;
		break;
	case ESocialType::Angry:
		ButtonStyle = &AngryButtonStyle;
		break;
	case ESocialType::Awkward:
		ButtonStyle = &AwkwardButtonStyle;
		break;
	case ESocialType::Flexing:
		ButtonStyle = &FlexingButtonStyle;
		break;
	case ESocialType::WeirdJoke:
		ButtonStyle = &WeirdJokeButtonStyle;
		break;
	case ESocialType::Hilarious:
		ButtonStyle = &HilariousButtonStyle;
		break;
	default:
		ButtonStyle = &NeutralButtonStyle;
		break;
	}
	if (ButtonStyle)
	{
		InButton->SetStyle(*ButtonStyle);
	}
}

bool USocialInteractionWidget_OM::IsButtonThisStyle(const FButtonStyle* Style1, const FButtonStyle* Style2)
{
	if (!Style1 || !Style2)
	{
		UE_LOG(LogTemp, Error, TEXT("Style1 and/or Style2 passed into IsButtonThisStyle is null"));
		return false;
	}
	return Style1->Normal == Style2->Normal &&
	   Style1->Hovered == Style2->Hovered &&
	   Style1->Pressed == Style2->Pressed &&
	   Style1->Disabled == Style2->Disabled;
}

void USocialInteractionWidget_OM::OnExitButtonClicked()
{
	if (!Npc)
	{
		UE_LOG(LogTemp, Error, TEXT("Npc is NULL"));
		return;
	}
	Npc->EndDialog();
	Super::OnExitButtonClicked();
	SocialInteractionComponent->LeaveConversation();
}