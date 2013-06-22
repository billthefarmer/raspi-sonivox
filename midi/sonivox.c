////////////////////////////////////////////////////////////////////////////////
//
// File: sonivox.c
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
#include <stdlib.h>

#include "midi.h"

// MIDI data
static char midiOn[] =
    {0xc0, 19, 0x90, 64, 95, 0x90, 72, 95};
static char midiOff[] =
    {0x80, 64, 0, 0x80, 72, 0};

// main
int main(int argc, char *argv[])
{
    MIDI_HANDLE handle;

    // init midi

    if (MIDI_Init() < 0)
    {
	fprintf(stderr, "sonivox: Midi initialization failed\n");
	return 1;
    }

    // open stream

    if (MIDI_OpenStream(&handle) < 0)
    {
	MIDI_Shutdown();
	fprintf(stderr, "sonivox: Can't open midi stream\n");
	return 1;
    }

    // write notes on

    if (MIDI_WriteStream(handle, midiOn, sizeof(midiOn)) < 0)
    {
	MIDI_CloseStream(handle);
	MIDI_Shutdown();
	fprintf(stderr, "sonivox: Can't write to  midi stream\n");
	return 1;
    }

    // wait for a bit

    sleep(5);

    // write notes off

    if (MIDI_WriteStream(handle, midiOff, sizeof(midiOff)) < 0)
    {
	MIDI_CloseStream(handle);
	MIDI_Shutdown();
	fprintf(stderr, "sonivox: Can't write to  midi stream\n");
	return 1;
    }

    // wait a bit more

    sleep(2);

    // close stream

    if (MIDI_CloseStream(handle) < 0)
    {
	MIDI_Shutdown();
	fprintf(stderr, "sonivox: Can't close  midi stream\n");
	return 1;
    }

    // shutdown

    if (MIDI_Shutdown()< 0)
    {
	fprintf(stderr, "sonivox: Midi shutdown failed\n");
	return 1;
    }

    return 0;
}
