workspace "Sorter"
	configurations { "Debug", "Release" }

project "Sorter"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "%{prj.name}/*.cpp", "%{prj.name}/*.h" }
	includedirs { "%{prj.name}/dependencies/SFML-2.6.2/include", "%{prj.name}/dependencies/SDL-2.30.10/include" }
	libdirs { "%{prj.name}/dependencies/SFML-2.6.2/lib", "%{prj.name}/dependencies/SDL-2.30.10/lib/x64" }
	links { "sfml-graphics.lib", "sfml-window.lib", "sfml-system.lib", "kernel32.lib", "user32.lib", "gdi32.lib", "winspool.lib", "comdlg32.lib", "advapi32.lib", "shell32.lib", "ole32.lib", "oleaut32.lib", "uuid.lib", "odbc32.lib", "odbccp32.lib", "SDL2.lib", "SDL2main.lib", "SDL2test.lib" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		architecture "x64"
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		architecture "x64"
		optimize "On"