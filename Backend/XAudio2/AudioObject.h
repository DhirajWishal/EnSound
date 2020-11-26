// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <xaudio2.h>

namespace EnSound
{
	namespace XAudio2
	{
		class XAudio2Backend;

		/**
		 * Audio Object for the XAudio2 backend.
		 * This object stores information that is ready to be played using this backend.
		 */
		class AudioObject {
		public:
			/**
			 * Default constructor.
			 */
			AudioObject() {}

			/**
			 * Default destructor.
			 */
			~AudioObject() {}

			/**
			 * Terminate the object.
			 */
			void Terminate();

			/**
			 * Get source pointer.
			 *
			 * @return IXAudio2SourceVoice pointer.
			 */
			IXAudio2SourceVoice* GetSourcePointer() const { return pSourceData; }

			/**
			 * Get the address of the source voice structure.
			 *
			 * @return The IXAudio2SourceVoice pointer address.
			 */
			IXAudio2SourceVoice** GetSourceDataPointer() const { return const_cast<IXAudio2SourceVoice**>(&pSourceData); }

			/**
			 * Play the audio once.
			 */
			void PlayOnce();

		private:
			IXAudio2SourceVoice* pSourceData = nullptr;	// Audio source data.
		};
	}
}