// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2/XAudio2Backend.h"
#pragma comment(lib,"xaudio2.lib")

#include "Core/Error/Logger.h"
#include "XAudio2/Loaders/WAVLoader.h"
#include "XAudio2/Utilities/Converters.h"
#include "XAudio2/Utilities/ObjectCreators.h"

namespace EnSound
{
	namespace XAudio2
	{
		void XAudio2Backend::Initialize()
		{
			// Initialize the COINIT.
			HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

			// Create the XAudio2 instance.
			if (FAILED(XAudio2Create(pXAudio2.GetAddressOf(), 0)))
			{
				Logger::LogError(STRING("Failed to create the XAudio2 instance!"));
				CoUninitialize();
				return;
			}

#ifdef ENSD_DEBUG
			// Initailize the debugger.
			XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
			debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
			debug.BreakMask = XAUDIO2_LOG_ERRORS;
			pXAudio2->SetDebugConfiguration(&debug, 0);
#endif // ENSD_DEBUG


			// Create the XAudio2 mastering voice.
			if (FAILED(pXAudio2->CreateMasteringVoice(&pMasteringVoice)))
			{
				Logger::LogError(STRING("Failed to create the XAudio2 mastering voice!"));
				CoUninitialize();
				return;
			}
		}

		void XAudio2Backend::Terminate()
		{
			mAudioObjects.clear();
			pMasteringVoice->DestroyVoice();
			pXAudio2.Reset();
			CoUninitialize();
		}

		AudioObjectHandle XAudio2Backend::CreateAudioObject(const wchar* pAsset)
		{
			// Create the handle instance.
			AudioObjectHandle mHandle = {};
			mHandle.pFileName = pAsset;

			// Create the object from using the WAV format.
			if (WString(pAsset).find(STRING(".wav")) != WString::npos)
				mAudioObjects.insert(mAudioObjects.end(), std::move(CreateFromWAV(pAsset, &mHandle)));

			// Get the handle and return it.
			mHandle.mHandle = mAudioObjects.size() - 1;
			return mHandle;
		}

		void XAudio2Backend::DestroyAudioObject(AudioObjectHandle mHandle)
		{
			mAudioObjects.at(mHandle.GetHandle()).Terminate();
		}

		void XAudio2Backend::PlayAudioOnce(const wchar* pAsset)
		{
			// Create the object instance.
			AudioObject mObject = {};

			// Play the WAV file once.
			if (WString(pAsset).find(STRING(".wav")) != WString::npos)
				mObject = std::move(CreateFromWAV(pAsset));

			// Play the audio.
			mObject.PlayOnce(GetInstance());

			// Terminate the object.
			mObject.Terminate();
		}

		void XAudio2Backend::PlayAudioOnce(AudioObjectHandle mHandle)
		{
			(mAudioObjects.data() + mHandle.GetHandle())->PlayOnce(GetInstance());
		}

		void XAudio2Backend::PlayLoop(const wchar* pAsset, uint64 loopCount)
		{
			// Create the object instance.
			AudioObject mObject = {};

			// Play the WAV file once.
			if (WString(pAsset).find(STRING(".wav")) != WString::npos)
				mObject = std::move(CreateFromWAV(pAsset));

			// Play the audio.
			while (loopCount--)
				mObject.PlayOnce(GetInstance());

			// Terminate the object.
			mObject.Terminate();
		}

		void XAudio2Backend::PlayLoop(AudioObjectHandle mHandle, uint64 loopCount)
		{
			// Get the required audio object.
			auto pAudioObject = (mAudioObjects.data() + mHandle.GetHandle());

			// Play the audio file.
			while (loopCount--)
				pAudioObject->PlayOnce(GetInstance());
		}
	}
}