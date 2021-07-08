// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class woolfnichCOMP313Ass1 : ModuleRules
{
	public woolfnichCOMP313Ass1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
