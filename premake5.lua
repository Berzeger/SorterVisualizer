workspace "Sorter"
	configurations { "Debug", "Release", "DebugWithAnalysis" }

project "Sorter"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.cpp", "src/**.h" }
	includedirs { "dependencies/SFML-3.0.0/include", "dependencies/SDL-2.30.10/include" }
	libdirs { "dependencies/SFML-3.0.0/lib", "dependencies/SDL-2.30.10/lib/x64" }
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
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-graphics-d-3.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-system-d-3.dll bin/%{cfg.buildcfg}" },			
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-window-d-3.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-audio-d-3.dll bin/%{cfg.buildcfg}" }
		}
		
	filter "configurations:DebugWithAnalysis"
		defines { "DEBUG" }
		architecture "x64"
		symbols "On"
		cppdialect "C++latest"
		links { "sfml-graphics-d.lib", "sfml-window-d.lib", "sfml-system-d.lib", "sfml-audio-d.lib" }
		postbuildcommands
		{	
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-graphics-d-3.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-system-d-3.dll bin/%{cfg.buildcfg}" },			
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-window-d-3.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-audio-d-3.dll bin/%{cfg.buildcfg}" }
		}
		clangtidy("On")
		runcodeanalysis("On")

	filter "configurations:Release"
		defines { "NDEBUG" }
		architecture "x64"
		optimize "On"
		cppdialect "C++latest"
		links { "sfml-graphics.lib", "sfml-window.lib", "sfml-system.lib", "sfml-audio.lib" }
		postbuildcommands
		{	
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-graphics-3.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-system-3.dll bin/%{cfg.buildcfg}" },			
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-window-3.dll bin/%{cfg.buildcfg}" },
			{ "{COPY} dependencies/SFML-3.0.0/bin/sfml-audio-3.dll bin/%{cfg.buildcfg}" }
		}