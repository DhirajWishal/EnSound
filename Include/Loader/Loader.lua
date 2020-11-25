-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Loader project description ----------

project "Loader"
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

	}