////////////////////////////////////////////////////////////////////////////////
//
// File: midi.h
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

typedef enum
    {
	FALSE = 0,
	TRUE
    } E_BOOL;

typedef long MIDI_RESULT;
typedef enum
    {
	MIDI_SUCCESS = 0,
	MIDI_FAILURE = -1
    } E_MIDI_RESULT;

typedef long MIDI_STATE;
typedef enum
    {
	MIDI_STATE_READY = 0,
	MIDI_STATE_PLAY,
	MIDI_STATE_STOPPING,
	MIDI_STATE_PAUSING,
	MIDI_STATE_STOPPED,
	MIDI_STATE_PAUSED,
	MIDI_STATE_OPEN,
	MIDI_STATE_ERROR,
	MIDI_STATE_EMPTY
    } E_MIDI_STATE;

typedef struct s_eas_stream_tag *MIDI_HANDLE;

MIDI_RESULT MIDI_Init();
MIDI_RESULT MIDI_PlayFile(char *, MIDI_HANDLE *);
MIDI_RESULT MIDI_CloseFile(MIDI_HANDLE);
MIDI_RESULT MIDI_State(MIDI_HANDLE, MIDI_STATE *);
MIDI_RESULT MIDI_OpenStream(MIDI_HANDLE *);
MIDI_RESULT MIDI_WriteStream(MIDI_HANDLE, char *, long);
MIDI_RESULT MIDI_CloseStream(MIDI_HANDLE);
MIDI_RESULT MIDI_Shutdown();
