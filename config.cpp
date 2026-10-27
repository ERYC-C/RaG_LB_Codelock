class CfgPatches
{
	class RaG_LB_Codelock
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"RaG_Core",
			"LBmaster_BetterCodelock"
		};
	};
};

class CfgMods
{
	class RaG_LB_Codelock
	{
		dir = "RaG_LB_Codelock";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "RaG LB Codelock";
		credits = "";
		author = "ERYC";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"RaG_LB_Codelock/scripts/4_World"};
			};
		};
	};
};
