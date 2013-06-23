Raspberry Pi EAS Sonivox Library
================================

Raspberry Pi implementation of the Android EAS Sonivox MIDI library.

### To Use

You will need:

  * The android/platform\_external\_sonivox sources from
    https://github.com/android/platform_external_sonivox
  * The Makefile from the arm-wt-22k folder here
  
For convenience move the arm-wt-22k folder to your workspace. Copy the
Makefile from here to the folder. Run make. You will get a couple of
warnings:

	lib_src/eas_reverb.c: In function 'ReverbCalculateSinCos':
	lib_src/eas_reverb.c:495:5: warning: this decimal constant is unsigned only in ISO C90 [enabled by default]
	lib_src/eas_reverb.c:500:5: warning: this decimal constant is unsigned only in ISO C90 [enabled by default]

I tried this originally for a bit of fun as I have used this
unsupported library in other android projects. However I am impressed
with the quality of the output compared to other midi libraries using
large soundfont files. There are the sources for two programs in the
midi folder. Playmidi plays midi files. Try playing the two Carolan
midi files. Sonivox uses midi streaming to play a couple of organ
notes, then turn them off.
