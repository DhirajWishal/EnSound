// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/DataTypes/Types.h"

/**
 * Make a tag using 4 characters.
 * This is well defined in the MSDN documentation about XAudio2: https://docs.microsoft.com/en-us/windows/win32/xaudio2/how-to--load-audio-data-files-in-xaudio2
 */
#define MAKE_TAG(ch0, ch1, ch2, ch3)									\
				  (static_cast<uint32>(static_cast<uint8>(ch0))			\
				| (static_cast<uint32>(static_cast<uint8>(ch1)) << 8)	\
				| (static_cast<uint32>(static_cast<uint8>(ch2)) << 16)	\
				| (static_cast<uint32>(static_cast<uint8>(ch3)) << 24))

namespace EnSound
{
	/**
	 * WAV File Tag enum.
	 */
	enum class WAVFileTag : const uint32 {
		WAV_FILE_TAG_UNKNOWN = 0U,
		WAV_FILE_TAG_RIFF = MAKE_TAG('R', 'I', 'F', 'F'),
		WAV_FILE_TAG_FORMAT = MAKE_TAG('f', 'm', 't', ' '),
		WAV_FILE_TAG_DATA = MAKE_TAG('d', 'a', 't', 'a'),
		WAV_FILE_TAG_WAVE_FILE = MAKE_TAG('W', 'A', 'V', 'E'),
		WAV_FILE_TAG_XWMA_FILE = MAKE_TAG('X', 'W', 'M', 'A'),
		WAV_FILE_TAG_DLS_SAMPLE = MAKE_TAG('w', 's', 'm', 'p'),
		WAV_FILE_TAG_MIDI_SAMPLE = MAKE_TAG('s', 'm', 'p', 'l'),
		WAV_FILE_TAG_XWMA_DPDS = MAKE_TAG('d', 'p', 'd', 's'),
		WAV_FILE_TAG_XMA_SEEK = MAKE_TAG('s', 'e', 'e', 'k'),
	};

	/**
	 * WAV file format.
	 * This structure contains information about a single WAV file.
	 */
	struct WAVFormat {
		uint16 mFormatTag = 0;			// Format tag.
		uint16 mChannels = 0;			// The number of channels in the audio file.
		uint64 mSampleRate = 0;			// Sample rate of the audio.
		uint64 mAvgByteRate = 0;		// Averate number of bytes played per second.
		uint16 mBlockAlignment = 0;		// Alignment of the memory block.
		uint16 mBitsPerSample = 0;		// Number of bits per sample.
		uint16 mCBSize = 0;				// Size of the additional information.
	};

	/**
	 * WAV Data structure.
	 * This structure contains information about a single WAV file.
	 */
	struct WAVData {
		WAVFormat mWAVFormat = {};	// Wave format.
		const uint32* pSeek = nullptr;       // Note: XMA Seek data is Big-Endian
		const uint8_t* pStartAudio = nullptr;	// Audio playback starting point.
		uint32 mAudioBytes = 0;	// Number of audio bytes to play.
		uint32 mLoopStart = 0;	// Loop start index.
		uint32 mLoopLength = 0;	// The length of the loop.
		uint32 mSeekCount = 0;	// The seek count.
	};

#pragma pack(push, 1)
	/**
	 * RIFF Chunk structure.
	 * RIFF stands for Resource Interchange File Format (https://docs.microsoft.com/en-us/windows/win32/xaudio2/resource-interchange-file-format--riff-).
	 */
	struct RIFFChunk {
		WAVFileTag mTag = WAVFileTag::WAV_FILE_TAG_UNKNOWN;
		uint32 mSize = 0;
	};

	/**
	 * RIFF Chunk Header structure.
	 */
	struct RIFFChunkHeader {
		WAVFileTag mTag = WAVFileTag::WAV_FILE_TAG_UNKNOWN;
		uint32 mSize = 0;
		WAVFileTag mRiff = WAVFileTag::WAV_FILE_TAG_UNKNOWN;
	};

	/**
	 * DLS Loop structure.
	 */
	struct DLSLoop {
		static const uint32 Forward = 0x00000000;
		static const uint32 Release = 0x00000001;

		uint32 mSize = 0;
		uint32 mLoopType = 0;
		uint32 mLoopStart = 0;
		uint32 mLoopLength = 0;
	};

	/**
	 * RIFF DLS Sample structure.
	 */
	struct RIFFDLSSample {
		static const uint32 NoTruncation = 0x00000001;
		static const uint32 NoCompression = 0x00000002;

		uint32 mSize = 0;
		uint16 mUnityNote = 0;
		int16 mFineTune = 0;
		int32 mGain = 0;
		uint32 mOptions = 0;
		uint32 mLoopCount = 0;
	};

	/**
	 * MIDI Loop structure.
	 */
	struct MIDILoop {
		static const uint32 Forward = 0x00000000;
		static const uint32 Alternating = 0x00000001;
		static const uint32 Backward = 0x00000002;

		uint32 mCuePointId = 0;
		uint32 mType = 0;
		uint32 mStart = 0;
		uint32 mEnd = 0;
		uint32 mFraction = 0;
		uint32 mPlayCount = 0;
	};

	/**
	 * RIFF MIDI Sample structure.
	 */
	struct RIFFMIDISample {
		uint32 mManufacturerId = 0;
		uint32 mProductId = 0;
		uint32 mSamplePeriod = 0;
		uint32 mUnityNode = 0;
		uint32 mPitchFraction = 0;
		uint32 mSMPTEFormat = 0;
		uint32 mSMPTEOffset = 0;
		uint32 mLoopCount = 0;
		uint32 mSamplerData = 0;
	};
#pragma pack(pop)

	/**
	 * Check if the RIFF Chunk size is valid.
	 */
	static_assert(sizeof(RIFFChunk) == 8, "RIFFChunk structure size mismatch!");

	/**
	 * Check if the RIFF Chunk Header size is valid.
	 */
	static_assert(sizeof(RIFFChunkHeader) == 12, "RIFFChunkHeader structure size mismatch!");

	/**
	 * Check if the DLS Loop size is valid.
	 */
	static_assert(sizeof(DLSLoop) == 16, "DLSLoop structure size mismatch!");

	/**
	 * Check if the RIFF DLS Sample size is valid.
	 */
	static_assert(sizeof(RIFFDLSSample) == 20, "RIFFDLSSample structure size mismatch!");

	/**
	 * Check if the MIDI Loop size is valid.
	 */
	static_assert(sizeof(MIDILoop) == 24, "MIDILoop structure size mismatch!");

	/**
	 * Check if the RIFF MIDI Sample size is valid.
	 */
	static_assert(sizeof(RIFFMIDISample) == 36, "RIFFMIDISample structure size mismatch!");
}