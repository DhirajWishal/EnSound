// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/DataTypes/Types.h"
#include "Core/Formats/WAV/Format.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <memory>
#include <mmreg.h>

namespace EnSound
{
	namespace XAudio2
	{
		/**
		 * Find the chunk of a given tag.
		 *
		 * @param data: The audio data.
		 * @param sizeBytes: The byte size of the audio data.
		 * @param tag: The tag to be searched for.
		 * @return The RIFFChunk pointer.
		 */
		const RIFFChunk* FindChunk(const uint8* data, uint64 sizeBytes, WAVFileTag tag);

		/**
		 * Find Format and Data function.
		 *
		 * @param wavData: The WAV file data.
		 * @param wavDataSize: The byte size of the WAV data.
		 * @param pwfx: The pointer of the WAVEFORMATEX structure.
		 * @param pdata: The output data pointer.
		 * @param dataSize: The output data size.
		 * @param dpds: Boolean check value.
		 * @param seek: Boolean seek value.
		 * @return HRESULT value.
		 */
		HRESULT FindFormatAndData(const uint8* wavData, uint64 wavDataSize, const WAVEFORMATEX** pwfx, const uint8** pdata, uint32* dataSize, bool& dpds, bool& seek);

		/**
		 * Find Loop Info.
		 *
		 * @param wavData: The WAV audio data.
		 * @param wavDataSize: The size of the WAV audio data.
		 * @param pLoopStart: The start of the loop.
		 * @param pLoopLength: The length of the loop.
		 * @return HRESULT value.
		 */
		HRESULT FindLoopInfo(const uint8* wavData, uint64 wavDataSize, uint32* pLoopStart, uint32* pLoopLength);

		/**
		 * Find Table.
		 *
		 * @param wavData: The WAV audio data.
		 * @param wavDataSize: The size of the WAV audio.
		 * @param tag: The tag to be searched.
		 * @param pData: The data pointer.
		 * @param dataCount: The data count.
		 * @return HRESULT value.
		 */
		HRESULT FindTable(const uint8* wavData, uint64 wavDataSize, WAVFileTag tag, const uint32** pData, uint32* dataCount);

		/**
		 * Load Audio From File.
		 * This loads audio data from the file.
		 *
		 * @param szFileName: The asset path.
		 * @param wavData: The WAV data pointer.
		 * @param bytesRead: The number of bytes read.
		 * @return HRESULT value.
		 */
		HRESULT LoadAudioFromFile(const wchar* szFileName, uint8** wavData, DWORD* bytesRead);

		/**
		 * Load the WAV audio data to the WAVEFORMATEX structure.
		 *
		 * @param wavData: The WAV file data.
		 * @param wavDataSize: The size of the WAV data.
		 * @param wfx: The WAVFormat structure pointer.
		 * @param startAudio: The start pointer.
		 * @param audioBytes: The audio bytes.
		 * @return HRESULT value.
		 */
		HRESULT LoadWAVAudioInMemory(const uint8* wavData, uint64 wavDataSize, WAVFormat* wfx, const uint8** startAudio, uint32* audioBytes);

		/**
		 * Load WAV audio from file.
		 *
		 * @param szFileName: The file name.
		 * @param wavData: The output audio data pointer.
		 * @param wfx: The WAVFormat structure pointer.
		 * @param startAudio: The start of the audio data.
		 * @param audioBytes: Number of audio bytes.
		 * @return HRESULT value.
		 */
		HRESULT LoadWAVAudioFromFile(const wchar* szFileName, uint8* wavData, WAVFormat* wfx, const uint8** startAudio, uint32* audioBytes);

		/**
		 * Load WAV Audio in Memory extension.
		 *
		 * @param wavData: The WAV data.
		 * @param wavDatSize: The size of the WAV data.
		 * @param result: The data result.
		 * @return HRESULT value.
		 */
		HRESULT LoadWAVAudioInMemoryEx(const uint8* wavData, uint64 wavDataSize, WAVData& result);

		/**
		 * Load WAV audio from file extension.
		 *
		 * @param szFileName: The name of the file.
		 * @param wavData: The WAV data pointer.
		 * @param result: The result value.
		 * @return HRESULT value.
		 */
		HRESULT LoadWAVAudioFromFileEx(const wchar* szFileName, uint8** wavData, WAVData& result);
	}
}
