////////////////////////////////////////////////////////////////////////////////
//
// File: midi.c
//
// Copyright 1203 Bill Farmer

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <alsa/asoundlib.h>

#include "eas.h"
#include "eas_reverb.h"

#include "midi.h"

// How many EAS buffers to fill a host buffer
#define NUM_BUFFERS 4

// EAS data
static EAS_DATA_HANDLE pEASData;
const S_EAS_LIB_CONFIG *pLibConfig;
static EAS_PCM *buffer;
static EAS_I32 bufferSize;
static EAS_FILE file;

// ALSA data
static char *device = "default";
static snd_pcm_t *handle;

// thread
static pthread_t thread;

// flag
static long flag;

// functions
void *render(void *);

// midi init
MIDI_RESULT MIDI_Init()
{
    EAS_RESULT result;

    // get the library configuration
    pLibConfig = EAS_Config();
    if ((pLibConfig == NULL) || (pLibConfig->libVersion != LIB_VERSION))
	return MIDI_FAILURE;

    // init library
    if ((result = EAS_Init(&pEASData)) != EAS_SUCCESS)
        return MIDI_FAILURE;

    // select reverb preset and enable
    EAS_SetParameter(pEASData, EAS_MODULE_REVERB, EAS_PARAM_REVERB_PRESET,
		     EAS_PARAM_REVERB_CHAMBER);
    EAS_SetParameter(pEASData, EAS_MODULE_REVERB, EAS_PARAM_REVERB_BYPASS,
		     EAS_FALSE);

    // open pcm stream
    if ((result = snd_pcm_open(&handle, device,
			       SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	return MIDI_FAILURE;

    // set stream parameters
    if ((result = snd_pcm_set_params(handle, SND_PCM_FORMAT_S16,
				     SND_PCM_ACCESS_RW_INTERLEAVED,
				     pLibConfig->numChannels,
				     pLibConfig->sampleRate,
				     1, 50000)) < 0)
	return MIDI_FAILURE;

    // calculate buffer size in samples
    bufferSize = pLibConfig->mixBufferSize * pLibConfig->numChannels *
	NUM_BUFFERS;

    // allocate buffer in bytes
    buffer = malloc(bufferSize * sizeof(EAS_PCM));

    // clear flag
    flag = FALSE;

    // start rendering thread
    pthread_create(&thread, NULL, render, NULL);

    return MIDI_SUCCESS;
}

// play
MIDI_RESULT MIDI_PlayFile(char *path, MIDI_HANDLE *handle)
{
    EAS_RESULT result;

    // fill in file struct
    file.path = path;
    file.fd = 0;

    // open file
    if ((result = EAS_OpenFile(pEASData, &file, handle)) != EAS_SUCCESS)
	return MIDI_FAILURE;

    // prepare
    if ((result =  EAS_Prepare(pEASData, *handle)) != EAS_SUCCESS)
	return MIDI_FAILURE;

    return MIDI_SUCCESS;
}

// close midi stream
MIDI_RESULT MIDI_CloseFile(MIDI_HANDLE handle)
{
    EAS_RESULT result;

    // close midi stream
    if ((result = EAS_CloseFile(pEASData, handle)) != EAS_SUCCESS)
	return MIDI_FAILURE;

    return MIDI_SUCCESS;
}

MIDI_RESULT MIDI_State(MIDI_HANDLE handle, MIDI_STATE *state)
{
    EAS_RESULT result;

    // check stream state
    if ((result = EAS_State(pEASData, handle, state)) !=
	EAS_SUCCESS)
	return MIDI_FAILURE;

    return MIDI_SUCCESS;
}

MIDI_RESULT MIDI_OpenStream(MIDI_HANDLE *handle)
{
    EAS_RESULT result;

    // open midi stream
    if ((result = EAS_OpenMIDIStream(pEASData, handle, NULL)) !=
	EAS_SUCCESS)
	return MIDI_FAILURE;

    return MIDI_SUCCESS;
}

// write midi stream
MIDI_RESULT MIDI_WriteStream(MIDI_HANDLE handle, char *data, long size)
{
    EAS_RESULT result;

    // write midi stream
    if ((result = EAS_WriteMIDIStream(pEASData, handle, data,
				      size)) != EAS_SUCCESS)
	return MIDI_FAILURE;

    return MIDI_SUCCESS;
}

// close stream
MIDI_RESULT MIDI_CloseStream(MIDI_HANDLE handle)
{
    EAS_RESULT result;

    // close midi stream
    if ((result = EAS_CloseMIDIStream(pEASData, handle)) != EAS_SUCCESS)
	return MIDI_FAILURE;

    return MIDI_SUCCESS;
}

// shutdown
MIDI_RESULT MIDI_Shutdown()
{
    EAS_RESULT result;

    // set flag
    flag = TRUE;

    // join render thread
    pthread_join(thread, NULL);

    // close pcm
    if ((result = snd_pcm_close(handle)) < 0)
    {
	free(buffer);
	EAS_Shutdown(pEASData);
	return MIDI_FAILURE;
    }

    // free buffer
    free(buffer);

    // shutdown library
    if ((result = EAS_Shutdown(pEASData)) < 0)
	return MIDI_FAILURE;

    return MIDI_SUCCESS;
}

// render
void * render(void *data)
{
    EAS_RESULT result;
    EAS_I32 numGenerated;
    EAS_I32 count;

    snd_pcm_sframes_t frames;
    snd_pcm_sframes_t size;

    // start loop
    while (flag == FALSE)
    {
	count = 0;
	while (count < bufferSize)
	{
	    // render
	    if ((result = EAS_Render(pEASData,  buffer + count,
				     pLibConfig->mixBufferSize,
				     &numGenerated)) != EAS_SUCCESS)
		break;

	    // calculate count in samples
	    count += numGenerated * pLibConfig->numChannels;
	}

	// calculate size in frames
	size = count / pLibConfig->numChannels;

	if (result == EAS_SUCCESS)
	{
	    // write pcm
	    frames = snd_pcm_writei(handle, buffer, size);

	    // try to recover if error
	    if (frames < 0)
		frames = snd_pcm_recover(handle, frames, 0);

	    // else give up
	    if (frames < 0)
		break;
	}
    }
}
