-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

workspace "EnSound"
	architecture "x64"

	platforms { "Windows", "Unix", "Mac" }

	configurations {
		"Debug",
		"Release"
	}

	filter "platforms:Windows"
		system "windows"

	filter "platforms:Unix"
		system "linux"

	filter "platforms:Mac"
		system "macosx"

	filter "configurations:Debug"
		defines { "ENSD_DEBUG" }
		symbols "On"
		
	filter "configurations:Release"
		defines { "ENSD_RELEASE" }
		optimize "On"


-- Libraries
IncludeDir = {}
IncludeDir["SDL2"] = "$(SolutionDir)Dependencies/ThirdParty/SDL2-2.0.12/include"

-- Binaries
IncludeLib = {}
IncludeLib["SDL2"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/SDL2-2.0.12/bin/x64/"

group "Include"
include "Include/Core/Core.lua"
include "Include/EnSound/EnSound.lua"

group "Backends"
include "Backend/XAudio2/XAudio2.lua"

group "Tests"
include "Tests/CoreTests/CoreTests.lua"
include "Tests/EnSoundTests/EnSoundTests.lua"

include "Tests/XAudio2Tests/XAudio2Tests.lua"