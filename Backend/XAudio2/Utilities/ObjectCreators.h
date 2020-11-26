// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "XAudio2/AudioObject.h"
#include "Core/DataTypes/Types.h"
#include "Core/Objects/AudioObjectHandle.h"

namespace EnSound
{
	namespace XAudio2
	{
		/**
		 * Create an audio object using a WAV file.
		 *
		 * @param pAsset: The audio file path.
		 * @param pHandle: The Audio Object Handle object pointer. Default is nullptr.
		 */
		AudioObject CreateFromWAV(const wchar* pAsset, AudioObjectHandle* pHandle = nullptr);
	}
}