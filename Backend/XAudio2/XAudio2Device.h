// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Objects/AudioObjectHandle.h"

namespace EnSound
{
	namespace XAudio2
	{
		/**
		 * XAudio2 Device object.
		 * This object stores information about a single XAudio2 device.
		 */
		class Device {
		public:
			/**
			 * Default constructor.
			 */
			Device() {}

			/**
			 * Default destructor.
			 */
			~Device() {}

			/**
			 * Initialize the device.
			 */
			void Initialize();

			/**
			 * Play audio using an audio object handle.
			 *
			 * @param aHandle: The audio handle.
			 */
			void PlayAudio(AudioObjectHandle aHandle);
		};
	}
}