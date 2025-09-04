// Copyright © 2025 4ozStudio. All rights reserved.


#include "Utils/Static Helpers/Helper.h"


Helper::Helper()
{
}

Helper::~Helper()
{
}

UTodoManagementSubsystem* Helper::GetTodoManager(const UObject* InContext)
{
	if (const UGameInstance* GI = InContext->GetWorld()->GetGameInstance())
	{
		return GI->GetSubsystem<UTodoManagementSubsystem>();
	}
	return nullptr;
}
