// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/DataTypes/Types.h"

namespace EnSound
{
	/**
	 * Audio File Type enum.
	 */
	enum class AudioFileType : uint8 {
		AUDIO_FILE_TYPE_UNKNOWN,
		AUDIO_FILE_TYPE_WAV,
		AUDIO_FILE_TYPE_MP3,
		AUDIO_FILE_TYPE_OGG,
		AUDIO_FILE_TYPE_FLAC,
	};

	/**
	 * Audio Object Handle.
	 * This object holds information about a single audio object. Since audio data are stored in the backends itself,
	 * this object has an ID/ index to the actual audio data. Aditionally this contains some basic information about the
	 * audio file.
	 */
	class AudioObjectHandle {
	public:
		/**
		 * Default constructor.
		 */
		AudioObjectHandle() {}

		/**
		 * Default destructor.
		 */
		~AudioObjectHandle() {}

		/**
		 * Get the handle of the audio object.
		 *
		 * @return The audio object handle.
		 */
		const uint64 GetHandle() const { return mHandle; }

		/**
		 * Get the name (file name) of the audio object.
		 *
		 * @return Const wchar pointer.
		 */
		const wchar* GetName() const { return pFileName; }

		/**
		 * Get the length of the audio.
		 *
		 * @return The length in miliseconds.
		 */
		uint64 GetLength() const { return mLength; }

		/**
		 * Get the sample rate.
		 *
		 * @return The sample rate in Hz.
		 */
		uint64 GetSampleRate() const { return mSampleRate; }

		/**
		 * Get the number of bytes played per second.
		 *
		 * @return The number of bytes per second.
		 */
		uint64 GetBytesPerSecond() const { return mBytesPerSecond; }

		/**
		 * Get the type of the audio file.
		 *
		 * @return The audio file type.
		 */
		AudioFileType GetType() const { return mFileType; }

	public:
		uint64 mHandle = 0;	// The backend audio handle.
		const wchar* pFileName = nullptr;	// The name of the audio file.

		uint64 mLength = 0;	// Length of the audio.
		uint64 mSampleRate = 0;	// The sample rate of the audio.
		uint64 mBytesPerSecond = 0;	// The number of bytes played per second.

		AudioFileType mFileType = AudioFileType::AUDIO_FILE_TYPE_UNKNOWN;	// The type of the audio file.
	};
}