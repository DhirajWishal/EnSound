// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2/AudioObject.h"
#include "XAudio2/XAudio2Backend.h"
#include "Core/Error/Logger.h"

namespace EnSound
{
	namespace XAudio2
	{
		void AudioObject::Terminate()
		{
		}

		void AudioObject::PlayOnce(IXAudio2* pInstance)
		{
			// Create the source voice structure.
			pInstance->CreateSourceVoice(GetSourceDataPointer(), &mWaveFromat);

			// Submit buffers.
			if (GetBufferXWMAAddress()->pDecodedPacketCumulativeBytes)
			{
				if (FAILED(GetSourcePointer()->SubmitSourceBuffer(GetBufferAddress(), GetBufferXWMAAddress())))
				{
					Logger::LogError(STRING("Failed to submit audio data to the buffer!"));
					GetSourcePointer()->DestroyVoice();
					return;
				}
			}
			else
			{
				if (FAILED(GetSourcePointer()->SubmitSourceBuffer(GetBufferAddress())))
				{
					Logger::LogError(STRING("Failed to submit audio data to the buffer!"));
					GetSourcePointer()->DestroyVoice();
					return;
				}
			}

			// Start playing.
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

			// Terminate the voice.
			GetSourcePointer()->DestroyVoice();
		}
	}
}