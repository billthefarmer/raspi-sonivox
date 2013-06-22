////////////////////////////////////////////////////////////////////////////////
//
// File: playmidi.c
//
// Copyright 2013 Bill Farmer

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

#include "midi.h"

// main
int main(int argc, char *argv[])
{
    MIDI_RESULT result;
    MIDI_HANDLE handle;
    MIDI_STATE state;

    // no file
    if (argc < 2)
    {
	fprintf(stderr, "Usage: playmidi <midi file>\n");
	return 1;
    }

    // init midi
    if (result = MIDI_Init() != MIDI_SUCCESS)
    {
	fprintf(stderr, "playmidi: Midi initialization failed\n");
	return 1;
    }

    // play file
    if (result = MIDI_PlayFile(argv[1], &handle) != MIDI_SUCCESS)
    {
	fprintf(stderr, "playmidi: Can't open '%s' for playing\n", argv[1]);
	MIDI_Shutdown();
	return 1;
    }

    // wait for finish
    while (state != MIDI_STATE_STOPPED && state != MIDI_STATE_ERROR)
    {
	// midi state
	if (result = MIDI_State(handle, &state) != MIDI_SUCCESS)
	    break;

	// sleep 1s
	sleep(1);
    }

    // close file
    if (result = MIDI_CloseFile(handle) != MIDI_SUCCESS)
    {
	fprintf(stderr, "playmidi: Can't close midi stream\n");
	MIDI_Shutdown();
	return 1;
    }

    // shutdown midi
    if (result = MIDI_Shutdown() != MIDI_SUCCESS)
    {
	fprintf(stderr, "playmidi: Can't shut down midi\n");
	return 1;
    }

    return 0;
}
