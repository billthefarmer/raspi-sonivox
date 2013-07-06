////////////////////////////////////////////////////////////////////////////////
//
// File: midi.h
//
// Copyright 2013 Bill Farmer
//
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

#ifndef MIDI_H
#define MIDI_H

#ifndef FALSE
typedef enum
    {
	FALSE = 0,
	TRUE
    } E_BOOL;
#endif

typedef long MIDI_RESULT;
typedef enum
    {
	MIDI_SUCCESS = 0,
	MIDI_FAILURE = -1,
	MIDI_ERROR_INVALID_MODULE = -2,
	MIDI_ERROR_MALLOC_FAILED = -3,
	MIDI_ERROR_FILE_POS = -4,
	MIDI_ERROR_INVALID_FILE_MODE = -5,
	MIDI_ERROR_FILE_SEEK = -6,
	MIDI_ERROR_FILE_LENGTH = -7,
	MIDI_ERROR_NOT_IMPLEMENTED = -8,
	MIDI_ERROR_CLOSE_FAILED = -9,
	MIDI_ERROR_FILE_OPEN_FAILED = -10,
	MIDI_ERROR_INVALID_HANDLE = -11,
	MIDI_ERROR_NO_MIX_BUFFER = -12,
	MIDI_ERROR_PARAMETER_RANGE = -13,
	MIDI_ERROR_MAX_FILES_OPEN = -14,
	MIDI_ERROR_UNRECOGNIZED_FORMAT = -15,
	MIDI_BUFFER_SIZE_MISMATCH = -16,
	MIDI_ERROR_FILE_FORMAT = -17,
	MIDI_ERROR_SMF_NOT_INITIALIZED = -18,
	MIDI_ERROR_LOCATE_BEYOND_END = -19,
	MIDI_ERROR_INVALID_PCM_TYPE = -20,
	MIDI_ERROR_MAX_PCM_STREAMS = -21,
	MIDI_ERROR_NO_VOICE_ALLOCATED = -22,
	MIDI_ERROR_INVALID_CHANNEL = -23,
	MIDI_ERROR_ALREADY_STOPPED = -24,
	MIDI_ERROR_FILE_READ_FAILED = -25,
	MIDI_ERROR_HANDLE_INTEGRITY = -26,
	MIDI_ERROR_MAX_STREAMS_OPEN = -27,
	MIDI_ERROR_INVALID_PARAMETER = -28,
	MIDI_ERROR_FEATURE_NOT_AVAILABLE = -29,
	MIDI_ERROR_SOUND_LIBRARY = -30,
	MIDI_ERROR_NOT_VALID_IN_THIS_STATE = -31,
	MIDI_ERROR_NO_VIRTUAL_SYNTHESIZER = -32,
	MIDI_ERROR_FILE_ALREADY_OPEN = -33,
	MIDI_ERROR_FILE_ALREADY_CLOSED = -34,
	MIDI_ERROR_INCOMPATIBLE_VERSION = -35,
	MIDI_ERROR_QUEUE_IS_FULL = -36,
	MIDI_ERROR_QUEUE_IS_EMPTY = -37,
	MIDI_ERROR_FEATURE_ALREADY_ACTIVE = -38
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
#endif
