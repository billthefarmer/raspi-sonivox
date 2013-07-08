Raspberry Pi EAS Sonivox Library
================================

Raspberry Pi implementation of the Android EAS Sonivox MIDI library.

### To Use

You will need:

  * The android/platform\_external\_sonivox sources from
    https://github.com/android/platform_external_sonivox
  * The Makefile from the arm-wt-22k folder here
  
For convenience move the arm-wt-22k folder to your workspace. Copy the
Makefile from here to the folder. Comment out some lines in
host\_src/eas\_hostmm.c:

	// #define LOG_TAG "Sonivox"
	// #include <utils/Log.h>
	// #include <media/MediaPlayerInterface.h>

otherwise you will get compile errors. These include files aren't
used. Run make. You will get a couple of warnings:

	lib_src/eas_reverb.c: In function 'ReverbCalculateSinCos':
	lib_src/eas_reverb.c:495:5: warning: this decimal constant is unsigned only in ISO C90 [enabled by default]
	lib_src/eas_reverb.c:500:5: warning: this decimal constant is unsigned only in ISO C90 [enabled by default]

I tried this originally as I have used this unsupported library in
other android projects. However I am impressed with the quality of the
output compared to other midi libraries using large soundfont
files. There are the sources for two programs and a shared library in
in the midi folder. The shared library provides the code to feed the
output of the synthesizer into the ALSA sound system. Playmidi plays
midi files, and several other formats. There are some test files in
the vectors folder. Try playing the two Carolan midi files. Sonivox
uses midi streaming to play a couple of organ notes, then turn them
off.

I have tried this on a i386 based linux system. A few changes are
required in the arm-wt-22k/Makefile:

	 # TARGET_ARCH = arm
	 LOCAL_CFLAGS+= -O2 -fPIC \ 

so as to not compile the arm assembler files and keep gcc happy. The
output sounds fine. However it doesn't work quite right on a i386-x64
system, there is booming cumulative feedback, which can be fixed by
changing a line in midi/midi.c from:

	EAS_SetParameter(pEASData, EAS_MODULE_REVERB, EAS_PARAM_REVERB_PRESET,
		     EAS_PARAM_REVERB_CHAMBER);

to:

	EAS_SetParameter(pEASData, EAS_MODULE_REVERB, EAS_PARAM_REVERB_PRESET,
		     EAS_PARAM_REVERB_ROOM);

I think this is probably due to EAS\_I32 being defined as a long which
is 64 bits on an x64 platform.
