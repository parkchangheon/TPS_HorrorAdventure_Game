// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPS_C_Project : ModuleRules
{
	public TPS_C_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks", "NavigationSystem", "UMG", "LevelSequence", "MovieScene"});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate", "SlateCore"
		});
	}

}
