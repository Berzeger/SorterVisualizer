workspace "Sorter"
	configurations { "Debug", "Release" }

project "Sorter"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.cpp", "src/**.h" }
	includedirs { "dependencies/SFML-2.6.2/include", "dependencies/SDL-2.30.10/include" }
	libdirs { "dependencies/SFML-2.6.2/lib", "dependencies/SDL-2.30.10/lib/x64" }
	links { "SDL2.lib", "SDL2_ttf.lib", "SDL2main.lib", "SDL2test.lib" }

	filter "system:windows"
		postbuildcommands
		{
			{ "{COPY} dependencies/SDL-2.30.10/lib/x64/SDL2.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SDL-2.30.10/lib/x64/SDL2_ttf.dll bin/%{cfg.buildcfg}" },
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		architecture "x64"
		symbols "On"
		cppdialect "C++latest"
		links { "sfml-graphics-d.lib", "sfml-window-d.lib", "sfml-system-d.lib", "sfml-audio-d.lib" }
		postbuildcommands
		{	
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-graphics-d-2.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-system-d-2.dll bin/%{cfg.buildcfg}" },			
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-window-d-2.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-audio-d-2.dll bin/%{cfg.buildcfg}" }
		}

	filter "configurations:Release"
		defines { "NDEBUG" }
		architecture "x64"
		optimize "On"
		cppdialect "C++latest"
		links { "sfml-graphics.lib", "sfml-window.lib", "sfml-system.lib", "sfml-audio.lib" }
		postbuildcommands
		{	
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-graphics-2.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-system-2.dll bin/%{cfg.buildcfg}" },			
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-window-2.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-2.6.2/bin/sfml-audio-2.dll bin/%{cfg.buildcfg}" }
		}