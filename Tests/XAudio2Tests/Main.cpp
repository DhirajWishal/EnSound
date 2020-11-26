// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2/XAudio2Backend.h"

int main()
{
	EnSound::XAudio2::XAudio2Backend mBackend;
	mBackend.Initialize();

	mBackend.PlayLoop(STRING("..\\..\\Assets\\Audio\\Gun+357+Magnum.wav"), 5);

	auto mHandle = mBackend.CreateAudioObject(STRING("..\\..\\Assets\\Audio\\file_example_WAV_10MG.wav"));
	mBackend.PlayAudioOnce(mHandle);

	mBackend.Terminate();
}