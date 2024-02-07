// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class striVe : ModuleRules
{
	public striVe(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
