-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- EnSound project description ----------

project "EnSound"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"

	defines {
		"ENSD_INTERNAL",
	}

	targetdir "$(SolutionDir)Builds/Binaries/$(Configuration)-$(Platform)"
	objdir "$(SolutionDir)Builds/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"**.lua",
		"**.txt",
		"**.md",
	}

	includedirs {
		"$(SolutionDir)Include/",
	}

	libdirs {

	}

	links { 
		"Loader",
	}