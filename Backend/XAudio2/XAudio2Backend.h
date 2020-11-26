// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "AudioObject.h"
#include "XAudio2Device.h"
#include "Core/DataTypes/Types.h"

#include <wrl\client.h>

namespace EnSound
{
	namespace XAudio2
	{
		/**
		 * XAudio2 Backend object.
		 * This object is responsible of creating XAudio2 devices.
		 */
		class XAudio2Backend {
		public:
			/**
			 * Default constructor.
			 */
			XAudio2Backend() {}

			/**
			 * Default destructor.
			 */
			~XAudio2Backend() {}

			/**
			 * Get the XAudio2 instance pointer.
			 *
			 * @return THe IXAudio2 pointer.
			 */
			IXAudio2* GetInstance() const { return pXAudio2.Get(); }

			/**
			 * Get the mastering voice structure pointer.
			 *
			 * @return The IXAudio2MasteringVoice pointer.
			 */
			IXAudio2MasteringVoice* GetMasteringVoice() const { return pMasteringVoice; }

		public:
			/**
			 * Initialize the backend.
			 */
			void Initialize();

			/**
			 * Terminate the backend.
			 */
			void Terminate();

		public:
			/**
			 * Create a new audio object.
			 *
			 * @param pAsset: The asset path.
			 * @return Audio Object Handle.
			 */
			AudioObjectHandle CreateAudioObject(const wchar* pAsset);

			/**
			 * Destroy an audio object using its handle.
			 *
			 * @param mHandle: The handle of the audio object.
			 */
			void DestroyAudioObject(AudioObjectHandle mHandle);

		public:
			/**
			 * Play audio once directly from the file. 
			 * Note that this does not stream data directly to the device!
			 * 
			 * @param pAsset: The asset path.
			 */
			void PlayAudioOnce(const wchar* pAsset);

			/**
			 * Play audio once.
			 *
			 * @param mHandle: The audio object handle.
			 */
			void PlayAudioOnce(AudioObjectHandle mHandle);

		private:
			Microsoft::WRL::ComPtr<IXAudio2> pXAudio2;	// XAudio2 instance.
			IXAudio2MasteringVoice* pMasteringVoice = nullptr;	// XAudio2 mastering voice pointer.
			Vector<AudioObject> mAudioObjects;	// All the created audio objects.
		};
	}
}