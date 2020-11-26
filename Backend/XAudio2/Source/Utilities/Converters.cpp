// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2/Utilities/Converters.h"

namespace EnSound
{
	namespace XAudio2
	{
		WAVEFORMATEX WAVFormatToWAVEFORMATEX(const WAVFormat& mFormat)
		{
			WAVEFORMATEX mWaveFormat = {};
			mWaveFormat.wFormatTag = mFormat.mFormatTag;
			mWaveFormat.nChannels = mFormat.mChannels;
			mWaveFormat.nSamplesPerSec = static_cast<uint32>(mFormat.mSampleRate);
			mWaveFormat.nAvgBytesPerSec = static_cast<uint32>(mFormat.mAvgByteRate);
			mWaveFormat.nBlockAlign = mFormat.mBlockAlignment;
			mWaveFormat.wBitsPerSample = mFormat.mBitsPerSample;
			mWaveFormat.cbSize = mFormat.mCBSize;

			return mWaveFormat;
		}
	}
}