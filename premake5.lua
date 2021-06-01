workspace "QBert"
	startproject "QBert"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "Heirloom"

project "QBert"
	location "QBert"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "On"
	warnings "Extra"

	flags
	{
		"FatalWarnings"
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Heirloom/thirdparty/spdlog/include",
		"Heirloom/include",
		"Heirloom/src",
		"Heirloom/thirdparty",
		"Heirloom/%{IncludeDir.GLFW}",
		"Heirloom/%{IncludeDir.glm}",
		"Heirloom/%{IncludeDir.irrKlang}"
	}

	links
	{
		"Heirloom"
	}
	
	filter "configurations:Debug"
		defines
		{
			"HL_DEBUG",
			"HL_PROFILE"
		}
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines
		{
			"HL_RELEASE",
			"HL_PROFILE"
		}
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "HL_DIST"
		runtime "Release"
		optimize "On"

	filter "platforms:Win32"
		postbuildcommands 
		{
			"{COPY} \"$(SolutionDir)QBert\\assets\" \"$(TargetDir)\\assets\\\"",
			"{COPY} \"$(SolutionDir)Heirloom\\thirdparty\\irrKlang\\bin\\Win32\\*.dll\" \"$(TargetDir)\""
		}
	
	filter "platforms:Win64"
		postbuildcommands 
		{
			"{COPY} \"$(SolutionDir)QBert\\assets\" \"$(TargetDir)\\assets\\\"",
			"{COPY} \"$(SolutionDir)Heirloom\\thirdparty\\irrKlang\\bin\\Win64\\*.dll\" \"$(TargetDir)\""
		}