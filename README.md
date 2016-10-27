Raspberry Pi EAS Sonivox Library
================================

Raspberry Pi implementation of the Android EAS Sonivox MIDI library.

The up to date EAS Sonivox sources have been added and modified to
remove references to Android include files.

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
	LOCAL_CFLAGS += -O2 -std=gnu99 \ 

so as to not compile the arm assembler files. The output sounds
fine.
