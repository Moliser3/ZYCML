// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BTDEditorTarget : TargetRules
{
	public BTDEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        // 升级到 V6
        DefaultBuildSettings = BuildSettingsVersion.V6;
        // 同时设置最新的包含顺序（可选，但建议）
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("BTD");
	}
}
