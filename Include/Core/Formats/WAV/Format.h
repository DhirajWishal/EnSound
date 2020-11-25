// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/DataTypes/Types.h"

namespace EnSound
{
	/**
	 * WAV file format.
	 * This structure contains information about a single WAV file.
	 */
	struct FormatWAV {
		uint64 mSampleRate = 0;			// Sample rate of the audio.
		uint64 mAvgByteRate = 0;		// Averate number of bytes played per second.
		uint16 mFormatTag = 0;			// Format tag.
		uint16 mChannels = 0;			// The number of channels in the audio file.
		uint16 mBlockAlignment = 0;		// Alignment of the memory block.
		uint16 mBitsPerSample = 0;		// Number of bits per sample.
		uint16 mCBSize = 0;				// Size of the additional information.
	};
}