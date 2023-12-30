project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir "bin/%{cfg.buildcfg}"
    objdir    "bin/obj/%{cfg.buildcfg}"
	
	files{
		"**.h",
		"**.hpp",
		"**.cpp",

	}
	
	includedirs {
		"include",
		"../include",
	}	
	
	libdirs {
		"../libs/GLFW",
		"../libs/GLEW",
	}
	
	links{
	    "glew32s",
		"glfw3_mt",
        "opengl32",
        "Winmm",
	}
	
	defines {
        "GLEW_STATIC",
    }
	
	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "ENG_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "ENG_RELEASE"
		runtime "Release"
		optimize "on"