//
//  UntzSystem.cpp
//  Part of UNTZ
//
//  Created by Francisco Tufro. (francisco@ziplinegames.com) on 02/18/2013.
//  Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
//

#include "UntzSystem.h"
#include "SystemData.h"
#include "AudioMixer.h"

#include <stdio.h>
#include <string.h>


#include <math.h>
#include <windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include "mmreg.h"


using namespace UNTZ;
using namespace std;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;

#define CHANNELS 2


namespace
{
	//
	// Handler for XAudio source voice callbacks to signal buffer end
	//
	struct SourceVoiceContext : public IXAudio2VoiceCallback
	{
	public:

		HANDLE hBufferEndEvent;
		SourceVoiceContext() : hBufferEndEvent(CreateEventEx(NULL, NULL, 0, EVENT_ALL_ACCESS))
		{
		}
		~SourceVoiceContext() {
			CloseHandle(hBufferEndEvent);
		}


		//
		// Voice callbacks from IXAudio2VoiceCallback
		//
		STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 bytesRequired);
		STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS);
		STDMETHOD_(void, OnStreamEnd) (THIS);
		STDMETHOD_(void, OnBufferStart) (THIS_ void* bufferContext);
		STDMETHOD_(void, OnBufferEnd) (THIS_ void* bufferContext);
		STDMETHOD_(void, OnLoopEnd) (THIS_ void* bufferContext);
		STDMETHOD_(void, OnVoiceError) (THIS_ void* bufferContext, HRESULT error);
	};

	//
	// Callback handlers, only implement the buffer events for maintaining play state
	//
	void SourceVoiceContext::OnVoiceProcessingPassStart(UINT32 /*bytesRequired*/)
	{
	}
	void SourceVoiceContext::OnVoiceProcessingPassEnd()
	{
	}
	void SourceVoiceContext::OnStreamEnd()
	{
	}
	void SourceVoiceContext::OnBufferStart(void* /*bufferContext*/)
	{

	}
	void SourceVoiceContext::OnBufferEnd(void* /*bufferContext*/)
	{
		SetEvent(hBufferEndEvent);
	}
	void SourceVoiceContext::OnLoopEnd(void* /*bufferContext*/)
	{
	}
	void SourceVoiceContext::OnVoiceError(void* /*bufferContext*/, HRESULT /*error*/)
	{
	}
}


class XAudioSystemData : public UNTZ::SystemData
{
public:
	XAudioSystemData() : SystemData() {};
  ~XAudioSystemData();
  
  UInt32 getNumFrames();
  UInt32 getNumOutputChannels();
  
  CRITICAL_SECTION mAudioCriticalSection;
  IAsyncAction^ mAudioThread;

  IXAudio2 *m_audioEngine;
  IXAudio2MasteringVoice *m_masteringVoice;
  IXAudio2SourceVoice *m_sourceVoice;
  SourceVoiceContext mVoiceContext;


  UInt32 mSampleRate;
  UInt32 mFramesPerBuffer;
  UInt32 mOptions;
};

XAudioSystemData::~XAudioSystemData() {
	if (m_sourceVoice) {
		m_sourceVoice->DestroyVoice();
		m_sourceVoice = nullptr;
	}

	if (m_masteringVoice) {
		m_masteringVoice->DestroyVoice();
		m_masteringVoice = nullptr;
	}

	if (m_audioEngine) {
		m_audioEngine->Release();
		m_audioEngine = nullptr;
	}
}

UInt32 XAudioSystemData::getNumFrames()
{
	return mFramesPerBuffer;
}
UInt32 XAudioSystemData::getNumOutputChannels()
{
    return CHANNELS;
}

static inline SInt16 limit_float_conv_SInt16(float inValue)
{
    //return (SInt16)((1-2*signbit(inValue)) * atanf(fabs(inValue) * 2.0f) * ((2.0f / 3.14f) * 32767));
		return (SInt16)(inValue * 32767);
}

/*
void SDL_callback (void *unused, Uint8 *_stream, int _length) {

    SDLSystemData* alsd = (SDLSystemData*) System::get ()->getData ();

	const int length = _length / CHANNELS;
	const int length_by_channels = length / CHANNELS;
	const float volume = alsd->mMixer.getVolume();
	float float_buffer[ length ];

	alsd->mMixer.process ( 0, NULL, CHANNELS, float_buffer, length_by_channels);

	// Convert left-right buffers to short samples and interleave.
	SInt16 intBuffer[ length ];
//	SInt16 *outbuf = &intBuffer[0];
	SInt16 *outbuf= (SInt16*) _stream;

    for(int i=0; i<length_by_channels; i++)
    {
        for(int j=0; j<CHANNELS; j++)
        {
        	*(outbuf++) = limit_float_conv_SInt16(volume * float_buffer[j*length_by_channels+i]); // HBS
        }
    }


//    SDL_MixAudio(_stream, (UInt8*)&intBuffer[0], length, SDL_MIX_MAXVOLUME);
}
*/



void fillBuffer() {
	
}

