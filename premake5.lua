workspace "Sorter"
	configurations { "Debug", "Release" }

project "Sorter"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.cpp", "src/**.h" }
	includedirs { "dependencies/SFML-2.6.2/include", "dependencies/SDL-2.30.10/include" }
	libdirs { "dependencies/SFML-2.6.2/lib", "dependencies/SDL-2.30.10/lib/x64" }
	links { "sfml-graphics.lib", "sfml-window.lib", "sfml-system.lib", "kernel32.lib", "user32.lib", "gdi32.lib", "winspool.lib", "comdlg32.lib", "advapi32.lib", "shell32.lib", "ole32.lib", "oleaut32.lib", "uuid.lib", "odbc32.lib", "odbccp32.lib", "SDL2.lib", "SDL2main.lib", "SDL2test.lib" }

	filter "system:windows"
		postbuildcommands
        	{
            		{ "{COPY} dependencies/SDL-2.30.10/lib/x64/SDL2.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-graphics-2.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-system-2.dll bin/%{cfg.buildcfg}" },			
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-window-2.dll bin/%{cfg.buildcfg}" },
     		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		architecture "x64"
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		architecture "x64"
		optimize "On"