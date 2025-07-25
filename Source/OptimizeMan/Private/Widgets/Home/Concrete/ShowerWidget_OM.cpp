// Copyright © 2025 4ozStudio. All rights reserved.


#include "Widgets/Home/Concrete/ShowerWidget_OM.h"

#include "Components/Button.h"
#include "Game/Persistent/SubSystems/TodoManagementSubsystem.h"

void UShowerWidget_OM::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetIsFocusable(true);

	
	if (!Shower) return;
	
	if (HotShowerButton)
	{
		HotShowerButton->OnClicked.Clear();
		HotShowerButton->OnClicked.AddDynamic(Shower, &AShower_OM::TakeHotShower);
	}
	if (ColdShowerButton)
	{
		ColdShowerButton->OnClicked.Clear();
		ColdShowerButton->OnClicked.AddDynamic(Shower, &AShower_OM::TakeColdShower);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.Clear();
		ExitButton->OnClicked.AddDynamic(Shower, &AShower_OM::CloseWidget);
	}
}

