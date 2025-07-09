// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Home/Concrete/WakeUpWidget_OM.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Audio/Concrete/NotificationAudio_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

void UWakeUpWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("Wake up Construct Called"));

	
	
	TaskOptionPanel_0->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionPanel_1->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionPanel_2->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionPanel_3->SetVisibility(ESlateVisibility::Hidden);
	TaskOptionPanel_4->SetVisibility(ESlateVisibility::Hidden);
	SetTodoOptions();
	UpdateFakeTodoList();
	
}
