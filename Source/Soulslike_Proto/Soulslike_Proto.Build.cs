// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Soulslike_Proto : ModuleRules
{
	public Soulslike_Proto(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "Soulslike_Proto" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "AIModule", "UMG" });
	}
}
