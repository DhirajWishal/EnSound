-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Loader Tests project description ----------

project "LoaderTests"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"
	staticruntime "On"
	systemversion "latest"

	targetdir "$(SolutionDir)Builds/Tests/Binaries/$(Configuration)-$(Platform)/$(ProjectName)"
	objdir "$(SolutionDir)Builds/Tests/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"**.lua"
	}

	includedirs {
		"$(SolutionDir)Include",
		"$(SolutionDir)Tests/LoaderTests",
	}

	links {
		"Loader",
	}