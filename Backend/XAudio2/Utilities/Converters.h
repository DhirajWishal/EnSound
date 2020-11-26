// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Formats/WAV/Format.h"
#include <xaudio2.h>

namespace EnSound
{
	namespace XAudio2
	{
		/**
		 * Get WAVFormat data and insert it to the WAVEFORAMATEX structure.
		 *
		 * @param mFormat: The WAVFormat structure.
		 * @return WAVEFORMATEX structure.
		 */
		WAVEFORMATEX WAVFormatToWAVEFORMATEX(const WAVFormat& mFormat);
	}
}