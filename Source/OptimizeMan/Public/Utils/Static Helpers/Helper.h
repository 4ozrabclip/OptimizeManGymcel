// Copyright © 2025 4ozStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"

class UTodoManagementSubsystem;
/**
 * 
 */
class OPTIMIZEMAN_API Helper
{
public:
	Helper();
	~Helper();

	static UTodoManagementSubsystem* GetTodoManager(const UObject* InContext);
};
