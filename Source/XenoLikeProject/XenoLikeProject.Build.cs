// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XenoLikeProject : ModuleRules
{
	public XenoLikeProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"XenoLikeProject",
			"XenoLikeProject/Variant_Platforming",
			"XenoLikeProject/Variant_Platforming/Animation",
			"XenoLikeProject/Variant_Combat",
			"XenoLikeProject/Variant_Combat/AI",
			"XenoLikeProject/Variant_Combat/Animation",
			"XenoLikeProject/Variant_Combat/Gameplay",
			"XenoLikeProject/Variant_Combat/Interfaces",
			"XenoLikeProject/Variant_Combat/UI",
			"XenoLikeProject/Variant_SideScrolling",
			"XenoLikeProject/Variant_SideScrolling/AI",
			"XenoLikeProject/Variant_SideScrolling/Gameplay",
			"XenoLikeProject/Variant_SideScrolling/Interfaces",
			"XenoLikeProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
