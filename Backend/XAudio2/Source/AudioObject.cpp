// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2/AudioObject.h"
#include "XAudio2/XAudio2Backend.h"

namespace EnSound
{
	namespace XAudio2
	{
		void AudioObject::Terminate()
		{
			GetSourcePointer()->DestroyVoice();
		}
		
		void AudioObject::PlayOnce()
		{
			auto hr = GetSourcePointer()->Start(0);

			// Let the sound play
			BOOL isRunning = TRUE;
			while (SUCCEEDED(hr) && isRunning)
			{
				XAUDIO2_VOICE_STATE state;
				GetSourcePointer()->GetState(&state);
				isRunning = (state.BuffersQueued > 0) != 0;

				// Wait till the escape key is pressed
				if (GetAsyncKeyState(VK_ESCAPE))
					break;

				Sleep(10);
			}
		}
	}
}