// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class woolfnichCOMP313Ass1EditorTarget : TargetRules
{
	public woolfnichCOMP313Ass1EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("woolfnichCOMP313Ass1");
	}
}
