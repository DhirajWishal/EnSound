// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2/XAudio2Backend.h"
#pragma comment(lib,"xaudio2.lib")

#include "Core/Error/Logger.h"
#include "XAudio2/Loaders/WAVLoader.h"

namespace EnSound
{
	namespace XAudio2
	{
		/**
		 * Get WAVFormat data and insert it to the WAVEFORAMATEX structure.
		 *
		 * @param mFormat: The WAVFormat structure.
		 * @return WAVEFORMATEX structure.
		 */
		WAVEFORMATEX WAVFormatToWAVEFORMAT(const WAVFormat& mFormat)
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

		void XAudio2Backend::Initialize()
		{
			// Initialize the COINIT.
			HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

			// Create the XAudio2 instance.
			if (FAILED(XAudio2Create(pXAudio2.GetAddressOf(), 0)))
			{
				Logger::LogError(TEXT("Failed to create the XAudio2 instance!"));
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
				Logger::LogError(TEXT("Failed to create the XAudio2 mastering voice!"));
				CoUninitialize();
				return;
			}
		}

		void XAudio2Backend::Terminate()
		{
			// Terminate all the audio objects before terminating the backend.
			for (auto itr = mAudioObjects.begin(); itr != mAudioObjects.end(); itr++)
				itr->GetSourcePointer()->DestroyVoice();

			pMasteringVoice->DestroyVoice();
			pXAudio2.Reset();
			CoUninitialize();
		}

		/**
		 * Create an audio object using a WAV file.
		 *
		 * @param pAsset: The audio file path.
		 * @param pInstance: The XAudio2 instance.
		 * @param pHandle: The Audio Object Handle object pointer. Default is nullptr.
		 */
		AudioObject CreateFromWAV(const wchar* pAsset, IXAudio2* pInstance, AudioObjectHandle* pHandle = nullptr)
		{
			AudioObject mObject = {};
			WAVData wavData = {};
			uint8* pData = nullptr;

			// Load audio data.
			if (FAILED(LoadWAVAudioFromFileEx(pAsset, &pData, wavData)))
				Logger::LogError(TEXT("Failed to load the WAV file!"));

			// Set handle data if needed.
			if (pHandle)
			{
				pHandle->mFileType = AudioFileType::AUDIO_FILE_TYPE_WAV;
				pHandle->mBytesPerSecond = wavData.mWAVFormat.mAvgByteRate;
				pHandle->mLength = wavData.mLoopLength;
				pHandle->mSampleRate = wavData.mWAVFormat.mSampleRate;
			}

			// Create source voice.
			auto format = WAVFormatToWAVEFORMAT(wavData.mWAVFormat);
			pInstance->CreateSourceVoice(mObject.GetSourceDataPointer(), &format);

			XAUDIO2_BUFFER buffer = { 0 };
			buffer.pAudioData = wavData.pStartAudio;
			buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
			buffer.AudioBytes = wavData.mAudioBytes;

			if (wavData.mLoopLength > 0)
			{
				buffer.LoopBegin = wavData.mLoopStart;
				buffer.LoopLength = wavData.mLoopLength;
				buffer.LoopCount = 1; // We'll just assume we play the loop twice
			}

			if (wavData.pSeek)
			{
				XAUDIO2_BUFFER_WMA xwmaBuffer = { 0 };
				xwmaBuffer.pDecodedPacketCumulativeBytes = wavData.pSeek;
				xwmaBuffer.PacketCount = wavData.mSeekCount;

				if (FAILED(mObject.GetSourcePointer()->SubmitSourceBuffer(&buffer, &xwmaBuffer)))
				{
					Logger::LogError(TEXT("Failed to submit source buffer!"));
					mObject.GetSourcePointer()->DestroyVoice();
					return AudioObject();
				}
			}
			else if (FAILED(mObject.GetSourcePointer()->SubmitSourceBuffer(&buffer)))
			{
				Logger::LogError(TEXT("Failed to submit source buffer!"));
				mObject.GetSourcePointer()->DestroyVoice();
				return AudioObject();
			}

			return mObject;
		}

		AudioObjectHandle XAudio2Backend::CreateAudioObject(const wchar* pAsset)
		{
			// Create the handle instance.
			AudioObjectHandle mHandle = {};
			mHandle.pFileName = pAsset;

			// Create the object from using the WAV format.
			if (WString(pAsset).find(TEXT(".wav")) != WString::npos)
				mAudioObjects.insert(mAudioObjects.end(), std::move(CreateFromWAV(pAsset, GetInstance(), &mHandle)));

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
			if (WString(pAsset).find(TEXT(".wav")) != WString::npos)
				mObject = std::move(CreateFromWAV(pAsset, GetInstance()));

			// Play the audio.
			mObject.PlayOnce();

			// Terminate the object.
			mObject.Terminate();
		}

		void XAudio2Backend::PlayAudioOnce(AudioObjectHandle mHandle)
		{
			mAudioObjects.at(mHandle.GetHandle()).PlayOnce();
		}
	}
}