void audio_loop () {
	XAudioSystemData* alsd = (XAudioSystemData*)System::get()->getData();

	OutputDebugString(L"Creating Audio Engine");
	// Create the XAudio2 Engine
	UINT32 flags = 0;
	HRESULT hr;
	if (FAILED(XAudio2Create(&alsd->m_audioEngine, flags)))
	{
		OutputDebugString(L"Error creating audio  engine");
		alsd->setError(true);
		return;
	}

	if (FAILED(alsd->m_audioEngine->CreateMasteringVoice(
		&alsd->m_masteringVoice,
		XAUDIO2_DEFAULT_CHANNELS,
		alsd->mSampleRate
		)))
	{
		OutputDebugString(L"Error creating mastering voice");
		alsd->setError(true);
		return;
	}

	//now wire up our single input voice
	WAVEFORMATEX wfx;
	wfx.nChannels = CHANNELS;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nSamplesPerSec = alsd->mSampleRate;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	wfx.cbSize = 0;

	if (FAILED(hr = alsd->m_audioEngine->CreateSourceVoice(
		&alsd->m_sourceVoice,
		(WAVEFORMATEX*)&wfx,
		0,
		XAUDIO2_DEFAULT_FREQ_RATIO,
		reinterpret_cast<IXAudio2VoiceCallback*>(&alsd->mVoiceContext),
		nullptr,
		nullptr
		)))
	{
		OutputDebugString(L"Error creating Source voice");
		alsd->setError(true);
		return;
	}


	if (FAILED(alsd->m_audioEngine->StartEngine()))
	{
		OutputDebugString(L"Error creating starting audio engine");
		alsd->setError(true);
		return;
	}


#define STREAMING_BUFFER_SIZE_BYTES 8820// 2 channels * 16 bits per channel * 22050 samples per second *100ms/1000ms
#define MAX_BUFFER_COUNT 2


	const int samples = STREAMING_BUFFER_SIZE_BYTES / 2; //16bits per sample so divide by two
	const int samplesPerChannel = samples / CHANNELS;



	SInt16 buffers[MAX_BUFFER_COUNT][samples];

	int buffer = 0;
	float float_buffer[samples];
	XAUDIO2_VOICE_STATE state;
	

	auto sourceVoice = alsd->m_sourceVoice;

	if (FAILED(hr=sourceVoice->Start(0, 0))) {
		zl_printf("Start failed %x", hr);
	}
	auto mythread = alsd->mAudioThread;
	auto voiceContext = alsd->mVoiceContext;
	while (mythread->Status != AsyncStatus::Canceled) {
		//read from mixer
		const float volume = alsd->mMixer.getVolume();
		alsd->mMixer.process(0, NULL, CHANNELS, float_buffer, samplesPerChannel);
		SInt16 *outbuf = (SInt16 *)buffers[buffer];
		for (int i = 0; i<samplesPerChannel; i++)
		{
			for (int j = 0; j<CHANNELS; j++)
			{
				*(outbuf++) = limit_float_conv_SInt16(volume * float_buffer[j*samplesPerChannel + i]); 
			}
		}

		XAUDIO2_BUFFER buf = { 0 };
		buf.AudioBytes = STREAMING_BUFFER_SIZE_BYTES;

		buf.pAudioData = (BYTE *)buffers[buffer];
		//directx will queue this sound up
		HRESULT hr2 = sourceVoice->SubmitSourceBuffer(&buf);
		if (FAILED(hr2)) {
			zl_printf("Buffer submit failed %x\n", hr2);
		}
		//use our next buffer while this one is playing
		buffer++;
		if (buffer >= MAX_BUFFER_COUNT) {
			buffer = 0;
		}

		//wait for one of our buffers to free up
		while (sourceVoice->GetState(&state), state.BuffersQueued >= MAX_BUFFER_COUNT - 1)
		{
			WaitForSingleObjectEx(voiceContext.hBufferEndEvent, 1000, FALSE); 
		}
	}


	
}

System* System::msInstance = 0;

System::System(UInt32 sampleRate, UInt32 numFrames, UInt32 options)
{
	XAudioSystemData *alsd = new XAudioSystemData();
	alsd->mSampleRate = sampleRate;
	alsd->mFramesPerBuffer = numFrames;
	alsd->mOptions = options;
	mpData = alsd;

	auto workItem = ref new WorkItemHandler(
		[this](IAsyncAction^ workItem)
	{
		audio_loop();
	});

	alsd->mAudioThread = ThreadPool::RunAsync(workItem);
}

System::~System()
{

	if(mpData)
		delete mpData;
}

void System::shutdown()
{
	if(msInstance)
	{
		delete msInstance;
		msInstance = 0;
	}
}

System* System::initialize(UInt32 sampleRate, UInt32 numFrames, UInt32 options)
{

	if(!msInstance)
	{
		msInstance = new System(sampleRate, numFrames, options);
		if(msInstance->mpData->getError())
		{
			delete msInstance;
		}
		else
		{
			msInstance->mpData->mMixer.init();
		}
	}

	return msInstance;
}

System* System::get()
{
	return msInstance;
}

void System::setSampleRate(UInt32 sampleRate)
{
	// TODO: Implement
}

unsigned int System::getSampleRate()
{
	XAudioSystemData* alsd = (XAudioSystemData*)mpData;
	return alsd->mSampleRate;
}

void System::setVolume(float volume)
{
	return msInstance->mpData->mMixer.setVolume(volume);
}

float System::getVolume() const
{
	return msInstance->mpData->mMixer.getVolume();
}

void System::suspend()
{
	msInstance->mpData->setActive(false);
	XAudioSystemData* alsd = (XAudioSystemData*)mpData;

	if (alsd->m_audioEngine)
		alsd->m_audioEngine->StopEngine();

}

void System::resume()
{
	msInstance->mpData->setActive(true);
	XAudioSystemData* alsd = (XAudioSystemData*)mpData;

	if (alsd->m_audioEngine)
		alsd->m_audioEngine->StartEngine();

}


