// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OptimizeMan : ModuleRules
{
	public OptimizeMan(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput" , 
			"Slate",
			"SlateCore", 
			"GameplayTags",
			"GameplayAbilities",
			"GameplayTasks",
			"LevelSequence",
			"MovieScene",
			"AIModule",
			"NavigationSystem",
			"MetasoundEngine",
			"UMG", 
			"CinematicCamera",
			"Niagara",
			"NiagaraCore",
		});
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "MetasoundEditor", "AnimGraph" });
		}
		

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
