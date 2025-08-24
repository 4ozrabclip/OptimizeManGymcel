// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Both/Concrete/EndPlaytestWidget_OM.h"

#include "Animation/DebugSkelMeshComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UEndPlaytestWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();

	if (ExitButton)
	{
		if (!ExitButton->OnClicked.IsAlreadyBound(this, &UEndPlaytestWidget_OM::EndPlaytest))
			ExitButton->OnClicked.AddDynamic(this, &UEndPlaytestWidget_OM::EndPlaytest);
	}


	if (EndAnim)
		PlayAnimation(EndAnim);
	
}

void UEndPlaytestWidget_OM::NativeDestruct()
{
	if (GoodbyeAnim && GetAnimationState(GoodbyeAnim)->IsPlayingForward())
		GetAnimationState(GoodbyeAnim)->Stop();
	if (EndAnim && GetAnimationState(EndAnim)->IsPlayingForward())
		GetAnimationState(EndAnim)->Stop();

	Super::NativeDestruct();

}

void UEndPlaytestWidget_OM::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Levels/MainMenu"));
	
}

void UEndPlaytestWidget_OM::EndPlaytest()
{
	if (GoodbyeAnim)
		PlayAnimation(GoodbyeAnim);

	OnAnimationFinished_Implementation(GoodbyeAnim);
}
