-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "thirdparty/GLFW/include"
IncludeDir["glad"] = "thirdparty/glad/include"
IncludeDir["ImGui"] = "thirdparty/imgui"
IncludeDir["glm"] = "thirdparty/glm"
IncludeDir["stb_image"] = "thirdparty/stb_image"
IncludeDir["irrKlang"] = "thirdparty/irrKlang/include"
IncludeDir["JSONforModernC++"] = "thirdparty/JSONforModernCpp/include"

configurations 
{
	"Debug",
	"Release",
	"Dist"
}

platforms 
{
	"Win32",
	"Win64"
}

filter "platforms:Win32"
	system "windows"
	architecture "x86"

filter "platforms:Win64"
	system "windows"
	architecture "x86_64"

group "Dependencies"
	include "thirdparty/GLFW"
	include "thirdparty/glad"
	include "thirdparty/imgui"
group ""

project "Heirloom"
	kind "StaticLib"
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
	
	pchheader "hlpch.h"
	pchsource "src/hlpch.cpp"
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	files
	{
		"include/**.h",
		"src/**.h",
		"src/**.cpp",
		"thirdparty/stb_image/**.h",
		"thirdparty/stb_image/**.cpp",
		"thirdparty/glm/glm/**.hpp",
		"thirdparty/glm/glm/**.inl"
	}
	
	includedirs
	{
		"src",
		"thirdparty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.irrKlang}",
		"%{IncludeDir.JSONforModernCpp}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"irrKlang.lib"
	}

	filter "platforms:Win32"
		libdirs
		{
			"thirdparty/irrKlang/lib/Win32"
		}

	filter "platforms:Win64"
		libdirs 
		{
			"thirdparty/irrKlang/lib/Win64"
		}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"HL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
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