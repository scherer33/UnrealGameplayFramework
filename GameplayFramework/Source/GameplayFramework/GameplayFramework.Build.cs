// Copyright (c) 2026 PH Scherer. MIT License.

using UnrealBuildTool;
using System.Collections.Generic;

public class GameplayFramework : ModuleRules
{
	public GameplayFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine"
		});
	}
}
